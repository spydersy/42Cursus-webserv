/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:17:47 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/26 17:55:42 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/webserv.hpp"

/*
** CONSTRUCTORS && DESTRUCTORS : ***********************************************
*/
Response::Response( Request REQ, std::vector<Server> SERV )
{
    this->_server = SERV;
    this->_request = REQ;
    this->_serverIndex = 0;
    this->_cgiIndex = 0;
    this->_isLocation = NPOS;
    this->_isCGI = false;
    this->_responseBuffer = "";
    this->_length = 0;
    this->_accessType = 0;
    this->_full_path = "";
    this->_root = "";
    this->_path = "";
    this->_method = "";
    this->_status = "";
    this->_indexs = std::vector<std::string>();
    this->_autoindex = "";
    this->_pathIsDir = false;
    this->_fileFD = -1;
    this->_SENT = 0;
    this->_HeaderSent = false;
    this->_FULL_SIZE = 0;
    this->_bodyPath = _request.getBodyfilename();

    setHttpVersion();
	setHttpStatus();
    if (this->_request.getContentLength() > 0)
        remove(this->_request.getBodyfilename().c_str());
}

Response::Response( std::string FLAG)
{
    this->_responseBuffer = "";
    this->_serverIndex = 0;
    this->_cgiIndex = 0;
    this->_isLocation = NPOS;
    this->_isCGI = false;
    this->_length = 0;
    this->_accessType = 0;
    this->_full_path = "";
    this->_root = "";
    this->_path = "";
    this->_method = "";
    this->_status = "";
    this->_indexs = std::vector<std::string>();
    this->_autoindex = "";
    this->_pathIsDir = false;
    this->_fileFD = -1;
    this->_SENT = 0;
    this->_FULL_SIZE = 0;
    this->_HeaderSent = false;
    if (FLAG.compare(REQUEST_TIMEOUT) == 0)
    {
        setHttpVersion();
        _status = REQUEST_TIMEOUT;
        fillErrorPage();
    }
    else if (FLAG.compare(BAD_RQST) == 0)
    {
        setHttpVersion();
        _status = BAD_RQST_400;
        fillErrorPage();
    }
    else
        this->~Response();
}

Response::Response( Response const &src)
{
    if (this != &src)
    {
        this->_request = src._request;
        this->_server = src._server;
        this->_MT = src._MT;
        this->_isCGI = src._isCGI;
        this->_responseBuffer = src._responseBuffer;
        this->_serverIndex = src._serverIndex;
        this->_cgiIndex = src._cgiIndex;
        this->_isLocation = src._isLocation;
        this->_length = src._length;
        this->_accessType = src._accessType;
        this->_full_path = src._full_path;
        this->_root = src._root;
        this->_path = src._path;
        this->_method = src._method;
        this->_status = src._status;
        this->_indexs = src._indexs;
        this->_autoindex = src._autoindex;
        this->_pathIsDir = src._pathIsDir;
        this->_fileFD = src._fileFD;
        this->_SENT = src._SENT;
        this->_FULL_SIZE = src._FULL_SIZE;
        this->_HeaderSent = src._HeaderSent;
    }
}

Response::~Response() {}

Response        &Response::operator=( const Response &src ) {
    if (this != &src)
    {
        this->_request = src._request;
        this->_server = src._server;
        this->_MT = src._MT;
        this->_responseBuffer = src._responseBuffer;
        this->_cgiIndex = src._cgiIndex;
        this->_serverIndex = src._serverIndex;
        this->_isLocation = src._isLocation;
        this->_length = src._length;
        this->_isCGI = src._isCGI;
        this->_accessType = src._accessType;
        this->_full_path = src._full_path;
        this->_root = src._root;
        this->_path = src._path;
        this->_method = src._method;
        this->_status = src._status;
        this->_indexs = src._indexs;
        this->_autoindex = src._autoindex;
        this->_pathIsDir = src._pathIsDir;
        this->_fileFD = src._fileFD;
        this->_SENT = src._SENT;
        this->_FULL_SIZE = src._FULL_SIZE;
        this->_HeaderSent = src._HeaderSent;
    }
    return *this;
}

int                 &Response::get_fileFD( void ) { return this->_fileFD; }
void                Response::set_HeaderSent( bool val ) { this->_HeaderSent = val; }
void                Response::setHttpVersion( void ) { _responseBuffer.append("HTTP/1.1 "); }
bool                &Response::get_HeaderSent( void ) { return this->_HeaderSent; }
size_t              &Response::get_SENT( void ){ return this->_SENT; }
size_t              &Response::get_FULL_SIZE( void ){ return this->_FULL_SIZE; }
std::string         &Response::get_full_path( void ) { return  this->_full_path; }
std::string         &Response::get_root( void ) { return this->_root; }
std::vector<Server> &Response::get_server( void ) { return this->_server; }

