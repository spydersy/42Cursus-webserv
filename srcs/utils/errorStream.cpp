/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorStream.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:14:04 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/02 23:08:44 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

void    errorStream(std::string description, bool EXIT_FLAG, int value)
{
    std::cerr << KRED<< "Error: " << description << KNRM << std::endl;
    if (EXIT_FLAG == true)
        exit(value);
}
