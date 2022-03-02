#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <fcntl.h>

class SocketInfos {
	private:
		int					socketFd;
		struct sockaddr_in	socketAddress;
	public:
		SocketInfos();
		~SocketInfos();

		int		createSocket ();
		void	setSocketAddress ( int port );
		int		bindSocket () const;
		int		listenSocket () const;

		// Getters
		int					&getSocketFd ();
		struct sockaddr_in	&getSocketAddress ();
};

#endif