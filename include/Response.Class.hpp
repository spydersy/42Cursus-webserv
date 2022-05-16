/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:13 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/26 12:51:10 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSPONSE_CLASS_HPP
#define RSPONSE_CLASS_HPP

#include "./webserv.hpp"
#define RECV_SIZE 4096
#define SEND_SIZE 4096

class Response
{
private:
    int                         _fileFD;
    bool                        _isCGI;
    bool                        _pathIsDir;
    bool                        _HeaderSent;
    size_t                      _SENT;
    size_t                      _FULL_SIZE;
    size_t                      _serverIndex;
    size_t                      _cgiIndex;
    size_t                      _length;
    size_t                      _accessType;
    size_t                      _isLocation;
    Request                     _request;
    MimeTypes                   _MT;
    std::string                 _bodyPath;
    std::string                 _full_path;
    std::string                 _responseBuffer;
    std::string                 _root;
    std::string                 _path;
    std::string                 _method;
    std::string                 _status;
    std::string                 _autoindex;
    std::string                 _connection;
    std::vector<Server>         _server;
    std::vector<std::string>    _indexs;

    void                        pathRedirection(std::string to);
    void                        fillErrorPage( void );
    void                        fillDefaultErrorPage( void );
    void                        fillContentLength( void );
    void                        fillContentType( void );
    void                        fillResponseBuffer( void );
    void                        fillAutoindexPage( void );
    void                        cgi_handler( void );
    bool                        initData( void );
    bool                        check_error_page( void );
    bool                        mustRedirect( void );
    bool                        mustRedirect( std::string );
    bool                        notImplemented( void );
    bool                        methodNotAllowed( void );
    bool                        payloadTooLarge( void );
    bool                        noIndexMatch( void );
    size_t                      getAccessType(std::string PATH);

public:
    Response( std::string FLAG );
    Response( Request REQ, std::vector<Server> SERV );
    Response(Response const &src);
    Response    &operator=( const Response &src );
    ~Response( void );

    int                                     &get_fileFD( void );
    int                                     getServerIndex( void );
    void                                    setHttpVersion( void );
    void                                    setHttpStatus( void );
    void                                    setConnection( void );
    void                                    moveBody(std::string from, std::string to, Request request);
    void                                    set_HeaderSent( bool val );
    bool                                    &get_HeaderSent( void );
    bool                                    isCGI( void );
    bool                                    badRequest( void );
    bool                                    forbiddenRessources( void );
    size_t                                  &get_SENT( void );
    size_t                                  &get_FULL_SIZE( void );
    size_t                                  isLocation( void );
    size_t                                  &get_length( void );
    Request                                 &get_request( void );
    MimeTypes                               &get_MT( void );
    std::string                             &get_full_path( void );
    std::string                             &get_responseBuffer( void );
    std::string                             &get_bodyPath( void );
    std::string                             checkMethods( void );
    std::string                             getConnection( void );
    std::string                             &get_root( void );
    std::vector<Server>                     &get_server( void );
};

#endif
