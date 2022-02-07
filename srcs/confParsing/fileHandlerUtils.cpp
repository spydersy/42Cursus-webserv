/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileHandlerUtils.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:22:37 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/07 18:05:16 by abelarif         ###   ########.fr       */
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

void    nextChar(std::string FILE, std::string::iterator &it) 
{
    while (it != FILE.end()) {
        if (*it != ' ' && *it != '\n' && *it != '\t')
            return ;
        it++;
    }
}

int    validatedKeyword(std::string FILE, std::string::iterator &it)
{
    // is 'server_name' Keyword:
    if (FILE.compare(it - FILE.begin(), strlen(KW_SERVER_NAME), KW_SERVER_NAME) == 0) {
        it += strlen(KW_SERVER_NAME);
        return KW_SERVER_NAME_VALUE;
    }
    // // is 'error_page' Keyword:
    // else if (FILE.compare(it - FILE.begin(), strlen(KW_ERR_PAGE), KW_ERR_PAGE) == 0) {
    //     it += strlen(KW_ERR_PAGE);
    //     return true;
    // }
    // // is 'client_max_body_size' Keyword:
    // else if (FILE.compare(it - FILE.begin(), strlen(KW_CLIENT_BODY_SIZE), KW_CLIENT_BODY_SIZE) == 0) {
    //     it += strlen(KW_CLIENT_BODY_SIZE);
    //     return true;
    // }
    // // is 'allow_methods' Keyword:
    // else if (FILE.compare(it - FILE.begin(), strlen(KW_ACCEPTED_METHOD), KW_ACCEPTED_METHOD) == 0) {
    //     it += strlen(KW_ACCEPTED_METHOD);
    //     return true;
    // }
    // // is 'autoindex' Keyword:
    // else if (FILE.compare(it - FILE.begin(), strlen(KW_AUTOINDEX), KW_AUTOINDEX) == 0) {
    //     it += strlen(KW_AUTOINDEX);
    //     return true;
    // }
    // // is 'index' Keyword:
    // else if (FILE.compare(it - FILE.begin(), strlen(KW_DEFAULT_FILE), KW_DEFAULT_FILE) == 0) {
    //     it += strlen(KW_DEFAULT_FILE);
    //     return true;
    // }
    // // is 'location' Keyword:
    // else if (FILE.compare(it - FILE.begin(), strlen(KW_LOCATION), KW_LOCATION) == 0) {
    //     it += strlen(KW_LOCATION);
    //     return true;
    // }
    // // is 'root' Keyword:
    // else if (FILE.compare(it - FILE.begin(), strlen(KW_LOCATION_ROOT), KW_LOCATION_ROOT) == 0) {
    //     it += strlen(KW_LOCATION_ROOT);
    //     return true;
    // }
    return 0;
}