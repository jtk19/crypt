
#include <dirent.h>
#include "util.h"


int common::listdir( vector<string> &dirEntries, string path )
{
	struct dirent *entry;
	DIR *dp;

	dp = opendir(path.c_str());
	if (dp == NULL)
	{
		cerr<< "[listdir()] Directory ["<< path << "] does not exist."<< endl;
		return -1;
	}

	while((entry = readdir(dp)))
	{
		string d( entry->d_name);
		if ( (d != string("."))  &&  (d != string("..")) )
		{
			dirEntries.push_back( d );
		}
	}

	closedir(dp);
	return 0;
}
