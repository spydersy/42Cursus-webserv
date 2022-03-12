/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:17:47 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/12 02:42:40 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

/*
** CONSTRUCTORS && DESTRUCTORS : ***********************************************
*/
Response::Response( Request REQ, std::vector<Server> SERV ) :   _request(REQ),
                                                                _server(SERV),
                                                                _MT(""),
                                                                _responseBuffer(""),
                                                                _serverIndex(NPOS),
                                                                _isLocation(NPOS),
                                                                _length(0),
                                                                _root(""),
                                                                _method(""),
                                                                _status(""),
                                                                _indexs(std::vector<std::string>()),
                                                                _autoindex(""),
                                                                _pathIsDir(false) {
    // std::cout << "Response Constructor Called :)" << std::endl;
}

Response::~Response(){
    // std::cout << "Response Destructor Called :'( " << std::endl;
}

Response        &Response::operator=( const Response &src ) {
    this->_request = src._request;
    this->_server = src._server;
    this->_MT = src._MT;
    this->_responseBuffer = src._responseBuffer;
    this->_serverIndex = src._serverIndex;
    this->_isLocation = src._isLocation;
    this->_root = src._root;
    this->_path = src._path;
    this->_method = src._method;
    this->_status = src._status;
    this->_indexs = src._indexs;
    this->_autoindex = src._autoindex;
    this->_pathIsDir = src._pathIsDir;
    return *this;
}
/*
** GETTERS && SETTERS : ********************************************************
*/
Request             &Response::get_request( void ) { return this->_request; }
size_t              &Response::get_length( void ) { return this->_length; }
std::vector<Server> &Response::get_server( void ) { return this->_server; }
MimeTypes           &Response::get_MT( void ) { return this->_MT; }
std::string         &Response::get_responseBuffer( void ) { return this->_responseBuffer; }

void    Response::setHttpVersion( void ) {
    _responseBuffer.append("HTTP/1.1 ");
}

/*
** GET-POST-DELETE methods : ***************************************************
*/
std::string Response::GETmethod() {
    std::string     ret;
    if (_pathIsDir == true) {
        if (_indexs.size()) {
            for (std::vector<std::string>::iterator it = _indexs.begin(); it != _indexs.end(); it++) {
                if (getAccessType(_root + "/" + *it) == S_IFREG) {
                    if (access((_root + "/" + *it).c_str(), R_OK) == F_OK) {
                        _root.append("/" + *it);
                        return OK;
                    }
                    else {
                        ret = FORBIDDEN_RQST;
                    }
                }
                else {
                    if (ret.compare(FORBIDDEN_RQST))
                        ret = NOT_FOUND;
                }
                // std::cout << "[" <<  fullPath << "]" << std::endl;
            }
            return ret;
        }
        else {
            if (!_autoindex.compare(ON))
                return "AUTOINDEX";
            else
                return FORBIDDEN_RQST;
        }
        return ret;
    }
    else {
        if (getAccessType(_root + _request.getPath()) == S_IFREG) {
            if (access((_root + _request.getPath()).c_str(), R_OK) == F_OK) {
                _root.append(_request.getPath());
                return OK;
            }
            else {
                return FORBIDDEN_RQST;
            }
        }
        else {
            return NOT_FOUND;
        }
    }
    // return "";
}

