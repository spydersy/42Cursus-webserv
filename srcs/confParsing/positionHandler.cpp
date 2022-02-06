/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positionHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:34:11 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/06 17:56:41 by abelarif         ###   ########.fr       */
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
    std::string::size_type     position;

    (void)vect;
    skipSpaces(FILE, it);
    if (it >= FILE.end()) {
        *whereAmI = EOF;
        return ;
    }
    // FILE.find(KW_SERVER, 6, it - FILE.begin());
    
    // if ((position = FILE.find(KW_SERVER, it - FILE.begin(), 6)) != std::string::npos) {
    //     std::cout << "true : " << position << std::endl;
    //     exit(21);   
    // }
    // else {
    //     std::cout << "false" << std::endl;
    // }
    if ((position = FILE.compare(it - FILE.begin(), 6, KW_SERVER)) == 0) {
        std::cout << "true" << std::endl;
        
    } else {
        std::cout << "false" << std::endl;
    }
    exit(0);
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
