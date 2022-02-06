/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isEmptyLine.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:41:01 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/06 14:32:31 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

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