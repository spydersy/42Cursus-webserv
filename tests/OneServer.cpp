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
#include "request/Request.hpp"

std::string randomfilename(std::string str) {
	static int a = 1;
	time_t ttime = std::time(0);
	std::string filename(std::to_string(ttime));
	filename.insert(filename.length(), std::to_string(a));
	a++;
	return (filename);
}

void	initialize_address(struct sockaddr_in &address, char *port) {
	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_UNSPEC;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(std::stoi(port));
}

Request	read_request(int &newSockfd) {
	Request				rqst;
	int					recvLength = 1024;								// length received in request
	char				buffer[1024];									// request reading buffer
	std::string			filename = "/var/tmp/request_" + randomfilename("");
	std::ofstream		rqstFile(filename);
	// std::ofstream		requestFile(requestFilename, std::ofstream::out);
	std::cout << "Receiving:" << std::endl;
	while ((recvLength = recv(newSockfd, &buffer, 1024, 0)) == 1024) {
		buffer[recvLength] = '\0';
		rqstFile << buffer;
	}
	buffer[recvLength] = '\0';
	rqstFile << buffer;
	remove(filename.c_str());
	return rqst;
}

void	send_simple_response(int &newSockfd)
{
	std::string str_send = "HTTP/1.1 200 OK\nServer: Test Server\nContent-Type: text/plain\nContent-Length: 7\n\nHello!\n";
	send(newSockfd, str_send.c_str(), strlen(str_send.c_str()), 0);
}

int main (int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " [PORT]" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		int					sockfd;											// server socket FD
		int					newSockfd;										// new connection FD
		struct sockaddr_in	address;										// server configuration
		struct sockaddr_in	connAddress;									// new connection configuration
		
		// creation of socket
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd <= 0) {
			std::cerr << "Socket Creation Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}

		// initialize address
		initialize_address(address, argv[1]);

		if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
			std::cerr << "Bind Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}

		// listen on socket
		if (listen(sockfd, 5) < 0) {
			std::cerr << "Listen Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}

		while (true) {
			std::cout << "Waiting for connection on port " << argv[1] << "..." << std::endl;

			socklen_t stor_size = sizeof(struct sockaddr_in);
			newSockfd = accept(sockfd, (struct sockaddr *)&connAddress, &stor_size);
			if (newSockfd < 0) {
				std::cerr << "Accepting Connection Failed!" << std::endl;
				exit(EXIT_FAILURE);
			}
			Request rqst = read_request(newSockfd);						// read request
			send_simple_response(newSockfd);							// to prevent multi request from mozilla
			// remove(filename.c_str());
			std::cout << "End Reading!" << std::endl;
			close(newSockfd);
		}
	}
}