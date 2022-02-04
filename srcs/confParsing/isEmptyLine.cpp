/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isEmptyLine.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:41:01 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/04 22:43:09 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

bool    isEmptyLine(std::string line)
{
    int     i = -1;
    if (line.length() == 0)
        return 1;
    while (line[++i])
        if (line[i] != ' ' && line[i] != '\t')
            return (false);
    return true;
}