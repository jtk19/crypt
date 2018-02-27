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

/*------------------------------------------------------------------
 * Directory functions.                                              */
extern int listdir( vector<string> &dirEntries, string path );
extern int create_dir( string path );
extern int create_empty_dir( string path );

}


#endif
