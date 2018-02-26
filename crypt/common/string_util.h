/*-------------------------------------------------------------------------------
 * string_util.h: String processing utility functions
 *
 */
#ifndef __CRYPT_STRING_H__
#define __CRYPT_STRING_H__

#include <iostream>

using namespace std;


namespace common
{

extern string trim(std::string str);
extern bool isspace(char c);


}


#endif
