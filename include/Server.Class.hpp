/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.Class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:22:45 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/26 06:12:58 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
#define SERVER_CLASS_HPP

#include "Location.Class.hpp"
#include "CGI.Class.hpp"
#include "webserv.hpp"
#include <iostream>
#include <vector>

/*
** DEFAULT CONFIGFILE: *********************************************************
** No write permission: -r--r--r--  conf/default.conf
*/
# define DFLTCONF   "./conf/default.conf"

#include "../servers/SocketInfos.hpp"

/*
** CONFIGFILE  KEYWORDS: *******************************************************
*/
# define KW_SERVER              "server"
# define KW_SERVER_NAME         "server_name"           //  Server_name
# define KW_ERR_PAGE            "error_page"            //  Default error pages
# define KW_LISTEN              "listen"                //  Listen HOST:PORT
# define KW_CLIENT_BODY_SIZE    "client_max_body_size"  //  Limit client body size
# define KW_ACCEPTED_METHOD     "allow_methods"         //  Define a list of accepeted HTTP Methods
# define KW_AUTOINDEX           "autoindex"             //  Turn on or off directory listing
# define KW_DEFAULT_FILE        "index"                 //  Default file to answer if the request is a directory
# define KW_LOCATION            "location"              //  Define a directory or a file from where the file should be search
# define KW_CGI                 "cgi"                   //
# define KW_LOCATION_ROOT       "root"                  //  The KW_LOCATION is rooted to KW_LOCATION_ROOT
# define KW_REDIRECTION         "redirection"           //  Redireciont from /path to /another_path
# define KW_UPLOAD_PATH         "upload_path"           //
# define KW_CGI_PATH            "cgi_path"              //

# define KW_CLOSED_BRACKET            9000
# define KW_SERVER_VALUE              9001
# define KW_SERVER_NAME_VALUE         9002
# define KW_ERR_PAGE_VALUE            9003
# define KW_CLIENT_BODY_SIZE_VALUE    9004
# define KW_ACCEPTED_METHOD_VALUE     9005
# define KW_AUTOINDEX_VALUE           9006
# define KW_DEFAULT_FILE_VALUE        9007
# define KW_LOCATION_VALUE            9008
# define KW_LOCATION_ROOT_VALUE       9009
# define KW_LISTEN_VALUE              9010
# define KW_REDIRECTION_VALUE         9011
# define KW_UPLOAD_PATH_VALUE         9012
# define KW_CGI_VALUE                 9013
# define KW_CGI_PATH_VALUE            9014

class ServerData
{
public:
    int                                                 whereAmI;
    std::pair<std::vector<bool>, std::vector<bool> >    Bracket;
    ServerData(int POSITION) : whereAmI(POSITION) {}
    ~ServerData() {}
};

class Server
{
private:
    std::vector<std::string>                            _server_names;
    std::string                                         _host;
    size_t                                              _port;
    std::string                                         _root;
    std::vector<std::string>                            _index;
    std::vector<std::string>                            _methods;
    std::vector<Location>                               _location;
    std::vector<CGI>                                    _CGI;
    std::string                                         _client_max_body_size;
    std::string                                         _autoindex;
    const std::string                                   _whoAmI;
    SocketInfos					                        _socketInfos;
    std::vector<std::pair<std::string, std::string> >   _redirections;
    std::vector<std::pair<std::string, std::string> >   _error_pages;
    std::string                                         _upload_path;

public:

    bool    operator==(const Server & rhs) const
    {
        return (
            (_server_names == rhs._server_names) &&
            (_host == rhs._host) &&
            (_port == rhs._port));
    }

    Server( void );
    Server      &operator= ( const Server & srv );
    ~Server();

    //  GETTERS :
    std::vector<std::string>                            &get_server_names();
    std::string                                         &get_host();
    size_t                                              &get_port();
    std::string                                         &get_root();
    std::string                                         &get_client_max_body_size();
    std::vector<std::string>                            &get_index();
    std::vector<std::string>                            &get_methods();
    std::vector<Location>                               &get_location();
    std::vector<CGI>                                    &get_CGI();
    std::string                                         &get_autoindex();
    std::string                                         getId() const ;
    SocketInfos					                        &get_socketInfos();
    std::vector<std::pair<std::string, std::string> >   &get_error_pages();
    std::vector<std::pair<std::string, std::string> >   &get_redirections();
    std::string                                         &get_upload_path();

    //  METHODS:
    bool    setHostPort();
    void    dbgServer();
};

#endif