std::string         &Response::get_responseBuffer( void )
{
    int         retRead = 0;

    if (this->_SENT == this->_FULL_SIZE) {
        return this->_responseBuffer;
    }
    if (_HeaderSent == true) {
        _responseBuffer.clear();
        _responseBuffer.clear();
        retRead = read_select(this->_fileFD, _responseBuffer, SEND_SIZE);
    }
    else
    {
        set_HeaderSent(true);
    }
    this->_SENT += this->_responseBuffer.length();
    return this->_responseBuffer;
}

bool    Response::mustRedirect(std::string path)
{
    std::vector<std::pair<std::string, std::string> >::iterator it;
    std::vector<std::pair<std::string, std::string> >::iterator end;

    if (_isLocation == NPOS)
    {
        it = this->_server[_serverIndex].get_redirections().begin();
        end = this->_server[_serverIndex].get_redirections().end();
        for (; it != end; it++)
        {
            if (it->first.compare(path) == 0)
            {
                _status = MOVED_PERM;
                pathRedirection(it->second);
                return true;
            }
        }
    }
    return false;
}

bool    Response::initData( void )
{
    _serverIndex = getServerIndex();
    isLocation();

    if (_isLocation != NPOS)
        this->_root = this->_server[_serverIndex].get_location()[_isLocation].get_root();
    else
        this->_root = this->_server[_serverIndex].get_root();
    if (*(_root.rbegin()) != '/')
        _root.append("/");
    if (mustRedirect(_request.getPath()) == true)
        return true;
    if (_isLocation != NPOS)
    {
        this->_path = this->_request.getPath();
        size_t  position = this->_path.find(this->_server[_serverIndex].get_location()[_isLocation].get_locations_path());
        size_t  len = this->_server[_serverIndex].get_location()[_isLocation].get_locations_path().length();
        if (position != NPOS)
            this->_path.erase(position, len);
    }
    else
        this->_path = this->_request.getPath();
    _pathIsDir =  (getAccessType(_root + _path) == S_IFDIR) ? (true) : (false);
    _autoindex = ((_isLocation == NPOS) ? _server[_serverIndex].get_autoindex()
                                        : _server[_serverIndex].get_location()[_isLocation].get_autoindex());
    _indexs = ((_isLocation == NPOS) ? _server[_serverIndex].get_index()
                                    : _server[_serverIndex].get_location()[_isLocation].get_index());
    _full_path = _root + _path;
    return false;
}

void    Response::pathRedirection(std::string to)
{
    _responseBuffer.append(_status).append("\n");
    _responseBuffer.append("Location: " + to).append("\n");
}

bool    Response::mustRedirect()
{
    if (_pathIsDir == true && *(_path.rbegin()) != '/')
    {
        _status = MOVED_PERM;
        return true;
    }
    return false;
}

bool    Response::noIndexMatch()
{
    for (std::vector<std::string>::iterator it = _indexs.begin(); it != _indexs.end(); it++)
    {
        if (getAccessType(_full_path + *it) == S_IFREG && access(std::string(_full_path + *it).c_str(), R_OK) == F_OK)
        {
            _status = OK;
            _full_path.append(*it);
            return false;
        }
    }
    return true;
}

bool    Response::forbiddenRessources( void )
{
    if ( _accessType == S_IFDIR )
    {
        if (_request.getMethod().compare(GET) == 0)
        {
            if (_indexs.size() == 0 && _autoindex.compare(OFF) == 0)
            {
                return true;
            }
            else if (_indexs.size() == 0 && _autoindex.compare(ON) == 0
                && access(_full_path.c_str(), R_OK) != F_OK)
            {
                return true;
            }
            else if (_indexs.size() == 0 && _autoindex.compare(ON) == 0
                && access(_full_path.c_str(), R_OK) == F_OK)
            {
                _status = AUTOINDEX;
                return false;
            }
            else if (_indexs.size() && _autoindex.compare(OFF) == 0)
            {
                if (noIndexMatch() == true)
                {
                    return true;
                }
                else
                {
                    _pathIsDir = false;
                    return false;
                }
            }
            else if (_indexs.size() && _autoindex.compare(ON) == 0)
            {
                if (noIndexMatch() == true)
                {
                    _status = AUTOINDEX;
                    return (access(_full_path.c_str(), R_OK) == F_OK)
                        ? (false) : (true);
                }
                else
                {
                    _pathIsDir = false;
                    return false;
                }
            }
        }
        return false;
    }
    else if ( _accessType == S_IFREG )
    {
        if (access(_full_path.c_str(), R_OK) != F_OK)
            return true;
        _status = OK;
        return false;
    }
    else
    {
        _status = NOT_FOUND;
        return true;
    }
    return false;
}

