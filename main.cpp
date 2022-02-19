/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:54:12 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/13 09:30:12 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/webserv.hpp"

int     main(int argc, char *argv[])
{
    if (argc > 2)
        errorStream(ARGS_ERR, true, 1);
    else if (argc == 1)
        confParsing(DFLTCONF);
    else
        confParsing(argv[1]);
    return (0);
}
