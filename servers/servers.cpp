#include "servers.hpp"

/*
 * This Function  create sockets for servers, set them to non-block mood,
 * configure the port, bind them and listen
 */

int		create_servers( std::vector< Server > &servers ) {
	std::vector<int>    bound;
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
		// Create Socket
		if (it->get_socketInfos().createSocket() == -1) {
			perror("Socket");
			return (-1);
		}
		fcntl(it->get_socketInfos().createSocket(), F_SETFL, O_NONBLOCK);
		// set Socket Address
		it->get_socketInfos().setSocketAddress(it->get_port());

		// test if the socket is already bound to prevent bind failure
		if (find(bound.begin(), bound.end(), it->get_port()) == bound.end()) {
			// Bind Socket if not already bound
			if(it->get_socketInfos().bindSocket() == -1) {
				perror("Bind");
				return (-1);
			}
		}

		// Listen on socket
		if (it->get_socketInfos().listenSocket() == -1) {
			perror("Listen");
			return (-1);
		}
	}
	return (0);
}

/*
 * This Function add all lunched servers to the select read_set
 */
void	add_servers( std::vector<Server> &servers, fd_set &rfds, int &maxfd ) {
	// to remove all file descriptors from the the set rfds
	FD_ZERO(&rfds);

	// iterate all servers and add file descriptor to rfds set with FD_SET
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
		FD_SET(it->get_socketInfos().getSocketFd(), &rfds);

		// test for max fd
		if (it->get_socketInfos().getSocketFd() > maxfd)
			maxfd = it->get_socketInfos().getSocketFd();
	}
}

/*
 * Accept a connection on a server add new client
 * and mapped request to the read_client vector
 */

void	accept_connection( std::vector< std::pair< Client, Request > > &read_clients, int &fd )
{
	// New Connection configuration
	socklen_t	stor_size = sizeof(struct sockaddr_in);
	Client		clt;
	Request		 rqst;

	clt.getClientFd() = accept(fd, (struct sockaddr *)&(clt.getClientAddress()), &stor_size);
	// protection for accept
	if (clt.getClientFd() < 0) {
		std::cerr << "Accepting Connection Failed!" << std::endl;
	}
	fcntl(clt.getClientFd(), F_SETFL, O_NONBLOCK);		// check if this is the right place
	read_clients.push_back(std::make_pair< Client, Request >(clt, rqst));
}

/*
 * loop over all servers fds after select return fds are ready for read
 * to see which fd is ready for accepting connection using FD_ISSET
 */

void	accept_connections( std::vector<Server> &servers, std::vector< std::pair< Client, Request > > &read_clients, fd_set &backup_rset ) {

	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
		if (FD_ISSET(it->get_socketInfos().getSocketFd(), &backup_rset) ) {
			accept_connection(read_clients, it->get_socketInfos().getSocketFd());
		}
	}
}

void	add_read_clients( std::vector< std::pair< Client, Request > > &clients, fd_set &rset, int &maxfd )
{
	for (std::vector< std::pair< Client, Request > >::iterator it = clients.begin(); it != clients.end(); it++) {
		FD_SET(it->first.getClientFd(), &rset);
		if (it->first.getClientFd() > maxfd)
			maxfd = it->first.getClientFd();
	}
}

void	add_write_clients( std::vector< std::pair< Client, Request > > &clients, fd_set &wset, int &maxfd )
{
	for (std::vector< std::pair< Client, Request > >::iterator it = clients.begin(); it != clients.end(); it++) {
		FD_SET(it->first.getClientFd(), &wset);
		if (it->first.getClientFd() > maxfd)
			maxfd = it->first.getClientFd();
	}
}

void	handle_clients_requests( std::vector< std::pair< Client, Request > > &read_clients,
		std::vector< std::pair< Client, Request > > &write_clients, fd_set &backup_rset) {
	// static int o = 0;
	char										buffer[RECV_SIZE + 1];	// buffer for read
	int											recvLength = 0;
	for(std::vector< std::pair< Client, Request > >::iterator it = read_clients.begin(); it != read_clients.end(); it++) {
		if (FD_ISSET(it->first.getClientFd(), &backup_rset)) {
			// read_request and add it to the propre on
			memset(buffer, '\0', RECV_SIZE);
			if ((recvLength = recv(it->first.getClientFd(), buffer, RECV_SIZE, 0)) != -1) {
				buffer[recvLength] = '\0';
				// std::cerr << "DATA: " << o++ << std::endl;
				// std::cerr.flush();
				// if the request is finished add fd to writing list
				if (it->second.add_buffer(recvLength, buffer) == true) {
					it->second.Lexer_to_parser();
					// std::cout << it->second;			// printing the request
					write_clients.push_back(std::make_pair(it->first, it->second));
					std::vector< std::pair< Client, Request > >::iterator tmpIt = it - 1;
					read_clients.erase(it);
					it = tmpIt;
				}
			}
		}
	}
}

// just for try
void	send_simple_response(int &newSockfd)
{
	std::string str_send = "HTTP/1.1 200 OK\nServer: Test Server\nContent-Type: text/plain\nContent-Length: 7\n\nHello!\n";
	send(newSockfd, str_send.c_str(), strlen(str_send.c_str()), 0);
}

void	handle_clients_responses(std::vector< std::pair< Client, Request > > &write_clients, fd_set &backup_wset)
{
	for(std::vector< std::pair< Client, Request > >::iterator it = write_clients.begin(); it != write_clients.end(); it++) {
		if (FD_ISSET(it->first.getClientFd(), &backup_wset)) {
			// write part from response
			send_simple_response(it->first.getClientFd());
			close(it->first.getClientFd());
			// if the response is finished remove the fd if connection not to keep alive
			std::vector< std::pair< Client, Request > >::iterator tmpIt = it - 1;
			write_clients.erase(it);
			it = tmpIt;
		}
	}
}

void	handle_all_servers( std::vector<Server> &servers, fd_set &read_fds, fd_set &write_fds, int &maxfd ) {
	std::vector< std::pair< Client, Request > >	read_clients;
	std::vector< std::pair< Client, Request > >	write_clients;

	// create another set bcs select is destroys the set feeded
	fd_set	backup_rset, backup_wset;
	unsigned int status;
	std::cout << "Servers Up..." << std::endl;
	while (true) {
		// initialize fd set
		backup_rset = read_fds;
		backup_wset = write_fds;

		// add reading client socket file descriptors to rset
		add_read_clients(read_clients, backup_rset, maxfd);
		// add reading client socket file descriptors to rset
		add_write_clients(write_clients, backup_wset, maxfd);
		// feed fds to select only for read option
		status = select(maxfd + 1, &backup_rset, &backup_wset, NULL, NULL);
		// protection for select
		if (status < 0) {
			std::cerr << "Select Failed!" << std::endl;
		}
		// if the fd is between servers fds accept new connection
		accept_connections(servers, read_clients, backup_rset);
		// if the fd is between read_clients fds accept read request
		handle_clients_requests(read_clients, write_clients, backup_rset);
		// if the fd is between write_client fds write response
		handle_clients_responses(write_clients, backup_wset);
	}
}