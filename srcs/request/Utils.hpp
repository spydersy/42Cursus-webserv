#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>
#include "../../servers/SocketInfos.hpp"

std::vector< std::string >		StringSplit( std::string str, std::string delimiter );
std::vector< SocketInfos >		create_multiple_servers();
std::string						randomfilename( std::string str );
std::string						trimString( std::string str, char c );
bool                            isHex( char c );
int 							write_select (int fd, std::string &buffer, size_t size);
int						        read_select (int fd, std::string &buffer, size_t size);

#endif
