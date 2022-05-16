/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:02:09 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/26 06:07:27 by abelarif         ###   ########.fr       */
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

void    fill_upload_path(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    if (data.whereAmI != POSITION_SERVER && data.whereAmI != POSITION_LOCATION)
        errorStream(SYNTAX_ERR, true, 4);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_UPLOAD_PATH, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_UPLOAD_PATH, true, 1);
    if (data.whereAmI == POSITION_SERVER)
    {
        if (vect.rbegin()->get_upload_path().compare("") != 0)
            errorStream(" upload_path: multiple definition", true, 1);
        vect.rbegin()->get_upload_path() = getToken(FILE, it);
    }
    if (data.whereAmI == POSITION_LOCATION)
    {
        if (vect.rbegin()->get_location().rbegin()->get_upload_path().compare("") != 0)
            errorStream(" upload_path: multiple definition", true, 1);
        vect.rbegin()->get_location().rbegin()->get_upload_path() = getToken(FILE, it);
    }
    skipSpaces(FILE, it);
    if (*it != '\n')
        errorStream(SYNTAX_ERR, true, 42);
    it++;
    skipSpaces(FILE, it);
}


void    fill_cgi_path(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    if (data.whereAmI != POSITION_CGI)
        errorStream(SYNTAX_ERR, true, 4);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_CGI_PATH, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_CGI_PATH, true, 1);

    if (vect.rbegin()->get_CGI().rbegin()->get_cgi_path().compare("") != 0)
        errorStream(" cgi_path: multiple definition", true, 1);
    vect.rbegin()->get_CGI().rbegin()->get_cgi_path() = getToken(FILE, it);
    skipSpaces(FILE, it);
    if (*it != '\n')
        errorStream(SYNTAX_ERR, true, 43);
    it++;
    skipSpaces(FILE, it);
}

void    fill_redirection(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    if (data.whereAmI != POSITION_SERVER)
        errorStream(SYNTAX_ERR, true, 3);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_REDIRECTION, true, 11);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_REDIRECTION, true, 12);

    std::string::iterator   redirection_begin = it;
    while (it < FILE.end() && *it != '\n')
        it++;
    std::string tmp_redirection_line = FILE.substr(redirection_begin - FILE.begin(), it - redirection_begin);
    char       *redirection_line = (char*)tmp_redirection_line.c_str();
    std::pair<std::string, std::string>   redirection_pair;

    char*   ret = NULL;
    ret = strtok(redirection_line, " \t");
    if (ret != NULL)
        redirection_pair.first = ret;
    else
        errorStream(KW_REDIRECTION, true, 15);
    for (int i = 1; ret != NULL; i++)
    {
        if (i > 2)
            errorStream(KW_REDIRECTION, true, 16);
        ret = strtok(NULL, " \t");
        if (i == 1 && ret != NULL)
            redirection_pair.second = ret;
        else if (i == 1 && ret == NULL)
            errorStream(KW_ERR_PAGE, true, 14);
    }
    vect.rbegin()->get_redirections().push_back(redirection_pair);
    if (*it == '\n')
        it++;
    skipSpaces(FILE, it);
}

void    fill_methods(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
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
        if (*it != '\n')
            skipSpaces(FILE, it);
    }
    if (*it == '\n')
        it++;
    skipSpaces(FILE, it);
}

void    fill_index(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
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
        if (data.whereAmI == POSITION_SERVER)
            vect.rbegin()->get_index().push_back(getToken(FILE, it));
        else
            vect.rbegin()->get_location().rbegin()->get_index().push_back(getToken(FILE, it));
        if (*it != '\n')
            skipSpaces(FILE, it);
    }
    if (*it == '\n')
        it++;
    skipSpaces(FILE, it);
}

