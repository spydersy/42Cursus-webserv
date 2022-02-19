#include "SocketInfos.hpp"

SocketInfos::SocketInfos() {
	this->socketFd = -1;
	memset((char *)&(this->socketAddress), 0, sizeof(this->socketAddress));
}

SocketInfos::~SocketInfos() {

}

int		SocketInfos::createSocket () {
	this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketFd == -1) {
		return (-1);
	}
	// if(fcntl(this->socketFd, F_SETFL, O_NONBLOCK) < 0) {
	// 	return (-1);
	// }
	return (0);
}

void	SocketInfos::setSocketAddress ( int port ) {
	this->socketAddress.sin_family = AF_UNSPEC;
	this->socketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	this->socketAddress.sin_port = htons(port);
}

int		SocketInfos::bindSocket () const {
	if (bind(this->socketFd, (struct sockaddr *)&(this->socketAddress), sizeof(this->socketAddress)) == -1) {
		return (-1);
	}
	return (0);
}

int		SocketInfos::listenSocket () const {
	if (listen(this->socketFd, 100) < 0) {
		return (-1);
	}
	return (0);
}

int					SocketInfos::getSocketFd () const {
	return (this->socketFd);
}

struct sockaddr_in	SocketInfos::getSocketAddress () const {
	return (this->socketAddress);
}