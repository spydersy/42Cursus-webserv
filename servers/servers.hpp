#ifndef SERVERS_HPP
#define SERVERS_HPP
#include "../include/webserv.hpp"
#include "Client.hpp"
#define RECV_SIZE 4096

// creation of servers

int				create_servers( std::vector< Server > &servers );
void			add_servers( std::vector<Server> &servers, fd_set &rfds, int &maxfd );
void			add_read_clients( std::vector< std::pair< Client, Request > > &clients, fd_set &rset, int &maxfd );
void			add_write_clients( std::vector< std::pair< Client, Request > > &clients, fd_set &wset, int &maxfd );
void			accept_connection( std::vector< std::pair< Client, Request > > &clients, int &fd );
void			handle_all_servers( std::vector<Server> &servers, fd_set &read_fds, fd_set &write_fds, int &maxfd );

#endif