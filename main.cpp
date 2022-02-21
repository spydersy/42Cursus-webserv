/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:54:12 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/13 09:30:12 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/webserv.hpp"

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

int     main(int argc, char *argv[])
{
    std::vector< Server > servers;
    if (argc > 2)
        errorStream(ARGS_ERR, true, 1);
    else if (argc == 1)
        servers = confParsing(DFLTCONF);
    else
        servers = confParsing(argv[1]);
    printServer(servers);       // to print all servers
    // if (create_servers(servers) == -1)            // to create and lunch sockets
    // {
    //     std::cout << "Creation of servers Failed!" << std::endl;
    //     return (EXIT_FAILURE);
    // }

    // crazy s*****t
	// int					newSockfd;										// new connection FD										// server configuration
	// struct sockaddr_in	connAddress;
	// socklen_t stor_size = sizeof(struct sockaddr_in);

    // fd_set	rfds, rset;
	// int maxfd = -1, fd = -1;
	// unsigned int i, status;
	// FD_ZERO(&rfds);

    // for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
	// 	FD_SET((*it).get_socketInfos().getSocketFd(), &rfds);
	// 	if ((*it).get_socketInfos().getSocketFd() > maxfd)
	// 		maxfd = (*it).get_socketInfos().getSocketFd();
	// }

    // while (true) {
	// 	rset = rfds;
	// 	status = select(maxfd + 1, &rset, NULL, NULL, NULL);
	// 	if (status < 0) {
	// 		std::cerr << "Select Failed!" << std::endl;
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	for (i = 0; i < servers.size(); i++) {
	// 		if (FD_ISSET(servers[i].get_socketInfos().getSocketFd(), &rset)) {
	// 			fd = servers[i].get_socketInfos().getSocketFd();
	// 			break ;
	// 		}
	// 	}
	// 	if (fd == -1) {
	// 		std::cerr << "No Connection Failed!" << std::endl;
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	else {
	// 		newSockfd = accept(fd, (struct sockaddr *)&connAddress, &stor_size);
	// 		fcntl(newSockfd, F_SETFL, O_NONBLOCK);
    //         if (newSockfd < 0) {
	// 			std::cerr << "Accepting Connection Failed!" << std::endl;
	// 			exit(EXIT_FAILURE);
	// 		}
	// 		handle_request(newSockfd);
	// 	}
	// }
    return (0);
}
