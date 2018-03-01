#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <vector>

#include <string_util.h>
#include <util.h>
#include "ohlcv_fmt.h"


using namespace std;

struct FeedRec_T
{
	struct tm timestamp;
	double	open;
	double	high;
	double	low;
	double	close;
	double	volume_base;
	double 	volume_currency;

	FeedRec_T()
	:timestamp({0}), open(0.0), high(0.0), low(0.0), close(0.0),
	 volume_base(0.0), volume_currency(0.0)
	{}
};


string feeds_dir = "/home/data/crypt_data/";
string write_dir = "/home/data/crypt_ohlcv/";

CryptoFeed_T current_feed = Feed_Unknown;


int config();
int processFeeds();
CryptoFeed_T getFeed( string path );


void test();

	
int main()
{
	int rc;

	//test(); return 0;

	rc = config();
	if (rc)
	{
		return rc;
	}
	cout<< "Config completed."<< endl<< endl;

	processFeeds();

    return 0;
}


int config()
{
	string var, value;
	char line[1024];
	DIR *dr;
	size_t i;

	ifstream cfgs( CRYPT_CONFIG_FILE );
	if (cfgs.fail())
	{
		cerr << "Failed to open config file '"<< CRYPT_CONFIG_FILE
			 << "'. Make sure the config file exists with read permissions." << endl;
		return -1;
	}

	while (cfgs.good())
	{

		cfgs.getline(line, 1023);
		string lnstr( common::trim(line) );
		i = lnstr.find("=");
		if  (  ( lnstr[0] == '#' ) 		// skip as comments
			|| (i == string::npos)
			)
		{
			continue;
		}
		var = lnstr.substr(0, i);
		value = lnstr.substr(i + 1);
		value = common::trim(value);
		if (var.find("feeds_dir") != string::npos)
		{
			feeds_dir = common::trim(value);
			if (feeds_dir[feeds_dir.size() - 1] != '/')
			{
				feeds_dir.push_back('/');
			}
			//cout << feeds_dir.c_str() << endl;
		}
		else if (var.find("write_dir") != string::npos)
		{
			// make sure write directory extsts with write permissions
			write_dir = common::trim(value);
			if (write_dir[write_dir.size() - 1] != '/')
			{
				write_dir.push_back('/');
			}
			string test_dir, test_file;
			test_dir = write_dir + "test_dir/";
			test_file = test_dir + "test_file.txt";

			if (  ( ( dr = opendir(write_dir.c_str())) == NULL ) )
			{
				cout<< "Test directory does not exist. Creating... ";
				if ( mkdir(write_dir.c_str(), 0775) != 0 )
				{
					cerr << endl<< "Failed to open or create the write directory: "<< write_dir.c_str()<< endl;
					cfgs.close();
					return -2;
				}
				else if ( mkdir(test_dir.c_str(), 0775) != 0 )
				{
					cerr << endl<< "Failed to open or create the write test directory: "<< test_dir.c_str()<< endl;
					cfgs.close();
					return -3;
				}
				cout<< "done."<< endl;
			}
			else
			{
				closedir(dr);
				if (  ( dr = opendir(test_dir.c_str() ) ) == NULL )
				{
					cout<< "Test directory does not exist. Creating... ";
					if ( mkdir(test_dir.c_str(), 0775) != 0 )
					{
						cerr << endl<< "Failed to open or create the write test directory: "<< test_dir.c_str()<< endl;
						cfgs.close();
						return -3;
					}
					cout<< "done."<< endl;
				}
				else
				{
					closedir( dr );
				}
			}

			ofstream wfs( test_file );
			if ( wfs.fail() )
			{
				cerr << "Failed to open or create the write test file: "<< test_file.c_str()<< endl;
				cfgs.close();
				return -3;
			}
			wfs.close();
			string cmd( "rm -rf " );
			cmd = cmd + test_dir.c_str();
			system( cmd.c_str() );
		}
	}
	cfgs.close();

	return 0;
}

