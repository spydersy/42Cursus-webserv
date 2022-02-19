#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <string>
#include "../servers/Socket.hpp"
#define MAX_SERVERS 1
#define PORT 8000

std::vector< std::string >		StringSplit( std::string str, std::string delimiter );
std::vector< Socket >			create_multiple_servers();
std::string						getfilename( std::string str );
#endif