bool    Response::check_error_page( void )
{
    std::vector<std::pair<std::string, std::string> >::iterator it;
    std::vector<std::pair<std::string, std::string> >::iterator it_end;
    size_t                                                      size = 0;

    if (_isLocation != NPOS)
    {
        if ((size = _server[_serverIndex].get_location().operator[](_isLocation).get_error_pages().size()) != 0)
        {
            it = _server[_serverIndex].get_location().operator[](_isLocation).get_error_pages().begin();
            it_end = _server[_serverIndex].get_location().operator[](_isLocation).get_error_pages().end();
        }
    }
    else
    {
        if ((size = _server[_serverIndex].get_error_pages().size()) != 0)
        {
            it = _server[_serverIndex].get_error_pages().begin();
            it_end = _server[_serverIndex].get_error_pages().end();
        }
    }
    if (size != 0)
    {
        for (; it != it_end; it++)
        {
            if ( this->_status.compare(0, 3, it->first) == 0)
            {
                if (getAccessType(it->second) == S_IFREG
                    && access(it->second.c_str(), R_OK) == F_OK)
                {
                    this->_full_path = it->second;
                    return true;
                }
                else
                    return false;
            }
        }
    }
    return false;
}


void    Response::fillErrorPage( void )
{
    std::string     buffer;
    if (check_error_page() == true)
    {
        fillResponseBuffer();
        return ;
    }
    _responseBuffer.append(_status);
    _responseBuffer.append("\nContent-Type: text/html\nContent-Length: ");
    if (!_status.compare(FORBIDDEN_RQST))
        buffer = FORBIDDEN_RQST_403;
    else if (!_status.compare(NO_CONTENT))
        buffer = NO_CONTENT_204;
    else if (!_status.compare(BAD_RQST))
        buffer = BAD_RQST_400;
    else if (!_status.compare(SERVICE_UNAVAILABLE))
        buffer = SERVICE_UNAVAILABLE_503;
    else if (!_status.compare(METHOD_NOT_ALLOWED))
        buffer = METHOD_NOT_ALLOWED_405;
    else if (!_status.compare(NOT_IMPLEMENTED))
        buffer = NOT_IMPLEMENTED_501;
    else if (!_status.compare(NOT_FOUND))
        buffer = NOT_FOUND_404;
    else if (!_status.compare(REQUEST_TIMEOUT))
        buffer = REQUEST_TIMEOUT_408;
    else if (!_status.compare(PAYLOAD_TOO_LARGE))
        buffer = PAYLOAD_TOO_LARGE_413;
    else if (!_status.compare(BAD_GATEWAT))
        buffer = BAD_GATEWAT_502;
    else if (!_status.compare(OK_UPLOAD))
        buffer = UPLOAD_FILE_SUCCESS;
    else if (!_status.compare(NO_CONTENT))
        buffer = NO_CONTENT_204;
    else if (!_status.compare(INTERNAL_SERVER_ERROR))
        buffer = INTERNAL_SERVER_ERROR_500;
    _length = buffer.length();
    _responseBuffer.append(std::to_string(_length));
    _responseBuffer.append("\n\n").append(buffer);
}

bool    Response::notImplemented( void )
{
    if (_request.getMethod().compare(GET) && _request.getMethod().compare(POST) && _request.getMethod().compare(DELETE))
    {
        _status = NOT_IMPLEMENTED;
        return true;
    }
    return false;
}

bool    Response::methodNotAllowed( void )
{
    std::string                         requestMethod = this->_request.getMethod();
    std::vector<std::string>::iterator  it;
    std::vector<std::string>::iterator  end;

    if (_isLocation != NPOS)
    {
        it = this->_server[_serverIndex].get_location()[_isLocation].get_methods().begin();
        end = this->_server[_serverIndex].get_location()[_isLocation].get_methods().end();
    }
    else
    {
        it = this->_server[_serverIndex].get_methods().begin();
        end = this->_server[_serverIndex].get_methods().end();
    }
    for (; it != end; it++)
    {
        if (requestMethod.compare(*it) == 0)
        {
            return false;
        }
    }
    _status = METHOD_NOT_ALLOWED;
    return true;
}

