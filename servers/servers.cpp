#include "servers.hpp"

/*
 * This Function  create sockets for servers, set them to non-block mood,
 * configure the port, bind them and listen
 */

/*
 * getClientResponse() function :***********************************************************
 */

Response getClientResponse(Request clientReq, Servers &servers)
{
	if (clientReq.getPath().length() && servers.size()) {}
	return Response(clientReq, servers);
}

/*
 * This Function  create sockets for servers, set them to non-block mood,
 * configure the port, bind them and listen
 */

int		create_servers( std::vector< Server > &servers ) {
	std::vector<int>    bound;
	for (Servers::iterator it = servers.begin(); it != servers.end(); it++) {
		// Create Socket
		if (it->get_socketInfos().createSocket() == -1) {
			perror("Socket");
			return (-1);
		}
		fcntl(it->get_socketInfos().createSocket(), F_SETFL, O_NONBLOCK);
		// set Socket Address
		it->get_socketInfos().setSocketAddress(it->get_port(), it->get_host());

		// test if the socket is already bound to prevent bind failure
		if (find(bound.begin(), bound.end(), it->get_port()) == bound.end()) {
			// Bind Socket if not already bound
			if(it->get_socketInfos().bindSocket() == -1) {
				perror("Bind");
				return (-1);
			}
			else {
				bound.push_back(it->get_port());
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

void	add_servers( Servers &servers, fd_set &rfds, int &maxfd ) {
	// to clear/remove all file descriptors from the the set rfds
	FD_ZERO(&rfds);

	// iterate all servers and add file descriptor to rfds set with FD_SET
	for (Servers::iterator it = servers.begin(); it != servers.end(); it++) {
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

void	accept_connection( ClientRequest &read_clients, int &fd )
{
	// New Connection configuration
	socklen_t	stor_size = sizeof(struct sockaddr_in);
	Client		clt;

	clt.getClientFd() = accept(fd, (struct sockaddr *)&(clt.getClientAddress()), &stor_size);
	// protection for accept
	if (clt.getClientFd() < 0) {
		std::cerr << "Accepting Connection Failed!" << std::endl;
	}
	else {
		fcntl(clt.getClientFd(), F_SETFL, O_NONBLOCK);
		read_clients.push_back(std::make_pair< Client, Request >(clt, Request()));
	}
}

/*
 * loop over all servers fds after select return fds are ready for read
 * to see which fd is ready for accepting connection using FD_ISSET
 */

void	accept_connections( Servers &servers, ClientRequest &read_clients, fd_set &backup_rset ) {

	for (Servers::iterator it = servers.begin(); it != servers.end(); it++) {
		if (FD_ISSET(it->get_socketInfos().getSocketFd(), &backup_rset) ){
			accept_connection(read_clients, it->get_socketInfos().getSocketFd());
		}
	}
}

void	add_read_clients( ClientRequest &clients, fd_set &rset, int &maxfd )
{
	for (ClientRequest::iterator it = clients.begin(); it != clients.end(); it++) {
		FD_SET(it->first.getClientFd(), &rset);
		if (it->first.getClientFd() > maxfd)
			maxfd = it->first.getClientFd();
	}
}

void	add_write_clients( ClientResponse &clients, fd_set &wset, int &maxfd )
{
	for (ClientResponse::iterator it = clients.begin(); it != clients.end(); it++) {
		FD_SET(it->first.getClientFd(), &wset);
		if (it->first.getClientFd() > maxfd)
			maxfd = it->first.getClientFd();
	}
}

void	handle_clients_requests( ClientRequest &read_clients, ClientResponse &write_clients, fd_set &backup_rset, Servers &servers) {
	char										buffer[RECV_SIZE + 1];	// buffer for read
	int											recvLength = 0;
	int											end_rqst = 0;

	for(ClientRequest::iterator it = read_clients.begin(); it != read_clients.end(); it++) {
		if (FD_ISSET(it->first.getClientFd(), &backup_rset)) {
			// read_request and add it to the propre on
			memset(buffer, '\0', RECV_SIZE);
			if ((recvLength = recv(it->first.getClientFd(), buffer, RECV_SIZE, 0)) > 0) {
				buffer[recvLength] = '\0';
				// if the request is finished add fd to writing list
				end_rqst = it->second.add_buffer(recvLength, buffer);
				if (end_rqst == FINISHED) {
					it->second.Lexer_to_parser();
					// Handle request
					Response clientRes = getClientResponse(it->second, servers);
					write_clients.push_back(std::make_pair(it->first, clientRes));
					// remove it from the read list
					std::vector<std::pair<Client, Request> >::iterator tmpIt = it - 1;
					read_clients.erase(it);
					it = tmpIt;
				}
				else if (end_rqst == BAD_REQUEST) {
					// ADD BAD REQUEST RESPONSE
					write_clients.push_back(std::make_pair(it->first, Response(BAD_RQST)));
					std::vector<std::pair<Client, Request> >::iterator tmpIt = it - 1;
					read_clients.erase(it);
					it = tmpIt;
				}
			}
			else if (recvLength == -1){
				// remove it from the read list
				std::vector<std::pair<Client, Request> >::iterator tmpIt = it - 1;
				read_clients.erase(it);
				it = tmpIt;
			}
		}
	}
}

int	send_response(int newSockfd, Response &response)
{
    int		ret;

	std::string res = response.get_responseBuffer();
	signal(SIGPIPE, SIG_IGN);
	ret = send(newSockfd, res.c_str(), res.length(), 0);
	if (ret == -1)
		return -1;
	signal(SIGPIPE, SIG_DFL);
	if (response.get_SENT() == response.get_FULL_SIZE())
		return 1;
	return 0;
}

void	close_connection( ClientResponse::iterator &it, ClientRequest &read_clients ) {
	if (it->second.getConnection() == "keep-alive") {
		read_clients.push_back(std::make_pair< Client, Request >(Client(it->first), Request()));
	}
	else {
		close(it->first.getClientFd());
	}
}

void	handle_clients_responses(ClientResponse &write_clients, ClientRequest &read_clients, fd_set &backup_wset)
{
	for (ClientResponse::iterator it = write_clients.begin(); it != write_clients.end(); it++)
	{

		if (FD_ISSET(it->first.getClientFd(), &backup_wset))
		{

			int DONE = send_response(it->first.getClientFd(), it->second);
			if (DONE == -1) {
				// remove it from the read list
				std::vector<std::pair<Client, Response> >::iterator tmpIt = it - 1;
				write_clients.erase(it);
				it = tmpIt;
			}
			else if (DONE == 1)
			{
				close(it->second.get_fileFD());
				close_connection(it, read_clients);
				ClientResponse::iterator tmpIt = it - 1;
				write_clients.erase(it);
				it = tmpIt;
			}
			// if the response is finished remove the fd if connection not to keep alive
		}
	}
}

void	handle_all_servers( std::vector<Server> &servers, fd_set &read_fds, fd_set &write_fds, int &maxfd )
{
	ClientRequest	read_clients;
	ClientResponse	write_clients;

	// create another set bcs select is destroys the set feeded
	fd_set	backup_rset, backup_wset;
	unsigned int status;
	while (42)
	{
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
		if (status < 0)
		{
			std::cerr << "Select Failed!" << std::endl;
		}
		// if the fd is between servers fds accept new connection
		accept_connections(servers, read_clients, backup_rset);
		// if the fd is between read_clients fds accept read request
		handle_clients_requests(read_clients, write_clients, backup_rset, servers);
		// if the fd is between write_client fds write response
		handle_clients_responses(write_clients, read_clients, backup_wset);
	}
}