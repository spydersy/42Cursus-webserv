/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.Class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:06:45 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/04 23:17:21 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOINDEX_CLASS_HPP
#define AUTOINDEX_CLASS_HPP

#include "./webserv.hpp"

class autoindex
{
private:
    std::string     _path;
    std::string     _page;
    void            generatePage( void );
public:
    // Constructors & Ddestructors : 
    autoindex(std::string path);
    ~autoindex();
    // Getters : 
    std::string get_page();
};

autoindex::autoindex( std::string path) :   _path(path),
                                            _page("") {
    this->_page.append("<html>\r\n");
    this->_page.append(" <style>\r\n");
    this->_page.append(" th {\r\n");
    this->_page.append("     text-align: left;\r\n");
    this->_page.append(" }\r\n");
    this->_page.append(" </style>\r\n");
    this->_page.append("<head><title>Index of " + this->_path + "</title></head>\r\n");
    this->_page.append("<body>\r\n");
    this->_page.append("<h1>Index of " + this->_path + "</h1><hr><pre>\r\n");
    this->_page.append("<table style=\"width:100%\">\r\n");
    this->_page.append("<tr>\r\n");
    this->_page.append("<th>Name</th>\r\n");
    this->_page.append("<th>Size</th>\r\n");
    this->_page.append("<th>Date</th>\r\n");
    this->_page.append("</tr>\r\n");
    generatePage();
}
autoindex::~autoindex(){}

void    autoindex::get_page(){
    DIR                 *d;

}

std::string autoindex::get_page() { return this->_page; }

#endif