bool    Response::payloadTooLarge( void )
{
    size_t  size = _request.getContentLength();
    size_t  max_body_size = 0;
    if (_isLocation != NPOS)
    {
        if (this->_server[_serverIndex].get_location()[_isLocation].get_client_max_body_size().length() != 0)
            max_body_size = std::stoi(this->_server[_serverIndex].get_location()[_isLocation].get_client_max_body_size());
        else
            return false;
    }
    else
    {
        if (this->_server[_serverIndex].get_client_max_body_size().length() != 0)
            max_body_size = std::stoi(this->_server[_serverIndex].get_client_max_body_size());
        else
            return false;
    }
    if (size != 0 && size > max_body_size)
    {
        if (size > max_body_size)
        {
            _status = PAYLOAD_TOO_LARGE;
            return true;
        }
    }
    return false;
}

void    Response::fillContentLength( void )
{
	int	    FD = -1;
	int	    len = 0;
	int	    ret = 0;
    std::string bufferString;

    _responseBuffer.append("\nContent-Length: ");
	FD = open(_full_path.c_str(), O_RDONLY);

    if (FD > 0)
    {
        while ((ret = read_select(FD, bufferString, RECV_SIZE)) > 0) {
            len += ret;
        }
        _responseBuffer.append(std::to_string(len));
        _responseBuffer.append("\n\n");
        close(FD);
        this->_FULL_SIZE += len + _responseBuffer.length();
    }
    this->_fileFD = open(_full_path.c_str(), O_RDONLY);
    if (_fileFD == -1) {
        this->_SENT = this->_FULL_SIZE;
    }
}

bool    Response::isCGI()
{
    size_t index;
    size_t len;

    for (std::vector<CGI>::iterator it = this->_server[_serverIndex].get_CGI().begin();
        it != this->_server[_serverIndex].get_CGI().end(); it++)
    {
        index = _full_path.length() - it->get_extention().length();
        len = it->get_extention().length();
        if (_full_path.compare(index, len, it->get_extention()) == 0)
        {
            _cgiIndex = it - this->_server[_serverIndex].get_CGI().begin();
            return true;
        }
    }
    return false;
}

void    Response::fillContentType( void )
{
    std::pair<std::string, std::string> ContentType;
    _responseBuffer.append(_status);
    _MT.set_path(_full_path);
    ContentType = _MT.get_mimetype();
    _responseBuffer.append("\nContent-Type: ").append(ContentType.second);
}

void    Response::fillResponseBuffer( void )
{
    if (isCGI() == true)
    {
        _status = this->_server[_serverIndex].get_CGI()[_cgiIndex].execute_cgi(_request, *this);
        if (_status.compare(OK) == 0)
        {
            this->_server[_serverIndex].get_CGI()[_cgiIndex].fillResponseBuffer(*this);
        }
        else
            fillErrorPage();
        return ;
    }
    fillContentType();
    fillContentLength();
}

void    Response::fillAutoindexPage( void )
{
    autoindex       page(_full_path, this->_request.getPath());
    std::string     autoindexPage;

    _responseBuffer.append(_status);
    _responseBuffer.append("\nContent-Type: text/html\nContent-Length: ");
    autoindexPage = page.get_page();
    _length = autoindexPage.length();
    _responseBuffer.append(std::to_string(_length));
    _responseBuffer.append("\n\n");
    _responseBuffer.append(autoindexPage);
}

void    Response::setHttpStatus( void )
{
    if (notImplemented() == true)
    {
        fillErrorPage();
        return ;
    }
    if (initData() == true)
    {
        return ;
    }
    if (mustRedirect() == true)
    {
        pathRedirection(_request.getPath() + "/");
        return ;
    }
    if (methodNotAllowed() == true)
    {
        fillErrorPage();
        return ;
    }
    if (payloadTooLarge() == true)
    {
        fillErrorPage();
        return ;
    }
    if (forbiddenRessources() == true)
    {
        if (_status.compare(NOT_FOUND) != 0)
            _status = FORBIDDEN_RQST;
        fillErrorPage();
        return ;
    }
    if (_status.compare(AUTOINDEX) == 0)
    {
        _status = OK;
        fillAutoindexPage();
        return ;
    }

    if (this->_request.getMethod().compare(POST) == 0 && _request.getContentLength() > 0 && !isCGI())
    {
        size_t      stat;
        std::string to;
        to = _server[_serverIndex].get_upload_path();
        if (to.length() == 0)
        {
            _status = INTERNAL_SERVER_ERROR;
            fillErrorPage();
            return ;
        }
        stat = getAccessType(to);
        if (stat == NPOS || stat == S_IFREG)
        {
            _status = INTERNAL_SERVER_ERROR;
            fillErrorPage();
            return ;
        }
        moveBody(_request.getBodyfilename(), to, _request);
        fillErrorPage();
        return ;
    }
    if (this->_request.getMethod().compare(DELETE) == 0 && !isCGI())
    {
        int status = 0;
        status = remove(this->_full_path.c_str());
        _status = NO_CONTENT;
        fillErrorPage();
    }
    fillResponseBuffer();
}

