#include "Utils.hpp"

std::vector<std::string>    StringSplit( std::string str, std::string delimiter ) {
	std::vector<std::string> parts;
	while (str.length() && str.find(delimiter) != std::string::npos) {
		std::string tmp = str.substr(0, str.find(delimiter));
			parts.push_back(tmp);
		str.erase(0, str.find(delimiter) + 1);
	}
	parts.push_back(str);
	return parts;
}


// bool                        checkHeaders( std::string header ) {
// 	header = header.substr(0, header.find(": "));
// 	std::vector< std::string > baseHeaders = StringSplit(HEADERS, ",");

// 	for (std::vector< std::string >::iterator it = baseHeaders.begin(); it != baseHeaders.end(); it++) {
// 		if (header == *it) {
// 			return true;
// 		}
// 	}
// 	return false;
// }