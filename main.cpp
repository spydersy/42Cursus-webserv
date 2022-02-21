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
    if (create_servers(servers) == -1)            // to create and lunch sockets
    {
        std::cout << "Creation of servers Failed!" << std::endl;
        return (EXIT_FAILURE);
    }

    // crazy s*****t

    fd_set	rfds;
	int maxfd = -1;

    addFds(servers, rfds, maxfd);

    handle_all_servers(servers, rfds, maxfd);
    return (0);
}