int getLineData( FeedRec_T &rec, string line )
{
	string discard;
	stringbuf sbuf( line );
	istream is(&sbuf);

	if ( common::contains( line, "NaN") )	// missing data
		return -1;

	// bitcoin feed
	// Timestamp,Open,High,Low,Close,Volume_(BTC),Volume_(Currency),Weighted_Price
	// 1389118680,874.6704,892.06753,874.6704,892.06753,0.03191496,28.191321036,883.32622181
	if (current_feed ==  Feed_BitcoinHistory )
	{
		//cout<< endl;
		if ( is.good() )
		{
			time_t ts;
			is >> ts;	// as epoch
			getline( is, discard, ',');	// remove comma

			rec.timestamp = *(localtime(&ts));

			// some tweaking for errors in epoch conversion c function
			rec.timestamp.tm_year += 1900;
			rec.timestamp.tm_mon += 1;
		}
		else
		{
			cerr<< "Feed csv error for Date, less than required fields: "<< line<< endl;
			return -2;
		}
		if ( is.good() )
		{
			is >> rec.open;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error Open, less than required fields: "<< line<< endl;
			return -3;
		}
		if ( is.good() )
		{
			is >> rec.high;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error High, less than required fields: "<< line<< endl;
			return -4;
		}
		if ( is.good() )
		{
			is >> rec.low;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error Low, less than required fields: "<< line<< endl;
			return -5;
		}
		if ( is.good() )
		{
			is >> rec.close;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error Close, less than required fields: "<< line<< endl;
			return -6;
		}
		if ( is.good() )
		{
			is >> rec.volume_base;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error Volume (BTC), less than required fields: "<< line<< endl;
			return -7;
		}
		if ( is.good() )
		{
			is >> rec.volume_currency;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error Volume (currency), less than required fields: "<< line<< endl;
			return -8;
		}
		if ( is.good() )
		{
			getline( is, discard ); // discard "weighted price" through to the end of the line

		}
		else
		{
			// Do nothing. We've got what we want.
		}
	}
	// Bittrex feed
	// [TimeStamp], [Open], [Close], [High], [Low], [Volume], [BaseVolume]
	//  2/14/2014 7:47:00 AM,0.00000400,0.00000400,0.00000400,0.00000400,50000.00000000,0.20000000
	else if (current_feed ==  Feed_BittrexHistory )
	{
		if ( is.good() )	// timestamp is in ascii string format: 2/14/2014 7:47:00 AM
		{
			string am_pm;
			is >> rec.timestamp.tm_mon;		getline( is, discard, '/');
			is >> rec.timestamp.tm_mday;		getline( is, discard, '/');
			is >> rec.timestamp.tm_year;
			is >> rec.timestamp.tm_hour;		getline( is, discard, ':');
			is >> rec.timestamp.tm_min;		getline( is, discard, ':');
			is >> rec.timestamp.tm_sec;
			getline( is, am_pm, ',' );
			if ( common::contains( am_pm, "PM") )
			{
				rec.timestamp.tm_hour += 12;
			}
		}
		else
		{
			cerr<< "Feed csv error for Date, less than required fields: "<< line<< endl;
			return -2;
		}
		if ( is.good() )
		{
			is >> rec.open;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error Open, less than required fields: "<< line<< endl;
			return -3;
		}
		if ( is.good() )
		{
			is >> rec.close;
			getline( is, discard, ',');	// remove comma

		}
		else
		{
			cerr<< "Feed csv error Close, less than required fields: "<< line<< endl;
			return -4;
		}
		if ( is.good() )
		{
			is >> rec.high;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error High, less than required fields: "<< line<< endl;
			return -5;
		}
		if ( is.good() )
		{
			is >> rec.low;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error Low, less than required fields: "<< line<< endl;
			return -6;
		}
		if ( is.good() )
		{
			is >> rec.volume_currency;
			getline( is, discard, ',');	// remove comma
		}
		else
		{
			cerr<< "Feed csv error Volume (currency), less than required fields: "<< line<< endl;
			return -7;
		}
		if ( is.good() )
		{
			is >> rec.volume_base;
		}
		else
		{
			cerr<< "Feed csv error Volume (crype), less than required fields: "<< line<< endl;
			return -8;
		}
	}
	else
	{
		cerr<< "CSV for unknown feed."<< endl;
	}

	return 0;
}

inline long get_day( struct tm &dtm )
{
	return ( dtm.tm_year * 10000  +  dtm.tm_mon * 100 + dtm.tm_mday );
}

