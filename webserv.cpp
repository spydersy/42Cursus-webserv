/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:02:22 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/02 22:58:17 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/webserv.hpp"

int webserv(int argc, char **argv)
{
    
    if (argc > 2)
        errorStream(ARGS_ERR, true, 1);
    else if (argc == 1)
        confParsing(DFLTCONF);
    else
        confParsing(argv[1]);
    return (0);
}