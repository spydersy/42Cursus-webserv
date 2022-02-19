/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:02:09 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/18 17:01:45 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

std::string     getToken(std::string &FILE, std::string::iterator &it)
{
    int         index = 0;
    std::string ret;

    while (*(it + index) != '\n' && *(it + index) != ' ' && *(it + index) != '\t') {
        index++;
    }
    ret = FILE.substr(it - FILE.begin(), index);
    it += index;
    return ret;
}

std::string     getPath(std::string &FILE, std::string::iterator &it)
{
    int         index = 0;
    std::string ret;

    while (*(it + index) != '\n'
        && *(it + index) != ' '
        && *(it + index) != '\t'
        && *(it + index) != '{'
        && *(it + index) != '}') {
        index++;
    }
    ret = FILE.substr(it - FILE.begin(), index);
    it += index;
    return ret;
}

void    fill_server_name(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    // std::cout << KYEL << "[FILLED : SERVER_NAME]" << KNRM << std::endl;
    if (data.whereAmI != POSITION_SERVER)
        errorStream(SYNTAX_ERR, true, 1);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_SERVER_NAME, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_SERVER_NAME, true, 1);
    if (vect.rbegin()->get_server_names().size() != 0) {
        errorStream("server_name : multiple definition", true, 1);
    }
    while (it < FILE.end() && *it != '\n') {
        vect[vect.size() - 1].get_server_names().push_back(getToken(FILE, it));
        if (*it != '\n')
            skipSpaces(FILE, it);
    }
    if (*it == '\n')
        it++;
    skipSpaces(FILE, it);
}

void    fill_methods(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    // std::cout << KYEL << "[FILLED : ALLOWED_METHODS]" << KNRM << std::endl;

    // std::cout << KGRN << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << KNRM << std::endl;
    // std::cout << "Size: " << (vect.rbegin()->get_location().rbegin()->get_methods()).size() << std::endl;
    // std::cout << KGRN << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << KNRM << std::endl;
    if (data.whereAmI != POSITION_SERVER && data.whereAmI != POSITION_LOCATION)
        errorStream(SYNTAX_ERR, true, 2);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_ACCEPTED_METHOD, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_ACCEPTED_METHOD, true, 1);
    if (data.whereAmI == POSITION_SERVER && vect.rbegin()->get_methods().size() != 0) {
        errorStream("allowed_methods : multiple definition", true, 1);
    }
    else if (data.whereAmI == POSITION_LOCATION && vect.rbegin()->get_location().rbegin()->get_methods().size() != 0) {
        errorStream("allowed_methods : multiple definition", true, 1);
    }
    while (it < FILE.end() && *it != '\n') {
        if (data.whereAmI == POSITION_SERVER)
            vect.rbegin()->get_methods().push_back(getToken(FILE, it));
        else 
            vect.rbegin()->get_location().rbegin()->get_methods().push_back(getToken(FILE, it));
            // get_methods().push_back(getToken(FILE, it));
        if (*it != '\n')
            skipSpaces(FILE, it);
    }
    if (*it == '\n')
        it++;
    skipSpaces(FILE, it);
}

void    fill_index(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    // std::cout << KYEL << "[FILLED : INDEX]" << KNRM << std::endl;
    if (data.whereAmI != POSITION_SERVER && data.whereAmI != POSITION_LOCATION)
        errorStream(SYNTAX_ERR, true, 3);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_DEFAULT_FILE, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_DEFAULT_FILE, true, 1);
    if (data.whereAmI == POSITION_SERVER && vect.rbegin()->get_index().size() != 0)
        errorStream("index : multiple definition", true, 1);
    else if (data.whereAmI == POSITION_LOCATION && vect.rbegin()->get_location().rbegin()->get_index().size() != 0)
        errorStream("index : multiple definition", true, 1);
    while (it < FILE.end() && *it != '\n') {
        vect.rbegin()->get_index().push_back(getToken(FILE, it));
        if (*it != '\n')
            skipSpaces(FILE, it);
    }
    if (*it == '\n')
        it++;
    skipSpaces(FILE, it);
}

void    fill_location_root(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    // std::cout << KYEL << "[FILLED : ROOT]" << KNRM << std::endl;
    if (data.whereAmI != POSITION_SERVER && data.whereAmI != POSITION_LOCATION)
        errorStream(SYNTAX_ERR, true, 4);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_LOCATION_ROOT, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_LOCATION_ROOT, true, 1);
    if (data.whereAmI == POSITION_SERVER) {
        if (vect.rbegin()->get_root().compare("") != 0)
            errorStream(" root: multiple definition", true, 1);
        vect.rbegin()->get_root() = getToken(FILE, it);
    }
    if (data.whereAmI == POSITION_LOCATION) {
        if (vect.rbegin()->get_location().rbegin()->get_root().compare("") != 0)
            errorStream(" root: multiple definition", true, 1);
        vect.rbegin()->get_location().rbegin()->get_root() = getToken(FILE, it);
    }
    skipSpaces(FILE, it);
    if (*it != '\n')
        errorStream(SYNTAX_ERR, true, 5);
    it++;
    skipSpaces(FILE, it);
}

