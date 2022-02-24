/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:02:24 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/14 04:51:15 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Server.Class.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../srcs/request/Request.hpp"
#include "../srcs/request/Utils.hpp"
#include "./MimeTypes.Class.hpp"
#include "../servers/SocketInfos.hpp"
#include "../srcs/request/RequestLexer.hpp"
#include "../servers/servers.hpp"

/*
** COLORS DEFINITION: **********************************************************
*/
# define KNRM       "\x1B[0m"
# define KRED       "\x1B[31m"
# define KGRN       "\x1B[32m"
# define KYEL       "\x1B[33m"
# define KBLU       "\x1B[34m"
# define KMAG       "\x1B[35m"
# define KCYN       "\x1B[36m"
# define KWHT       "\x1B[37m"

/*
** ERRORS DESCRIPTION: *********************************************************
*/
# define ARGS_ERR       "\nUsage: ./webserv ./CONFIG/FILE/PATH"
# define FORMAT_ERR     "Format insupported"
# define SYNTAX_ERR     "File : Syntax Error"
/*
** ONLY FOR FILE PARSING: ******************************************************
*/
# define     POSITION_OUT         0
# define     POSITION_SERVER      1
# define     POSITION_LOCATION    2
# define     POSITION_CGI         3

/*
** DATA STRUCTRS: **************************************************************
*/



/*
** FUNCTIONS PROTOTYPES: *******************************************************
*/
int     webserv(int argc, char **argv);
/*
** SHARED FUNCTIONS:
*/
// first Argument : String variable That describe the error.
// second Argument: bool variable (if EXIT_FLAG is set to true => the program exit with value) (else => Do nothing).
// third Argument: exit value.
void    errorStream(std::string description, bool EXIT_FLAG, int value);




void    printServer(std::vector<Server> &server);

/*
** PARSING FUNCTIONS:
*/
int                     validatedKeyword(std::string &FILE, std::string::iterator &it);
bool                    isEmptyLine(std::string LINE);
void                    OUT_Position(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    SERVER_Position(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    skipSpaces(std::string FILE, std::string::iterator &it);
void                    nextChar(std::string FILE, std::string::iterator &it);
void                    fill_server_name(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_host_port(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_index(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_location_root(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_location(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_methods(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_autoindex(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    setData(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_client_body_size(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
std::string             getPath(std::string &FILE, std::string::iterator &it);
std::vector<Server>     confParsing(std::string configFILE);


/*
** SERVER FUNCTIONS:
*/
void    server(std::vector<Server> CONF);

/*
** REQUEST FUNCTIONS:
*/
void    requestHandler(std::vector<Server> CONF, std::string buffer, int socketFD);

/*
** RESPONSE FUNCTIONS:
*/
void    responseHandler(std::vector<Server> CONF, Request rqst, int socketFD);

/*
** GLOBAL VARIABLES: ***********************************************************
*/


#endif
