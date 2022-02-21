#include "../include/webserv.hpp"
#include "SocketInfos.hpp"

int		create_servers( std::vector< Server > &servers ) {
	std::vector<int>    bound;
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
		// Create Socket
		if ((*it).get_socketInfos().createSocket() == -1) {
			perror("Socket");
			return (-1);
		}

		// set Socket Address
		(*it).get_socketInfos().setSocketAddress((*it).get_port());

		if (find(bound.begin(), bound.end(), (*it).get_port()) == bound.end()) {
			// Bind Socket if not already bound
			if((*it).get_socketInfos().bindSocket() == -1) {
				perror("Bind");
				return (-1);
			}
		}

		// Listen on socket
		if ((*it).get_socketInfos().listenSocket() == -1) {
			perror("Listen");
			return (-1);
		}
	}
	return (0);
}

void	addFds( std::vector<Server> &servers, fd_set &rfds, int &maxfd ) {
	FD_ZERO(&rfds);
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
		FD_SET((*it).get_socketInfos().getSocketFd(), &rfds);
		if ((*it).get_socketInfos().getSocketFd() > maxfd)
			maxfd = (*it).get_socketInfos().getSocketFd();
	}
}

std::string getfilename() {
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
	std::string			filename = "/var/tmp/request_" + getfilename();
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

void	handle_request(int newSockfd)
{
	Request rqst = read_request(newSockfd);						// read request
	send_simple_response(newSockfd);							// to prevent multi request from mozilla
	std::cout << "End Reading!" << std::endl;
	close(newSockfd);
}

void	handle_all_servers( std::vector<Server> &servers, fd_set &rfds, int &maxfd ) {
	int					newSockfd;										// new connection FD										// server configuration
	struct sockaddr_in	connAddress;
	socklen_t stor_size = sizeof(struct sockaddr_in);
	
	fd_set	rset = rfds;
	int		fd = -1;
	unsigned int status;

	while (true) {
		rset = rfds;
		status = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (status < 0) {
			std::cerr << "Select Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}
		for (unsigned int i = 0; i < servers.size(); i++) {
			if (FD_ISSET(servers[i].get_socketInfos().getSocketFd(), &rset)) {
				fd = servers[i].get_socketInfos().getSocketFd();
				break ;
			}
		}
		if (fd == -1) {
			std::cerr << "No Connection Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}
		else {
			newSockfd = accept(fd, (struct sockaddr *)&connAddress, &stor_size);
			fcntl(newSockfd, F_SETFL, O_NONBLOCK);
            if (newSockfd < 0) {
				std::cerr << "Accepting Connection Failed!" << std::endl;
				exit(EXIT_FAILURE);
			}
			handle_request(newSockfd);
		}
	}
}