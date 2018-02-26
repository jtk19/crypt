#include <iostream>
#include <fstream>
#include <vector>

#include "string_util.h"
#include <util.h>
#include "ohlcv_fmt.h"


using namespace std;


string feeds_dir = "/home/data/crypt_data/";

int config();
int processFeeds();


void test();

	
int main()
{
	int rc;

	//test();

	rc = config();
	if (rc)
	{
		return rc;
	}
	processFeeds();

    return 0;
}


int config()
{
	string var, value;
	char line[1024];
	size_t i;

	ifstream cfgs( "crypt_config.txt" );
	if (cfgs.fail())
	{
		cerr << "Failed to open config file 'config.txt'. Make sure the config file exists." << endl;
		return -1;
	}

	while (cfgs.good())
	{

		cfgs.getline(line, 1023);
		string lnstr(line);
		i = lnstr.find("=");
		if (i == string::npos)
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
			cout << feeds_dir.c_str() << endl;
		}
	}

	return 0;
}

/** @brief Converts each feed file and writs it to the destination csv file in the right format */
int convertFeed( string file )
{
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

	for ( size_t i = 0; i < feeds.size(); ++i )
	{
		if ( (feeds[i] != string("bak"))  &&  	// directories to skip
			 (feeds[i] != string("zips")) )		// directories to ignore
		{
			vector<string> fxfiles;
			rc = common::listdir( feeds, feeds_dir );
			if ( rc == 0 )
			{
				for ( size_t j = 0; j < fxfiles.size(); ++j )
				{
					string f = feeds_dir + feeds[i] + "/" + fxfiles[j];
					convertFeed( f );
				}
			}
		}
	}

	return 0;
}


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


void test()
{
	dir_test();
}