void    fill_location_root(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    if (data.whereAmI != POSITION_SERVER && data.whereAmI != POSITION_LOCATION)
        errorStream(SYNTAX_ERR, true, 4);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_LOCATION_ROOT, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_LOCATION_ROOT, true, 1);
    if (data.whereAmI == POSITION_SERVER)
    {
        if (vect.rbegin()->get_root().compare("") != 0)
            errorStream(" root: multiple definition", true, 1);
        vect.rbegin()->get_root() = getToken(FILE, it);
    }
    if (data.whereAmI == POSITION_LOCATION)
    {
        if (vect.rbegin()->get_location().rbegin()->get_root().compare("") != 0)
            errorStream(" root: multiple definition", true, 1);
        vect.rbegin()->get_location().rbegin()->get_root() = getToken(FILE, it);
    }
    skipSpaces(FILE, it);
    if (*it != '\n')
        errorStream(SYNTAX_ERR, true, 44);
    it++;
    skipSpaces(FILE, it);
}

void    fill_autoindex(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    if (data.whereAmI != POSITION_SERVER && data.whereAmI != POSITION_LOCATION)
        errorStream(SYNTAX_ERR, true, 6);
    if (!(*it == ' ' || *it == '\t')) {
        errorStream(KW_AUTOINDEX, true, 1);
    }
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_AUTOINDEX, true, 1);

    if (data.whereAmI == POSITION_SERVER)
    {
        if (vect.rbegin()->get_autoindex().length() != 0)
            errorStream(" root: multiple definition", true, 1);
        vect.rbegin()->get_autoindex() = getToken(FILE, it);
    }
    if (data.whereAmI == POSITION_LOCATION)
    {
        if (vect.rbegin()->get_location().rbegin()->get_autoindex().length() != 0)
            errorStream("autoindex : multiple definition", true, 1);
        vect.rbegin()->get_location().rbegin()->get_autoindex() = getToken(FILE, it);
    }

    skipSpaces(FILE, it);
    if (*it != '\n')
        errorStream(SYNTAX_ERR, true, 8);
    it++;
    skipSpaces(FILE, it);
}

void    fill_client_body_size(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
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
        errorStream(SYNTAX_ERR, true, 45);
    it++;
    skipSpaces(FILE, it);
}

void    fill_host_port(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
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
    if (vect.rbegin()->setHostPort() == false) {
        errorStream("Host Port ", true, 1);
    }
}

void    setData(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
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

void    fill_error_page(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, ServerData &data)
{
    if (data.whereAmI != POSITION_SERVER && data.whereAmI != POSITION_LOCATION && data.whereAmI != POSITION_CGI)
        errorStream(SYNTAX_ERR, true, 3);
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_ERR_PAGE, true, 11);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_ERR_PAGE, true, 12);
    std::string::iterator   error_begin = it;
    while (it < FILE.end() && *it != '\n')
        it++;
    std::string tmp_error_line = FILE.substr(error_begin - FILE.begin(), it - error_begin);
    char       *error_line = (char*)tmp_error_line.c_str();
    std::pair<std::string, std::string>   error_pair;

    char*   ret = NULL;
    ret = strtok(error_line, " \t");
    if (ret != NULL) {
        error_pair.first = ret;}
    else
        errorStream(KW_ERR_PAGE, true, 15);
    for (int i = 1; ret != NULL; i++) {
        if (i > 2) {
            errorStream(KW_ERR_PAGE, true, 16);
        }
        ret = strtok(NULL, " \t");
        if (i == 1 && ret != NULL) {
            error_pair.second = ret;
        }
        else if (i == 1 && ret == NULL)
        errorStream(KW_ERR_PAGE, true, 14);
    }
    if (data.whereAmI == POSITION_SERVER)
        vect.rbegin()->get_error_pages().push_back(error_pair);
    else if (data.whereAmI == POSITION_LOCATION)
        vect.rbegin()->get_location().rbegin()->get_error_pages().push_back(error_pair);
    if (*it == '\n')
        it++;
    skipSpaces(FILE, it);
}
