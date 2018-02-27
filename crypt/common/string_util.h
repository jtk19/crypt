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

/** @brief Removes leading and trailing white spaces in str */
extern string trim( string str);

extern string tolowers( string str );

extern bool isspace( char c);

/** @brief Returns whether str contains s1 independent of upper or lower case */
inline bool contains( string str, string s1 )
{
	str = common::tolowers(str);
	s1 = common::tolowers(s1);
	return ( str.find(s1) != string::npos );
}

/** @brief Replaces multiple instances of tgt with rep in str. */
extern string strrep( string str, string tgt, string rep );
/** @brief Replaces the first instances of tgt with rep in str. */
extern string strrep1( string str, string tgt, string rep );

}


#endif
