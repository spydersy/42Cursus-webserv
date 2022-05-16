/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.Class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 06:57:25 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/26 18:39:15 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

/*
** CGI CANONICAL FORM:
*/
CGI::CGI( void ) :  _extention(""),
                    _cgi_path(""),
                    _methods(std::vector<std::string>()),
                    _envp(NULL),
                    _argv(NULL),
                    _cgi_response_file(""),
                    _status(""),
                    _header(""),
                    _FILEINLINE("") {}

CGI::~CGI() {}

CGI::CGI( const CGI &src)
{
    if (this != &src)
    {
        this->_methods = src._methods;
        this->_cgi_path = src._cgi_path;
        this->_extention = src._extention;
        this->_cgi_response_file = src._cgi_response_file;
    }
}

CGI &CGI::operator=( const CGI &src)
{
    if (this != &src)
    {
        this->_methods = src._methods;
        this->_cgi_path = src._cgi_path;
        this->_extention = src._extention;
        this->_cgi_response_file = src._cgi_response_file;
    }
    return *this;
}

std::string                 &CGI::get_extention() { return this->_extention; }
std::string                 &CGI::get_cgi_path() { return this->_cgi_path; }
std::string                 &CGI::get_cgi_response_file() { return this->_cgi_response_file; }
std::vector<std::string>    &CGI::get_methods() { return this->_methods; }

void    CGI::set_argv(Response response)
{
    _argv = (char**)malloc(sizeof(char*) * 3);

    _argv[0]  = strdup(_cgi_path.c_str());
    _argv[1]  = strdup(response.get_full_path().c_str());
    _argv[2]  = NULL;
}

std::string CGI::get_script_name(Response response)
{
    size_t      index = response.get_full_path().find_last_of('/');
    std::string script_name = response.get_full_path().substr(index + 1);

    return script_name;
}

std::string CGI::get_path_info(Response response)
{
    size_t      index = response.get_full_path().find_last_of('/');
    std::string script_name = response.get_full_path().substr(0, index);

    return script_name;
}

std::string CGI::generate_uri(Request request)
{
    std::string uri;

    uri = "http://";
    uri.append(request.getHost());
    uri.append(std::to_string(request.getPort()));
    uri.append(request.getPath());
    uri.append(request.getQueryString());
    return uri;
}

std::string CGI::header_to_envp(string_pair pair)
{
    std::string             env = "HTTP_";
    std::string::iterator   it = pair.first.begin();

    for(; it != pair.first.end(); it++)
        env.push_back(std::toupper(*it));
    env.push_back('=');
    env.append(pair.second);
    return env;
}

void    CGI::set_envp(Request request, Response response)
{
    std::vector<std::string>    envp_vect;

    envp_vect.push_back("REQUEST_URI=" + request.getPath().substr(0, request.getPath().find_last_of("/")));
    envp_vect.push_back("DOCUMENT_URI=" + request.getPath() + request.getQueryString());
    envp_vect.push_back("SCRIPT_NAME=" +  request.getPath());
    envp_vect.push_back("SCRIPT_FILENAME=" + response.get_full_path());
    envp_vect.push_back("PATH_TRANSLATED=" + response.get_full_path());
    envp_vect.push_back("QUERY_STRING=" + request.getQueryString());
    envp_vect.push_back("SERVER_NAME=localhost");
    envp_vect.push_back("SERVER_PORT=" + std::to_string(request.getPort()));
    envp_vect.push_back("REQUEST_METHOD=" + request.getMethod());
    envp_vect.push_back("DOCUMENT_ROOT=" + response.get_root());
    envp_vect.push_back("GETAWAY_INTERFACE=CGI/1.1");
    envp_vect.push_back("SERVER_PROTOCOL=HTTP/1.1");
    envp_vect.push_back("REDIRECT_STATUS=200");
    envp_vect.push_back("FCGI_ROLE=RESPONDER");
    envp_vect.push_back("REQUEST_SCHEME=http");
    envp_vect.push_back("SERVER_SOFTWARE=webserv/1.1");
    envp_vect.push_back("PATH=" + std::string(std::getenv("PATH")));
    envp_vect.push_back("REMOTE_ADDR=0.0.0.0");
    envp_vect.push_back("REMOTE_PORT=0");
	if (request.getContentLength() > 0)
    {
        envp_vect.push_back("CONTENT_TYPE=" + request.getHeaders("Content-Type"));
        envp_vect.push_back("CONTENT_LENGTH=" + std::to_string(request.getContentLength()));
    }
    else
    {
        envp_vect.push_back("CONTENT_TYPE=text/html; charset=UTF-8");
        envp_vect.push_back("CONTENT_LENGTH=0");
    }
    for (std::vector<string_pair>::iterator it = request.getHeaders().begin();
            it != request.getHeaders().end(); it++)
        envp_vect.push_back(header_to_envp(*it));
    _envp = (char**)malloc(sizeof(char*) * (envp_vect.size() + 1));
    size_t i = -1;
    while (++i < envp_vect.size())
        _envp[i] = strdup(envp_vect[i].c_str());
    _envp[i] = NULL;
}