void    fill_autoindex(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    // std::cout << KYEL << "[FILLED : AUTOINDEX]" << KNRM << std::endl;
    if (data.whereAmI != POSITION_LOCATION)
        errorStream(SYNTAX_ERR, true, 6);
    if (!(*it == ' ' || *it == '\t')) {
        errorStream(KW_AUTOINDEX, true, 1);
    }
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_AUTOINDEX, true, 1);
    if (vect.rbegin()->get_location().rbegin()->get_autoindex().length() != 0)
        errorStream("autoindex : multiple definition", true, 1);
    vect.rbegin()->get_location().rbegin()->get_autoindex() = getToken(FILE, it);
    skipSpaces(FILE, it);
    if (*it != '\n')
        errorStream(SYNTAX_ERR, true, 8);
    it++;
    skipSpaces(FILE, it);
}

void    fill_client_body_size(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    // std::cout << KYEL << "[FILLED : CLIENT_BODY_SIZE]" << KNRM << std::endl;
    if (data.whereAmI != POSITION_SERVER && data.whereAmI != POSITION_LOCATION)
        errorStream(SYNTAX_ERR, true, 4);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_CLIENT_BODY_SIZE, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_CLIENT_BODY_SIZE, true, 1);
    if (data.whereAmI == POSITION_SERVER) {
        if (vect.rbegin()->get_client_max_body_size().compare("") != 0)
            errorStream(" client_max_body_size: multiple definition", true, 1);
        vect.rbegin()->get_client_max_body_size() = getToken(FILE, it);
    }
    if (data.whereAmI == POSITION_LOCATION) {
        if (vect.rbegin()->get_location().rbegin()->get_client_max_body_size().compare("") != 0)
            errorStream(" client_body_size: multiple definition", true, 1);
        vect.rbegin()->get_location().rbegin()->get_client_max_body_size() = getToken(FILE, it);
    }
    skipSpaces(FILE, it);
    if (*it != '\n')
        errorStream(SYNTAX_ERR, true, 5);
    it++;
    skipSpaces(FILE, it);
}

void    fill_host_port(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    // std::cout << KYEL << "[FILLED : HOST_PORT]" << KNRM << std::endl;
    if (data.whereAmI != POSITION_SERVER)
        errorStream(SYNTAX_ERR, true, 6);
    if (!(*it == ' ' || *it == '\t')) {
        errorStream(KW_LISTEN, true, 1);
    }
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_LISTEN, true, 1);
    if (vect.rbegin()->get_host().length() != 0)
        errorStream("listen : multiple definition", true, 1);
    vect.rbegin()->get_host() = getToken(FILE, it);
    skipSpaces(FILE, it);
    if (*it != '\n')
        errorStream(SYNTAX_ERR, true, 8);
    it++;
    skipSpaces(FILE, it);
}

void    fill_location(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    (void)FILE;
    (void)it;
    (void)vect;
    (void)data;
    // std::cout << KYEL << "[FILLED : LOCATION]" << KNRM << std::endl;
}

void    setData(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    // std::cout << KYEL << "[FILLED : CLOSED_BRACKET]" << KNRM << std::endl;
    
    std::vector<bool>::reverse_iterator rit = data.Bracket.second.rbegin();
    (void)vect;
    while (rit != data.Bracket.second.rend()) {
        if (*rit == false)
            *rit = true;
        rit++;
    }
    if (data.whereAmI == POSITION_SERVER)
        data.whereAmI = POSITION_OUT;
    else if (data.whereAmI == POSITION_CGI || data.whereAmI == POSITION_LOCATION)
        data.whereAmI = POSITION_SERVER;
    else if (data.whereAmI == POSITION_OUT)
        errorStream(SYNTAX_ERR, true, 9);
    it++;
    skipSpaces(FILE, it);
    nextChar(FILE, it);
    if (*it == '\n') {
        it++;
        skipSpaces(FILE, it);
    }
}











	// locatopn /bla {
	// 	allow_methods POST
	// 	cgi_pass test_mac/macos_cgi_tester
	// }
    
/*



server {
	server_name youpi
	listen 0.0.0.0:8001

	root ./YoupiBanane
	index index.html

	allow_methods GET

	location /put_test {
		allow_methods PUT
		root ./YoupiBanane/put_here
	}

	location /post_body {
		allow_methods POST
		client_body_buffer_size 100
	}

	location /directory {
		
		allow_methods GET
		root YoupiBanane/
		index youpi.bad_extension
	}

	location /bla {
		allow_methods POST
		cgi_pass test_mac/macos_cgi_tester
	}
}

server {
	server_name youpi
	listen 0.0.0.0:8002

	root ./YoupiBanane
	index index.html

	allow_methods GET

	location /put_test {
		allow_methods PUT
		root ./YoupiBanane/put_here
		alias
	}

	location /post_body {
		allow_methods POST
		client_body_buffer_size 100
	}

	location /directory {
		alias
		allow_methods GET
		root YoupiBanane/
		index youpi.bad_extension

		location *.bla {
			allow_methods GET POST
			cgi_pass test_mac/macos_cgi_tester
		}
	}

	location *.bla {
		allow_methods POST
		cgi_pass test_mac/macos_cgi_tester
	}
}



*/