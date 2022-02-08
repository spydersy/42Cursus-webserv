/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileHandlerUtils.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 22:22:37 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/08 02:39:04 by abelarif         ###   ########.fr       */
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

int    validatedKeyword(std::string &FILE, std::string::iterator &it)
{
    // is 'server_name' Keyword:
    std::cout << KYEL << "KYWRD: [" << *(it + 0) << *(it + 1) << *(it + 2) << *(it + 3) << *(it + 4) << *(it + 5) << *(it + 6) << "]" << KNRM << std::endl;
    if (FILE.compare(it - FILE.begin(), strlen(KW_SERVER_NAME), KW_SERVER_NAME) == 0) {
        it += strlen(KW_SERVER_NAME);
        return KW_SERVER_NAME_VALUE;
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
    return 0;
}

void    printServer(std::vector<Server> server)
{
    for (std::vector<Server>::iterator   it = server.begin(); it != server.end(); it ++)
    {
        std::cout << "************************************" << std::endl;
        it->dbgServer();
    }
}