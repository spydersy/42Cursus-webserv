/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:13 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/12 02:38:00 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSPONSE_CLASS_HPP
#define RSPONSE_CLASS_HPP

#include "./webserv.hpp"

class Response
{
private:
    Request                     _request;
    std::vector<Server>         _server;
    MimeTypes                   _MT;
    std::string                 _responseBuffer;
    size_t                      _serverIndex;
    size_t                      _isLocation;
    size_t                      _length;
    std::string                 _root;
    std::string                 _path;
    std::string                 _method;
    std::string                 _status;
    std::vector<std::string>    _indexs;
    std::string                 _autoindex;
    bool                        _pathIsDir;

    size_t                      getAccessType(std::string PATH);
    void                        fillErrorPage( void );
    bool                        serviceUnavailable();
    std::string                 GETmethod();
    void                        fillResponseBuffer( void );
    void                        fillContentType( void );
    void                        fillContentLength( void );
    void                        fillAutoindexPage( void );

public:
    /*
    ** Constructors && Destructors :
    */
    Response( Request REQ, std::vector<Server> SERV );
    Response    &operator=( const Response &src );
    ~Response();
    /*
    ** Getters && Setters :
    */
    Request             &get_request( void );
    size_t              &get_length( void );
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
    std::string                             checkMethods( void );
    /*
    ** METHODS :
    */
    bool                                    badRequest();
    bool                                    forbiddenRessources( void );
};

#endif