/*
** STATUS HANDLERS : ***********************************************************
*/
void    Response::setHttpStatus( void ) {
    if (badRequest() == true) {
        _status = FORBIDDEN_RQST;
        fillErrorPage();
        return;
    }
    getServerIndex();
    isLocation();
    _path = _request.getPath();
    _root = ((_isLocation == NPOS) ? _server[_serverIndex].get_root() : _server[_serverIndex].get_location()[_isLocation].get_root());
    if (_isLocation != NPOS)
        _request.getPath().erase(0, _server[_serverIndex].get_location()[_isLocation].get_locations_path().length());
    if (forbiddenRessources() == true) {
        _status = FORBIDDEN_RQST;
        fillErrorPage();
        return;
    }
    if ((_status = checkMethods()).length()) {
        fillErrorPage();
        return;
    }
    if (!_request.getMethod().compare(GET)) {
        std::string ret_GETmethod;

        ret_GETmethod = GETmethod();
        if (!ret_GETmethod.compare(OK)) {
            _status = OK;
            fillResponseBuffer();
            std::cout << KRED << "FINAL STATUS : OK" << KNRM << std::endl;
        }
        else if (!ret_GETmethod.compare(FORBIDDEN_RQST)) {
            _status = FORBIDDEN_RQST;
            fillErrorPage();
            std::cout << KRED << "FINAL STATUS : FORBIDDEN_RQST" << KNRM << std::endl;
        }
        else if (!ret_GETmethod.compare(NOT_FOUND)) {
            _status = NOT_FOUND;
            fillErrorPage();
            std::cout << KRED << "FINAL STATUS : NOT_FOUND" << KNRM << std::endl;
        }
        else if (!ret_GETmethod.compare("AUTOINDEX")) {
            _status = OK;
            fillAutoindexPage();
            std::cout << KRED << "FINAL STATUS : AUTOINDEX" << KNRM << std::endl;
        }
        // TODO : CHECK WHICH CASE
        // else if (!ret_GETmethod.compare("")) {
        //     _status = OK;
        //     std::cout << KRED << "FINAL STATUS : EMPTY SHIIIIIIIIIIIIIIIIIIIIIIT" << KNRM << std::endl;
        // }
    }
}

bool    Response::serviceUnavailable() {
    if (_request.getVersion().compare("HTTP/1.1"))
        return true;
    return false;
}

bool    Response::badRequest( void ) {
    // _status = BAD_RQST;
    return false;
}

bool    Response::forbiddenRessources( void ) {
    size_t  accessType;
    _autoindex = ((_isLocation == NPOS) ? _server[_serverIndex].get_autoindex() : _server[_serverIndex].get_location()[_isLocation].get_autoindex());
    _indexs = ((_isLocation == NPOS) ? _server[_serverIndex].get_index() : _server[_serverIndex].get_location()[_isLocation].get_index());

    // std::cout << "_rootDBG 403 : [" << _root << "] | RQST : [" << _request.getPath() << "] | method : [" << _request.getMethod() << "]" << std::endl;
    // std::cout << "Path 403 : [" << std::string(_root + _request.getPath()).c_str() << "]" << std::endl;
    accessType = getAccessType(_root + _request.getPath());
    if( accessType == S_IFDIR )
    {
        // std::cout << "DBG :::::::::::::::: is a directory" << std::endl;
        _pathIsDir = true;
        if (_request.getMethod().compare(GET) == 0) {
            if (access(_root.c_str(), R_OK) != F_OK)
                return true;
            else {
                if (_indexs.size() == 0)
                    if (_autoindex.compare(OFF) == 0)
                        return true;
            }
        }
        return false;
    }
    else if( accessType == S_IFREG ){
        // std::cout << "DBG :::::::::::::::: is a file" << std::endl;
        if (access(std::string(_root + _request.getPath()).c_str(), R_OK) != F_OK)
            return true;
        return false;
    }
    return false;
}

/*
** UTILS : *********************************************************************
*/
void    Response::fillAutoindexPage( void ) {
    // std::cout << "AUTOINDEX_DBG path :[" << _request.getPath() << "][" << _path << "]" << std::endl;
    autoindex       page(_root, _path);
    std::string     autoindexPage;

    _responseBuffer.append(_status);
    _responseBuffer.append("\nContent-Type: text/html\nContent-Length: ");
    autoindexPage = page.get_page();
    _length = autoindexPage.length();
    _responseBuffer.append(std::to_string(_length));
    _responseBuffer.append("\n\n");
    _responseBuffer.append(autoindexPage);
}

void    Response::fillContentType( void ) {
    std::pair<std::string, std::string> ContentType;
    _responseBuffer.append(_status);
    _MT.set_path(_root);
    ContentType = _MT.get_mimetype();
    _responseBuffer.append("\nContent-Type: ").append(ContentType.second);
}

void    Response::fillContentLength( void ) {
    std::ifstream   FILE;
    std::string     line;
    std::string     buffer;

    _responseBuffer.append("\nContent-Length: ");
    FILE.open(_root);
    if (FILE.is_open()) {
        while (getline(FILE, line)) {
            _length += line.length() + 1;
            buffer.append(line).append("\n");
        }
    }
    _responseBuffer.append(std::to_string(_length));
    _responseBuffer.append("\n\n");
    _responseBuffer.append(buffer);
}

