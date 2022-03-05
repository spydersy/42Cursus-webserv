/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.Class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:06:45 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/05 16:23:13 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOINDEX_CLASS_HPP
#define AUTOINDEX_CLASS_HPP

#include "./webserv.hpp"
#include<iostream>
#include<fstream>
#include <dirent.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <iomanip>

class autoindex
{
private:
    std::string     _path;
    std::string     _page;
    void            generatePage( void );
    int             getFileSize(std::string file);
    std::string     getFileDate(std::string file);
    std::string     getFilePermissions(std::string file);
public:
    // Constructors & Ddestructors : 
    autoindex(std::string path);
    ~autoindex();
    // Getters : 
    std::string     get_page();
};

#endif