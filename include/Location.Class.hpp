/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:57:42 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/13 07:45:08 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_CLASS_HPP
#define LOCATION_CLASS_HPP

#include <iostream>
#include <vector>

# define METH_GET           1
# define METH_POST          10
# define METH_DELETE        100

class Location
{
private:
    std::string                 _locations_path;
    std::vector<std::string>    _methods;
    std::string                 _root;
    std::string                 _client_max_body_size;
    std::vector<std::string>    _index;
    std::string                 _autoindex;
public:
    Location(): _locations_path(""),
                _methods(std::vector<std::string>()),
                _root(""),
                _client_max_body_size(""),  
                _index(std::vector<std::string>()),
                _autoindex("") {}
    
    ~Location() {}

    std::string                 &get_locations_path() { return this->_locations_path; }
    std::vector<std::string>    &get_methods() { return this->_methods; }
    std::string                 &get_root() { return this->_root; }
    std::string                 &get_autoindex() { return this->_autoindex; }
    std::string                 &get_client_max_body_size() { return this->_client_max_body_size; }
    std::vector<std::string>    &get_index() { return this->_index; }

};

#endif
