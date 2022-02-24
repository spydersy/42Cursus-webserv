#include "servers.hpp"

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

		// test if the socket is already bound to prevent bind failure
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

void	add_servers( std::vector<Server> &servers, fd_set &rfds, int &maxfd ) {
	// to remove all file descriptors from the the set rfds
	FD_ZERO(&rfds);

	// iterate all servers and add file descriptor to rfds set with FD_SET
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
		FD_SET((*it).get_socketInfos().getSocketFd(), &rfds);

		// test for max fd
		if ((*it).get_socketInfos().getSocketFd() > maxfd)
			maxfd = (*it).get_socketInfos().getSocketFd();
	}
}

void	add_clients( std::vector<int> &clients, fd_set &rset, int &maxfd )
{
	for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); it++) {
		FD_SET((*it), &rset);
		if ((*it) > maxfd)
			maxfd = (*it);
	}
}

void	accept_connection( std::vector<int> &clients, int &fd )
{
	// New Connection configuration
	struct sockaddr_in	connAddress;
	socklen_t stor_size = sizeof(struct sockaddr_in);

	int newSockfd = accept(fd, (struct sockaddr *)&connAddress, &stor_size);
	// protection for accept
	if (newSockfd < 0) {
		std::cerr << "Accepting Connection Failed!" << std::endl;
		exit(EXIT_FAILURE);
	}
	// fcntl(newSockfd, F_SETFL, O_NONBLOCK);		// check if this is the right place
	clients.push_back(newSockfd);
}

int		servers_fd( std::vector<Server> &servers, fd_set &rset ) {

	int fd = -1;
	// loop over all fds after select said the a fd is ready for read
	// to see which fd is ready for read using FD_ISSET
	for (unsigned int i = 0; i < servers.size(); i++) {
		if (FD_ISSET(servers[i].get_socketInfos().getSocketFd(), &rset)) {
			fd = servers[i].get_socketInfos().getSocketFd();
			break ;
		}
	}
	return (fd);
}

void	read_request(int &newSockfd) {
	RequestLexer	parser;
	int				recvLength;

	while ((recvLength = recv(newSockfd, &parser.buffer, RECV_SIZE, MSG_DONTWAIT)) > 0) {
		parser.buffer[recvLength] = '\0';
		parser.add_buffer(recvLength);
		if (parser.getLineSet() == false)
			parser.check_requestLine();
		if (parser.getHeadersSet() == false)
			parser.check_headers();
		if (parser.getHeadersSet() == true && parser.getLineSet() == true)
			break ;
	}
	if (parser.getHeaders().find("Content-Length:") != std::string::npos)
	{
		parser.read_content_length(newSockfd);
	}
	else if (parser.getHeaders().find("Transfer-Encoding:") != std::string::npos){
		parser.read_chunked(newSockfd);
	}
	else {
		std::cout << "Nothing" << std::endl;
	}
	if (parser.getRequestLine() != "" && parser.getHeaders() != "") {
		std::cout << "Request Line: " << parser.getRequestLine() << std::endl;
		std::cout << "Headers:\n" << parser.getHeaders() << std::endl;
	}
	// sleep(20);
}

void	send_simple_response(int &newSockfd)
{
	std::string str_send = "HTTP/1.1 200 OK\nServer: Test Server\nContent-Type: text/plain\nContent-Length: 7\n\nHello!\n";
	send(newSockfd, str_send.c_str(), strlen(str_send.c_str()), 0);
}

void	handle_request(int newSockfd)
{
	read_request(newSockfd);									// read request
	send_simple_response(newSockfd);							// to prevent multi request from mozilla
}

void	handle_all_servers( std::vector<Server> &servers, fd_set &rfds, int &maxfd ) {
	std::vector<int>	clients;

	// create another set bcs select is destroys the set feeded
	fd_set	rset;
	int		fd;
	unsigned int status;

	while (true) {
		// initialize fd set
		rset = rfds;

		// add client socket file descriptors to rset
		add_clients(clients, rset, maxfd);
		// feed fds to select only for read option
		status = select(maxfd + 1, &rset, NULL, NULL, NULL);
		// protection for select
		if (status < 0) {
			std::cerr << "Select Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}
		
		if ((fd = servers_fd(servers, rset)) != -1)
		{
			// accept connection and create socket for the connection
			accept_connection(clients, fd);
		}
		for(std::vector<int>::iterator it = clients.begin(); it != clients.end(); it++) {
			if (FD_ISSET((*it), &rset)) {
				handle_request((*it));
				std::vector<int>::iterator tmpIt = it - 1;
				close((*it));
				clients.erase(it);
				it = tmpIt;
				// break ;
			}
		}
	}
}