std::string    CGI::set_cgi_path( void )
{

    if ((getAccessType(_cgi_path)) == S_IFREG)
        return OK;
    else if ((getAccessType(_cgi_path)) == NPOS) {
        return INTERNAL_SERVER_ERROR;
    }
    return OK;
}

std::string    CGI::set_cgi_response_file()
{

    _cgi_response_file = "/var/tmp/cgi_" + randomfilename("") + "_response";

    std::ofstream    file;

    file.open(_cgi_response_file);
    if (file.is_open() == 0)
    {
        return INTERNAL_SERVER_ERROR;
    }
    return OK;
}

std::string CGI::init_data()
{
    if (set_cgi_path().compare(OK))
    {
    return (_status = INTERNAL_SERVER_ERROR);
    }
    if (set_cgi_response_file().compare(OK))
    {
        return (_status = INTERNAL_SERVER_ERROR);
    }
    return OK;
}

std::string  CGI::cgi_process( Response & response, Request request )
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
    {
        return BAD_GATEWAT;
    }
    if (pid == 0)
    {
        int cgi_response_fd = 0;
        int body_fd = 0;
        set_envp(request, response);
        set_argv(response);
        if ((cgi_response_fd = open(_cgi_response_file.c_str(), O_WRONLY)) < 0)
        {
            exit(BAD_GATEWAT_FAILURE);
        }
        if (0 < request.getContentLength() && (body_fd = open(request.getBodyfilename().c_str(), O_RDONLY)) < 0)
        {
            exit(BAD_GATEWAT_FAILURE);
        }
        if ((request.getMethod().compare(POST) == 0 || request.getMethod().compare(DELETE) == 0)
            && dup2(body_fd, STDIN_FILENO) < 0)
        {
            exit(BAD_GATEWAT_FAILURE);
        }
        if (dup2(cgi_response_fd, STDOUT) < 0)
        {
            exit(BAD_GATEWAT_FAILURE);
        }
        if (execve(_cgi_path.c_str(), _argv, this->_envp) < 0)
        {
            exit(BAD_GATEWAT_FAILURE);
        }
        exit(0);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
            return INTERNAL_SERVER_ERROR;
        int exit_status;
        if (WIFEXITED(status) && (exit_status = WEXITSTATUS(status)) == BAD_GATEWAT_FAILURE) {
            return BAD_GATEWAT;
        }
        else if (WIFEXITED(status) && (exit_status = WEXITSTATUS(status)) == NO_CONTENT_FAILURE)
        {
            return NO_CONTENT;
        }
    }
    return OK;
}

std::string CGI::execute_cgi(Request request, Response & response)
{
    if ((_status = init_data()).compare(OK))
        return  _status;
    std::string s = this->cgi_process(response, request);
    _status = s;
    return s;
}

std::string CGI::set_status( void )
{
    std::string                 status = "200 OK\r\n";
    size_t                      status_index = 0;
    size_t                      len;

    if (_header.length())
        status_index = this->_header.find("Status: ");
    if (status_index != NPOS)
    {
        len = this->_header.find("\r\n", 0);
        status = _header.substr(status_index + 8, len);
    }
    return status;
}

void        CGI::set_header(Response & response)
{
    (void) response;
    std::ifstream               FILE(_cgi_response_file);

    if (FILE.is_open())
    {
        std::string                 LINE;
        size_t                      header_index;

        while (getline (FILE, LINE))
            _FILEINLINE += LINE + "\n";
        header_index = _FILEINLINE.find_first_of("\n\n", 0, 2);
        if (header_index != NPOS)
            this->_header = _FILEINLINE.substr(0, header_index);
        else
            this->_header = "";
    }
    else
        this->_header = "";
}

void        CGI::fillResponseBuffer( Response & response )
{
    set_header(response);
    response.get_responseBuffer().append(set_status());
    response.get_responseBuffer().append(_FILEINLINE);
    response.get_FULL_SIZE() += response.get_responseBuffer().length();
    remove(_cgi_response_file.c_str());
}

size_t      CGI::getAccessType(std::string PATH) {
    size_t _accessType = 0;
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
