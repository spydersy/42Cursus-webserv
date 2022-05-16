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
	return (0);
}

void	SocketInfos::setSocketAddress ( int port, std::string host ) {
	this->socketAddress.sin_family = AF_UNSPEC;
	if (host.compare("") == 0) {
		this->socketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	} else {
		if (host.compare("localhost") == 0) {
			host = "127.0.0.1";
		}
		this->socketAddress.sin_addr.s_addr = inet_addr(host.c_str());
	}
	this->socketAddress.sin_port = htons(port);
}

int		SocketInfos::bindSocket () const {
	int one = 1;
	setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	if (bind(this->socketFd, (struct sockaddr *)&(this->socketAddress), sizeof(this->socketAddress)) == -1) {
		return (-1);
	}
	return (0);
}

int		SocketInfos::listenSocket () const {
	if (listen(this->socketFd, SOMAXCONN) < 0) {
		return (-1);
	}
	return (0);
}

int					&SocketInfos::getSocketFd () {
	return (this->socketFd);
}

struct sockaddr_in	&SocketInfos::getSocketAddress () {
	return (this->socketAddress);
}