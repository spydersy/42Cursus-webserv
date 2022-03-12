/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:02:24 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/11 21:22:32 by abelarif         ###   ########.fr       */
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
#include <sys/stat.h>

#include "../srcs/request/Request.hpp"
#include "../srcs/request/Utils.hpp"
#include "./MimeTypes.Class.hpp"
#include "./Response.Class.hpp"
#include "./autoindex.Class.hpp"

#include "../srcs/request/RequestLexer.hpp"
#include "../servers/servers.hpp"


/*
** ALIAS: **********************************************************************
*/
#define NPOS                    std::string::npos
#define GET                     "GET"
#define POST                    "POST"
#define DELETE                  "DELETE"
#define ON                      "on"
#define OFF                     "off"
#define BAD_RQST                "400 Bad Request"
#define FORBIDDEN_RQST          "403 Forbidden"
#define NOT_FOUND               "404 Not Found"
#define METHOD_NOT_ALLOWED      "405 Method Not Allowed"
#define NOT_IMPLEMENTED         "501 Not Implemented"
#define SERVICE_UNAVAILABLE     "503 Service Unavailable"
#define OK                      "200 OK"

/*
** DEFAULT PAGES: **************************************************************
*/

#define BAD_RQST_400               "<html> \r\n<head><title>Webserv 400: Bad Request</title></head> \r\n<body> \r\n<center><h1>Webserv 400: Bad Request</h1></center> \r\n"
#define FORBIDDEN_RQST_403         "<html> \r\n<head><title>Webserv 403: Forbidden</title></head> \r\n<body> \r\n<center><h1>Webserv 403: Forbidden</h1></center> \r\n"
#define NOT_FOUND_404              "<html> \r\n<head><title>Webserv 404: Not Found</title></head> \r\n<body> \r\n<center><h1>Webserv 404: Not Found</h1></center> \r\n"
#define METHOD_NOT_ALLOWED_405     "<html> \r\n<head><title>Webserv 405: Method Not Allowed</title></head> \r\n<body> \r\n<center><h1>Webserv 405: Method Not Allowed</h1></center> \r\n"
#define NOT_IMPLEMENTED_501        "<html> \r\n<head><title>Webserv 501: Not Implemented</title></head> \r\n<body> \r\n<center><h1>Webserv 501: Not Implemented</h1></center> \r\n"
#define SERVICE_UNAVAILABLE_503    "<html> \r\n<head><title>Webserv 503: Service Unavailable</title></head> \r\n<body> \r\n<center><h1>Webserv 503: Service Unavailable</h1></center> \r\n"

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
// void    responseHandler(std::vector< std::pair< Client, Request > > &clieent,);
/*
** GLOBAL VARIABLES: ***********************************************************
*/


#endif
