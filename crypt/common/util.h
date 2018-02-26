/*-------------------------------------------------------------------------------
 * util.h: varous utility functions
 *
 */
#ifndef __CRYPT_UTIL_H__
#define __CRYPT_UTIL_H__

#include <iostream>
#include <vector>


using namespace std;


namespace common
{

extern int listdir( vector<string> &dirEntries, string path );

}


#endif
