#include "ohlcv_fmt.h"
#include <iostream>
#include <fstream>

using namespace std;


string feeds_dir = "/home/data/crypt_data/";

int config();
string trim(std::string str);
bool isspace(char c);
int processFeed();
	
int main()
{
	int rc;

	rc = config();
	if (rc)
	{
		return rc;
	}

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
		value = trim(value);
		if (var.find("feeds_dir") != string::npos)
		{
			feeds_dir = trim(value);
			if (feeds_dir[feeds_dir.size() - 1] != '/')
			{
				feeds_dir.push_back('/');
			}
			cout << feeds_dir.c_str() << endl;
		}
	}

	return 0;
}

int processFeed()
{
	return 0;
}

string trim(std::string str)
{
	// remove trailing white space
	while (!str.empty() && isspace(str.back())) str.pop_back();

	// return residue after leading white space
	std::size_t pos = 0;
	while (pos < str.size() && isspace(str[pos])) ++pos;
	return str.substr(pos);
}

bool isspace(char c)
{
	return ((c == ' ') || (c == '\t'));
}


