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

int     main(int argc, char *argv[])
{
    std::vector< Server > servers;
    if (argc > 2)
        errorStream(ARGS_ERR, true, 1);
    else if (argc == 1)
        servers = confParsing(DFLTCONF);
    else
        servers = confParsing(argv[1]);

	// printServer(servers);       // to print all servers
    if (create_servers(servers) == -1)            // to create, bind and listen on sockets
    {
        std::cout << "Creation of servers Failed!" << std::endl;
        return (EXIT_FAILURE);
    }

    // crazy s*****t

    // rfds store file descriptors of sockets to feed to select
    fd_set	rfds;
    // maxfd store last socket fd
	int maxfd = -1;

    // add all sockets to rfds to feed to select
    add_servers(servers, rfds, maxfd);

    /* select allows a program to monitor multiple file descriptors,
       waiting until one or more of the file descriptors become "ready"
       for some class of I/O operation 
    */
    
    // feed all sockets fds to select and wait for an I/O operation on one of the sockets 
    handle_all_servers(servers, rfds, maxfd);
    return (0);
}
