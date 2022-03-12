#include "Utils.hpp"

std::string					randomfilename( std::string str ) {
	static int a = 1;
	time_t ttime = std::time(0);
	std::string filename(std::to_string(ttime));
	filename.insert(filename.length(), std::to_string(a) + "_" + str);
	a++;
	return (filename);
}

std::string					trimString( std::string str, char c )
{
	for (std::string::iterator it = str.begin(); *it == c; it++) {
        str.erase(it);
        it = str.begin();
    }
    if (*(str.begin()) == c)
        str.erase(str.begin());
    for (std::string::iterator it = str.end() - 1; *it == c; it--) {
        str.erase(it);
    }
	return (str);
}

std::vector< std::string >	StringSplit( std::string str, std::string delimiter ) {
	std::vector<std::string> parts;
	while (str.length() && str.find(delimiter) != std::string::npos) {
		std::string tmp = str.substr(0, str.find(delimiter));
			parts.push_back(tmp);
		str.erase(0, str.find(delimiter) + delimiter.length());
	}
	parts.push_back(str);
	return parts;
}

bool						isHex( char c )
{
	std::string hex("0123456789abcdefABCDEF");
	if (hex.find(c) != std::string::npos) {
		return true;
	}
	return false;
}