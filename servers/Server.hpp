#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <iostream>

class Server {
	private:
		int     			serverFd;
		int					acceptFd;
		struct sockaddr_in	serverAddress;
		struct sockaddr_in	connAddress;
		char				buffer[1024];
	public:
		Server();
		~Server();
};

#endif