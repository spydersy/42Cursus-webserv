#include "Client.hpp"

Client::Client() {
	this->clientFd = -1;
	memset((char *)&(this->clientAddress), 0, sizeof(this->clientAddress));
}

Client::~Client() {

}

int					&Client::getClientFd () {
	return (this->clientFd);
}

struct sockaddr_in	&Client::getClientAddress () {
	return (this->clientAddress);
}