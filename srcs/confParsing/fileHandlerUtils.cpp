/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileHandlerUtils.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:22:37 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/17 07:37:19 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

void skipSpaces(std::string FILE, std::string::iterator &it)
{
    while (it < FILE.end()) {
        if (*it != ' ' && *it != '\t') {
            return ;
        }
        it++;
    }
}

bool    isEmptyLine(std::string LINE)
{
    int i = -1;

    if (LINE.length() == 0)
        return true;
    while (LINE[++i])
    {
        if (LINE[i] == '\t')
            LINE[i] = ' ';
        if (LINE[i] != ' ' && LINE[i] != '\t')
            return false;
    }
    return true;
}

void    nextChar(std::string FILE, std::string::iterator &it)
{
    while (it != FILE.end()) {
        if (*it != ' ' && *it != '\n' && *it != '\t')
            return ;
        it++;
    }
}

int    validatedKeyword(std::string &FILE, std::string::iterator &it)
{

    // is 'server_name' Keyword:
    if (FILE.compare(it - FILE.begin(), strlen(KW_SERVER_NAME), KW_SERVER_NAME) == 0) {
        it += strlen(KW_SERVER_NAME);
        return KW_SERVER_NAME_VALUE;
    }
    // is 'server' Keyword:
    if (FILE.compare(it - FILE.begin(), strlen(KW_SERVER), KW_SERVER) == 0) {
        // it += strlen(KW_SERVER);
        return KW_SERVER_VALUE;
    }
    // is 'listen' Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_LISTEN), KW_LISTEN) == 0) {
        it += strlen(KW_LISTEN);
        return KW_LISTEN_VALUE;
    }
    // is "}" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen("}"), "}") == 0) {
        it += strlen("}");
        return KW_CLOSED_BRACKET;
    }
    // is "root" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_LOCATION_ROOT), KW_LOCATION_ROOT) == 0) {
        it += strlen(KW_LOCATION_ROOT);
        return KW_LOCATION_ROOT_VALUE;
    }
    // is "allow_methods" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_ACCEPTED_METHOD), KW_ACCEPTED_METHOD) == 0) {
        it += strlen(KW_ACCEPTED_METHOD);
        return KW_ACCEPTED_METHOD_VALUE;
    }
    // is "index" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_DEFAULT_FILE), KW_DEFAULT_FILE) == 0) {
        it += strlen(KW_DEFAULT_FILE);
        return KW_DEFAULT_FILE_VALUE;
    }
    // is "location" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_LOCATION), KW_LOCATION) == 0) {
        it += strlen(KW_LOCATION);
        return KW_LOCATION_VALUE;
    }
    // is "cgi_path" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_CGI_PATH), KW_CGI_PATH) == 0) {
        it += strlen(KW_CGI_PATH);
        return KW_CGI_PATH_VALUE;
    }
    // is "cgi" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_CGI), KW_CGI) == 0) {
        it += strlen(KW_CGI);
        return KW_CGI_VALUE;
    }
    // is "redirection" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_REDIRECTION), KW_REDIRECTION) == 0) {
        it += strlen(KW_REDIRECTION);
        return KW_REDIRECTION_VALUE;
    }
    // is "autoindex" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_AUTOINDEX), KW_AUTOINDEX) == 0) {
        it += strlen(KW_AUTOINDEX);
        return KW_AUTOINDEX_VALUE;
    }
    // is "client_max_body_size" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_CLIENT_BODY_SIZE), KW_CLIENT_BODY_SIZE) == 0) {
        it += strlen(KW_CLIENT_BODY_SIZE);
        return KW_CLIENT_BODY_SIZE_VALUE;
    }
    // is "error_page" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_ERR_PAGE), KW_ERR_PAGE) == 0) {
        it += strlen(KW_ERR_PAGE);
        return KW_ERR_PAGE_VALUE;
    }
    // is "upload_path" Keyword:
    else if (FILE.compare(it - FILE.begin(), strlen(KW_UPLOAD_PATH), KW_UPLOAD_PATH) == 0) {
        it += strlen(KW_UPLOAD_PATH);
        return KW_UPLOAD_PATH_VALUE;
    }
    return 0;
}
