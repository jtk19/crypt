#include "string_util.h"


string common::trim(std::string str)
{
	// remove trailing white space
	while (!str.empty() && isspace(str.back())) str.pop_back();

	// return residue after leading white space
	std::size_t pos = 0;
	while (pos < str.size() && isspace(str[pos])) ++pos;
	return str.substr(pos);
}

bool common::isspace(char c)
{
	return ((c == ' ') || (c == '\t'));
}

