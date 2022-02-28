/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:13 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/28 15:23:09 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSPONSE_CLASS_HPP
#define RSPONSE_CLASS_HPP

#include "./webserv.hpp"

#define NPOS std::string::npos

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
    ** METHODS : 
    */
    void                setHttpVersion( void );
    int                 getServerIndex();
    void                setHttpStatus( void );
};

#endif
