/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:13 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/02 01:14:44 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSPONSE_CLASS_HPP
#define RSPONSE_CLASS_HPP

#include "./webserv.hpp"

#define BAD_RQST 400
#define FORBIDDEN_RQST 403

// typedef struct s_defaultPages
// {
//     std::pair<int , std::string>    page[] ;

    
// } t_defaultPages;

/*
    Response Codes Order : 
        01 - 400 bad request
        03 - 403 forbidden
        04 - 200 OK
        05 - ... ...
*/

class Response
{
private:
    Request             _request;
    std::vector<Server> _server;
    MimeTypes           _MT;
    std::string         _responseBuffer;
    size_t              _serverIndex;
    size_t              _isLocation;
    std::string         _root;
    std::string         _path;
    std::string         _method;
    size_t              _status;
    bool                _pathIsDir;
public:
    /*
    ** Constructors && Destructors :
    */
    Response( Request REQ, std::vector<Server> SERV );
    ~Response();
    /*
    ** Getters && Setters :  
    */
    Request             &get_request( void );
    std::vector<Server> &get_server( void );
    MimeTypes           &get_MT( void );
    std::string         &get_responseBuffer( void );
    /*
    ** SETTERS : 
    */
    void                                    setHttpVersion( void );
    int                                     getServerIndex( void );
    void                                    setHttpStatus( void );
    size_t                                  isLocation( void );
    bool                                    checkMethods( void );
    /*
    ** METHODS :
    */
    bool                                    badRequest();
    bool                                    forbiddenRessources( void );
};

#endif
