#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

class Client
{
	private:
		int					clientFd;
		struct sockaddr_in	clientAddress;
	public:
		Client();
		~Client();

		// Getters
		struct sockaddr_in	&getClientAddress ();
		int					&getClientFd ();
};

#endif