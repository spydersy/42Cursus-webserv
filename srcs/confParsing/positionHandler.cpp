/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positionHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:34:11 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/06 21:51:27 by abelarif         ###   ########.fr       */
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

void    OUT_Position(std::string &FILE, std::string::iterator &it, std::vector<ServConfig> &vect, int *whereAmI)
{
    (void)vect;
    skipSpaces(FILE, it);
    if (it >= FILE.end()) {
        *whereAmI = EOF;
        return ;
    }
    if (FILE.compare(it - FILE.begin(), 6, KW_SERVER) == 0) {
        it+= 6;
        skipSpaces(FILE, it);
        if (FILE.compare(it - FILE.begin(), 1, "\n") == 0)
            it++;
        if (FILE.compare(it - FILE.begin(), 1, "{") == 0) {
            *whereAmI = SERVER;
            it++;
        }
        else {
            errorStream("File : Syntax Error", true, 1);
        }
        std::cout << "DBG CONTENT : [" << std::endl;
        while (it != FILE.end()) {
            std::cout << *it;
            it++;
        }
        std::cout << "]" << std::endl;
    }
}

void    SERVER_Position(std::string FILE, std::string::iterator &it, std::vector<ServConfig> &vect, int *whereAmI)
{
    (void)whereAmI;
    (void)vect;
    std::cout << *it << std::endl;
    skipSpaces(FILE, it);
    std::cout << *it << std::endl;}

void    LOCATION_Position(std::string FILE, std::string::iterator &it, std::vector<ServConfig> &vect, int *whereAmI)
{
    (void)whereAmI;
    (void)vect;
    std::cout << *it << std::endl;
    skipSpaces(FILE, it);
    std::cout << *it << std::endl;}

void    CGI_Position(std::string FILE, std::string::iterator &it, std::vector<ServConfig> &vect, int *whereAmI)
{
    (void)whereAmI;
    (void)vect;
    std::cout << *it << std::endl;
    skipSpaces(FILE, it);
    std::cout << *it << std::endl;
}
