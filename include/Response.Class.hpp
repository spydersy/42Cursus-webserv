/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:13 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/06 16:35:27 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSPONSE_CLASS_HPP
#define RSPONSE_CLASS_HPP

#include "./webserv.hpp"

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
    std::string         _status;
    bool                _pathIsDir;
    size_t              getAccessType(std::string PATH);
    void                fillDefaultPage( void );
    bool                serviceUnavailable();
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