size_t  match_server_name_port(std::vector<std::string> server_names, std::string host, int port, std::string reqHost, int reqPort)
{
    if (port == reqPort)
    {
        if (host.compare("localhost") == 0 || host.compare("127.0.0.1") == 0)
            if (reqHost.compare("localhost") == 0 || reqHost.compare("127.0.0.1") == 0)
                return true;
        for (std::vector<std::string>::iterator it = server_names.begin(); it != server_names.end(); it++)
        {
            if (it->compare(reqHost) == 0)
            {
                return true;
            }
        }
        if (reqHost.compare(host) == 0)
        {
            return true;
        }
    }
    return false;
}

int         Response::getServerIndex() {
    this->_serverIndex = 0;

    for (std::vector<Server>::iterator it = this->_server.begin(); it != this->_server.end(); it++)
    {
        if (match_server_name_port(it->get_server_names(), it->get_host(), it->get_port(), _request.getHost(), _request.getPort()) == true)
        {
            return it - this->_server.begin();
        }
    }
    return 0;
}

size_t      Response::isLocation()
{
    for (std::vector<Location>::iterator it = _server[_serverIndex].get_location().begin();
    it != _server[_serverIndex].get_location().end(); it++)
    {
        if (*(it->get_locations_path().rbegin()) == '/' && it->get_locations_path().length() > 1)
            it->get_locations_path().erase(it->get_locations_path().end() - 1);

        if (it->get_locations_path().compare(0, it->get_locations_path().length(),
            _request.getPath().substr(0, it->get_locations_path().length())) == 0) {
            if (_request.getPath().length() > it->get_locations_path().length())
            {
                if (_request.getPath()[it->get_locations_path().length()] == '/')
                {
                    _isLocation = it - _server[_serverIndex].get_location().begin();
                    break ;
                }
                else
                {
                    _isLocation = NPOS;
                }
            }
            else {
                _isLocation = it - _server[_serverIndex].get_location().begin();
                break ;
            }
        }
    }
    return _isLocation;
}

size_t      Response::getAccessType(std::string PATH) {
    struct stat s;
    if( stat(PATH.c_str() ,&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
            _accessType = S_IFDIR;
        else if( s.st_mode & S_IFREG )
            _accessType = S_IFREG;
    }
    else
        _accessType = NPOS;
    return _accessType;
}

void    Response::moveBody(std::string from, std::string to, Request request)
{
    int             src_fd = 0;
	int	            dst_fd = 0;
	size_t          buffer_size = 0;
	int             rw_return = 0;
	size_t          index = 0;
    std::string     content_type;
    std::string     bufferString;

    if (*(to.rbegin()) != '/')
        to.push_back('/');
    to.append(randomfilename("_upload."));
    content_type = request.getHeaders("Content-Type");
    index = content_type.find("/");
    if (index != NPOS)
        to.append(content_type.substr(index + 1, content_type.find(";")));
    src_fd = open(from.c_str(), O_RDONLY);
    dst_fd = open(to.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IRGRP | S_IROTH);

    if (dst_fd < 0 || src_fd < 0)
    {
        _status = INTERNAL_SERVER_ERROR;
        return ;
    }
    while (1)
    {

        rw_return = read_select(src_fd, bufferString, 4096);
        if (rw_return == -1)
        {
            _status = INTERNAL_SERVER_ERROR;
            return ;
        }
        buffer_size = rw_return;
        if (buffer_size == 0)
            break ;
        rw_return = write_select(dst_fd, bufferString , buffer_size);
        if (rw_return == -1)
        {
            _status = INTERNAL_SERVER_ERROR;
            return ;
        }
    }
    close(src_fd);
    close(dst_fd);
    _status = OK_UPLOAD;
    return ;
}

void    Response::setConnection( void ) {
    std::vector<Request::string_pair> headers = _request.getHeaders();
    for (std::vector<Request::string_pair>::iterator it = headers.begin(); it != headers.end(); it++) {
        if (it->first == "Connection") {
            this->_connection = it->second;
            break ;
        }
    }
}

std::string         Response::getConnection( void ) {
    return this->_connection;
}