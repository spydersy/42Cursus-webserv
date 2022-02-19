#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <string>

// #define HEADERS "Accept,Accept-Charset,Accept-Encoding,Accept-Language,
// Authorization,Expect,From,Host,If-Match,If-Modified-Since,
// If-None-Match,If-Range,If-Unmodified-Since,Max-Forwards,
// Proxy-Authorization,Range,Referer,TE,User-Agent,Connection"

std::vector<std::string>    StringSplit( std::string str, std::string delimiter );
// bool                        checkHeaders( std::string header );
#endif