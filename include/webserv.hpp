/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:02:24 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/26 15:07:18 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Server.Class.hpp"
#include <iostream>
#include<stdio.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cctype>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <string.h>
#include <ctime>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../srcs/request/Request.hpp"
#include "../srcs/request/Utils.hpp"
#include "./MimeTypes.Class.hpp"
#include "./Response.Class.hpp"
#include "./autoindex.Class.hpp"

#include "../srcs/request/RequestLexer.hpp"
#include "../servers/servers.hpp"

typedef std::pair<std::string, std::string>		string_pair;

/*
** ALIAS: **********************************************************************
*/
# define NPOS                    std::string::npos
# define GET                     "GET"
# define POST                    "POST"
# define DELETE                  "DELETE"
# define ON                      "on"
# define OFF                     "off"
# define BAD_GATEWAT_FAILURE     21
# define NO_CONTENT_FAILURE      204
# define STDOUT                  1

# define AUTOINDEX               "AUTOINDEX"
# define OK                      "200 OK"
# define OK_UPLOAD               "200 OK"
# define OK_DELETE               "200 OK"
# define NO_CONTENT              "204 No Content"
# define MOVED_PERM              "301 Moved Permanently"
# define BAD_RQST                "400 Bad Request"
# define FORBIDDEN_RQST          "403 Forbidden"
# define NOT_FOUND               "404 Not Found"
# define METHOD_NOT_ALLOWED      "405 Method Not Allowed"
# define REQUEST_TIMEOUT         "408 Request Timeout"
# define PAYLOAD_TOO_LARGE       "413 Payload Too Large"
# define INTERNAL_SERVER_ERROR   "500 Internal Server Error"
# define NOT_IMPLEMENTED         "501 Not Implemented"
# define BAD_GATEWAT             "502 Bad Gateway"
# define SERVICE_UNAVAILABLE     "503 Service Unavailable"

/*
** DEFAULT PAGES: **************************************************************
*/

# define UPLOAD_FILE_SUCCESS        "<html>\n<head><title>200 File Uploaded Successfully</title></head>\n<body>\n<center><h1>200 File Uploaded Successfully</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define DELETE_FILE_SUCCESS        "<html>\n<head><title>200 File Deleted Successfully</title></head>\n<body>\n<center><h1>200 File Deleted Successfully</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define NO_CONTENT_204             "<html>\n<head><title>204 No Content</title></head>\n<body>\n<center><h1>204 No Content</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define BAD_RQST_400               "<html>\n<head><title>400 Bad Request</title></head>\n<body>\n<center><h1>400 Bad Request</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define FORBIDDEN_RQST_403         "<html>\n<head><title>403 Forbidden</title></head>\n<body>\n<center><h1>403 Forbidden</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define NOT_FOUND_404              "<html>\n<head><title>404 Not Found</title></head>\n<body>\n<center><h1>404 Not Found</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define METHOD_NOT_ALLOWED_405     "<html>\n<head><title>405 Method Not Allowed</title></head>\n<body>\n<center><h1>405 Method Not Allowed</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define REQUEST_TIMEOUT_408        "<html>\n<head><title>408 Request Timeout</title></head>\n<body>\n<center><h1>408 Request Timeout</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define PAYLOAD_TOO_LARGE_413      "<html>\n<head><title>413 Payload Too Large</title></head>\n<body>\n<center><h1>413 Payload Too Large</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define INTERNAL_SERVER_ERROR_500  "<html>\n<head><title>500 Internal Server Error</title></head>\n<body>\n<center><h1>500 Internal Server Error</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define NOT_IMPLEMENTED_501        "<html>\n<head><title>501 Method Not Implemented</title></head>\n<body>\n<center><h1>501 Method Not Implemented</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define BAD_GATEWAT_502            "<html>\n<head><title>502 Bad Gateway</title></head>\n<body>\n<center><h1>502 Bad Gateway</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"
# define SERVICE_UNAVAILABLE_503    "<html>\n<head><title>503 Service Unavailable</title></head>\n<body>\n<center><h1>503 Service Unavailable</h1></center>\n<hr><center>webserv</center>\n</body>\n</html>\n"

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
int						read_select (int fd, std::string &buffer, size_t size);
bool                    isEmptyLine(std::string LINE);
void                    OUT_Position(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    SERVER_Position(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    skipSpaces(std::string FILE, std::string::iterator &it);
void                    nextChar(std::string FILE, std::string::iterator &it);
void                    fill_server_name(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_host_port(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_index(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_redirection(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_upload_path(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_cgi_path(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_location_root(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_methods(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_autoindex(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_error_page(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    setData(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
void                    fill_client_body_size(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data);
std::string             getPath(std::string &FILE, std::string::iterator &it);
std::string	            current_time_stamp( void );
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