/** @brief Converts each feed file and writs it to the destination csv file in the right format */
int convertFeed( string readFile, string writeFile )
{
	char line[1024];
	FeedRec_T rec, line_rec;
	bool started = false;
	int rtn;

	ifstream ifs( readFile.c_str() );
	if (ifs.fail())
	{
		cerr << "Failed to open feed csv: " << readFile.c_str()<< endl;
		return -1;
	}
	// We are converting 1-min bars to daily bars.
	writeFile = common::strrep1( writeFile, "1-min", "daily" );

	ofstream ofs( writeFile.c_str() );
	if ( ofs.fail() )
	{
		cerr << "Failed to open output csv: " << writeFile.c_str()<< endl;
		return -2;
	}

	cout<< " Processing feed csv file: "<< readFile.c_str()<< endl;
	cout<< " Writing to csv file: "<< writeFile.c_str()<< endl;
	ofs<< "[Date],[Open],[High],[Low],[Close],[Volume-crypto],[Volume-currency]"<< endl;

	started = false;
	while ( ifs.good())
	{

		ifs.getline(line, 1023);
		string lnstr( common::trim(line) );
		//cout<< line;

		if ( lnstr.empty() ||  (lnstr[0] == '#') ) // skip empty or comment lines
		{
			// skip
		}
		else if ( common::contains( lnstr, "TimeStamp" ) )
		{
			started = true;
		}
		else if ( started )
		{
			// populate FeedRec_T
			rtn = getLineData( line_rec, line );
			if ( rtn < 0 )
			{
				// error line, ignore
			}
			else
			{
				if ( get_day( rec.timestamp) == 0 )
				{
					// first record
					rec = line_rec;
				}
				else if ( get_day( rec.timestamp) == get_day( line_rec.timestamp) )	// aggregate for daily data
				{
					rec.close = line_rec.close;
					if ( rec.high < line_rec.high )
					{
						rec.high = line_rec.high;
					}
					if ( rec.low > line_rec.low )
					{
						rec.low = line_rec.low;
					}
					rec.volume_base += line_rec.volume_base;
					rec.volume_currency += line_rec.volume_currency;
				}
				else
				{
					ofs << fixed;
					ofs.precision(8);

					ofs << get_day( rec.timestamp)<< ','
						<< rec.open<< ','
						<< rec.high<< ','
						<< rec.low<< ','
						<< rec.close<< ','
						<< rec.volume_base << ','
						<< rec.volume_currency << endl;

					/*
					cout<< fixed;
					cout.precision(8);
					cout<< get_day( rec.timestamp)<< ','
						<< rec.open<< ','
						<< rec.high<< ','
						<< rec.low<< ','
						<< rec.close<< ','
						<< rec.volume_base << ','
						<< rec.volume_currency << endl;
						*/


					// start a new aggregation record
					rec = line_rec;
				}
			}
		}

	}

	ifs.close();
	ofs.close();

	return 0;
}


int processFeeds()
{
	vector<string> feeds;
	int rc;

	rc = common::listdir( feeds, feeds_dir );
	if ( rc )
	{
		return -1;	// could not find or could not read the feeds directory
	}

	string cmd = string("rm -rf ") + write_dir + "/*";
	system( cmd.c_str() );

	for ( size_t i = 0; i < feeds.size(); ++i )
	{
		if ( (feeds[i] != string("bak"))  &&  	// directories to skip
			 (feeds[i] != string("zips")) )		// directories to ignore
		{
			vector<string> fxfiles;
			string fdir = feeds_dir + feeds[i] + "/";
			string wdir = write_dir + feeds[i] + "/";

			common::create_empty_dir( wdir );
			current_feed = getFeed( fdir );
			if ( current_feed < Feed_Unknown )	// Feed recognised
			{
				rc = common::listdir( fxfiles, fdir );
				if ( rc == 0 )
				{
					for ( size_t j = 0; j < fxfiles.size(); ++j )
					{
						cout<< "\nProcessing feed: "<< feeds[i] << "/"<< fxfiles[j]<< endl;
						convertFeed( fdir + fxfiles[j], wdir + fxfiles[j] );
					}
				}
			}
			else
			{
				cerr<< "[ERROR] Unknown feed at: "<< fdir<< endl;
				continue;
			}
		}
	}

	return 0;
}

CryptoFeed_T getFeed( string path )
{
	CryptoFeed_T fd = Feed_Unknown;

	if ( common::contains( path, "bittrex") )
	{
		fd = Feed_BittrexHistory;
	}
	else if ( common::contains( path, "bitcoin") )
	{
		fd = Feed_BitcoinHistory;
	}
	return fd;
}


/*-------------------------------------------------------------------------
 * Test functions.
 */

void dir_test()
{
	vector<string> dirEntries;
	int rc;

	rc = common::listdir( dirEntries, feeds_dir );
	if ( rc ) return;
	for ( size_t i = 0; i < dirEntries.size(); ++i )
	{
		cout<< " ["<< dirEntries[i].c_str() << "]" << endl;
	}
	cout<< endl;

}

void line_test()
{
	struct tm dtm = {0};
	cout<< "Day ["<< get_day( dtm )<< "] "<< endl;
	cout<< "get_day( dtm ) == 0 ? "<< (get_day(dtm) == 0) << endl;

	time_t tm = 1519939131;
	struct tm *tp = gmtime(&tm);
	cout<< "year: "<< tp->tm_year << "  month: "<< tp->tm_mon<< endl;
	cout<< "Day of 1519939131 ["<< get_day( *tp )<< "] "<< endl;

	cout<< "Epoch now: "<< time(NULL)<< endl;
}


void test()
{
	line_test();
}

