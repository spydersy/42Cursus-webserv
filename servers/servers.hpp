#ifndef SERVERS_HPP
#define SERVERS_HPP
#include "../include/webserv.hpp"

// creation of servers

int				create_servers( std::vector< Server > &servers );
void			add_servers( std::vector<Server> &servers, fd_set &rfds, int &maxfd );
void			add_clients( std::vector<int> &clients, fd_set &rset, int &maxfd );
void			accept_connection( std::vector<int> &clients, int &fd );
void			handle_all_servers( std::vector<Server> &servers, fd_set &rfds, int &maxfd );

#endif