void    Response::fillResponseBuffer( void ) {
    fillContentType();
    fillContentLength();
}

void    Response::fillErrorPage( void ) {
    std::string     buffer;

    _responseBuffer.append(_status);
    _responseBuffer.append("\nContent-Type: text/html\nContent-Length: ");
    if (!_status.compare(FORBIDDEN_RQST))
        buffer = FORBIDDEN_RQST_403;
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
        _length = buffer.length();
    _responseBuffer.append(std::to_string(_length));
    _responseBuffer.append("\n\n").append(buffer);
}

int     Response::getServerIndex() {
    this->_serverIndex = 0;
    return 0;
    /*
    for (std::vector<Server>::iterator it = this->_server.begin(); it != this->_server.end(); it++) {
        std::cout << "DBG MY_HOST : [" << it->get_host() << "] | RQST_HOST : [" << _request.getHost() << "]" << std::endl;
        if (it->get_host().compare(_request.getHost()) == 0) {
            this->_serverIndex = it - this->_server.begin();
            return it - this->_server.begin();
        }
    }
    return -1;
    */
}

std::string    Response::checkMethods( void ) {
    std::string rqstMethod = _request.getMethod();
    // std::cout << "rqstMethod: [" << rqstMethod << "]" << std::endl;
    if (rqstMethod.compare(GET) &&  rqstMethod.compare(POST) && rqstMethod.compare(DELETE)) {
        // std::cout << "NOT IMPLEMENTED DBG" << std::endl;
        return NOT_IMPLEMENTED;
    }
    std::vector<std::string> methods;
    if (_isLocation != NPOS)
        methods = _server[_serverIndex].get_location()[_isLocation].get_methods();
    else
        methods = _server[_serverIndex].get_methods();
    for (std::vector<std::string>::iterator it = methods.begin(); it != methods.end(); it++) {
        if ((*it).compare(_request.getMethod()) == 0) {
            _method = *it;
            // std::cout << "IMPLEMENTED DBG" << std::endl;
            return "";
        }
    }
    return METHOD_NOT_ALLOWED ;
}

size_t     Response::isLocation() {
    for (std::vector<Location>::iterator it = _server[_serverIndex].get_location().begin();
    it != _server[_serverIndex].get_location().end(); it++) {
        if (it->get_locations_path().compare(0, it->get_locations_path().length(), _request.getPath().substr(0, it->get_locations_path().length())) == 0) {
            if (_request.getPath().length() > it->get_locations_path().length()) {
                if (_request.getPath()[it->get_locations_path().length()] == '/') {
                    _isLocation = it - _server[_serverIndex].get_location().begin();
                    break ;
                }
                else
                    _isLocation = NPOS;
            }
            else {
                _isLocation = it - _server[_serverIndex].get_location().begin();
                break ;
            }
        }
    }
    return _isLocation;
}

size_t    Response::getAccessType(std::string PATH) {
    struct stat s;
    if( stat(PATH.c_str() ,&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
            return S_IFDIR;
        else if( s.st_mode & S_IFREG )
            return S_IFREG;
    }
    return NPOS;
}

/*
    std::cout << " | LEN : " << _server[_serverIndex].get_location()[_isLocation].get_locations_path().length() << std::endl;
    std::string filePath = _server.begin()->get_root();
    filePath.append(_request.getPath());
    std::ifstream   FILE;

    std::cout << "FILE TO OPEN : " << filePath << std::endl;
    FILE.open(filePath);
    if (FILE.is_open()) {
        _responseBuffer.append("200 OK\nContent-Type: ");
        if (filePath.find(".html") != std::string::npos) {
            _responseBuffer.append("text/html\nContent-Leeength: ");
        }
        else {
            _responseBuffer.append("text/css\nContent-Leeength: ");
        }
        std::string FILEinLine;
        std::string buffer;
        int         len = 0;
        while (getline(FILE, buffer)) {
            FILEinLine.append(buffer).append("\n");
            len += buffer.length() + 1;
        }
        _responseBuffer.append(std::to_string(len)).append("\n\n").append(FILEinLine);
    }
    else {
        std::cerr << "Cant open FILE" << std::endl;
        _responseBuffer.append("404 OK\n");
    }
*/
