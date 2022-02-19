#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstdio>
#include <fcntl.h>
#include "request/Request.hpp"
#include "servers/SocketInfos.hpp"

#define MAX_SERVERS 10
#define PORT 8000

std::string getfilename(std::string str) {
	static int a = 1;
	time_t ttime = std::time(0);
	std::string filename(std::to_string(ttime));
	filename.insert(filename.length(), std::to_string(a));
	a++;
	return (filename);
}

Request	read_request(int &newSockfd) {
	Request				rqst;
	int					recvLength = 1024;								// length received in request
	char				buffer[1024];									// request reading buffer
	std::string			filename = "/var/tmp/request_" + getfilename("");
	std::ofstream		rqstFile(filename, std::ofstream::out);
	std::cout << "Receiving:" << std::endl;
	while ((recvLength = recv(newSockfd, &buffer, 1024, 0)) == 1024) {
		buffer[recvLength] = '\0';
		rqstFile << buffer;
	}
	buffer[recvLength] = '\0';
	rqstFile << buffer;
	std::cout << filename << "\n";
	remove(filename.c_str());
	return rqst;
}

void	send_simple_response(int &newSockfd)
{
	std::string str_send = "HTTP/1.1 200 OK\nServer: Test Server\nContent-Type: text/plain\nContent-Length: 7\n\nHello!\n";
	send(newSockfd, str_send.c_str(), strlen(str_send.c_str()), 0);
}

std::vector<SocketInfos>		create_multiple_servers()
{
	std::vector<SocketInfos>		servers;
	for (int i = 0; i < MAX_SERVERS; i++)
	{
		SocketInfos	serv;
		
		// creation of socket
		if (serv.createSocket() < 0) {
			perror("Socket");
			exit(EXIT_FAILURE);
		}

		// initialize address
		serv.setSocketAddress(PORT + (i * 100));

		if (serv.bindSocket() == -1) {
			perror("Bind");
			exit(EXIT_FAILURE);
		}

		// listen on socket
		if (serv.listenSocket() == -1) {
			perror("Listen");
			exit(EXIT_FAILURE);
		}
		servers.push_back(serv);
	}
	return servers;
}

void	handle_request(int newSockfd)
{
	Request rqst = read_request(newSockfd);						// read request
	send_simple_response(newSockfd);							// to prevent multi request from mozilla
	std::cout << "End Reading!" << std::endl;
	close(newSockfd);
}

int main () {
	std::vector<SocketInfos>	servers = create_multiple_servers();
	int					sockfd;											// server socket FD
	int					newSockfd;										// new connection FD										// server configuration
	struct sockaddr_in	connAddress;
	socklen_t stor_size = sizeof(struct sockaddr_in);

	fd_set	rfds, rset;
	int maxfd = -1, fd = -1;
	unsigned int i, status;
	FD_ZERO(&rfds);
	for (std::vector<SocketInfos>::iterator it = servers.begin(); it != servers.end(); it++) {
		FD_SET((*it).getSocketFd(), &rfds);
		if ((*it).getSocketFd() > maxfd)
			maxfd = (*it).getSocketFd();
	}
	while (true) {
		rset = rfds;
		status = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (status < 0) {
			std::cerr << "Select Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < servers.size(); i++) {
			if (FD_ISSET(servers[i].getSocketFd(), &rset)) {
				fd = servers[i].getSocketFd();
				break ;
			}
		}
		if (fd == -1) {
			std::cerr << "No Connection Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}
		else {
			newSockfd = accept(fd, (struct sockaddr *)&connAddress, &stor_size);
			if (newSockfd < 0) {
				std::cerr << "Accepting Connection Failed!" << std::endl;
				exit(EXIT_FAILURE);
			}
			handle_request(newSockfd);
		}
	}
}
