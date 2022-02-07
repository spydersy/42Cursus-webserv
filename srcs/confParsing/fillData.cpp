/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:02:09 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/07 20:07:24 by abelarif         ###   ########.fr       */
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

void    fill_server_name(std::string &FILE, std::string::iterator &it, std::vector<Server> &vect, int whereAmI)
{
    std::vector<std::string> content;

    if (whereAmI || vect.size()) {}
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_SERVER_NAME, true, 1);
    skipSpaces(FILE, it);
    if (*it == '\n')
        errorStream(KW_SERVER_NAME, true, 1);
    while (it < FILE.end() && *it != '\n') {
        // vect[vect.size() - 1].get_server_names().push_back()
        content.push_back(getToken(FILE, it));
        if (*it != '\n')
            skipSpaces(FILE, it);
    }
    std::cout << KGRN << "TOKENS: ";
    for (std::vector<std::string>::iterator it = content.begin(); it != content.end(); it++)
    {
        std::cout << "[" << *it << "]";
    }
    std::cout << KNRM << std::endl;
    exit(0);
}