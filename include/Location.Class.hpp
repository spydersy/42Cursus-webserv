/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:57:42 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/10 04:49:14 by abelarif         ###   ########.fr       */
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
    int                         _client_body_buffer_size;
    std::vector<std::string>    _index;
public:
    Location(): _locations_path(""),
                _methods(std::vector<std::string>()),
                _root(""),
                _client_body_buffer_size(0),  
                _index(std::vector<std::string>()) {}
    
    ~Location() {}

    std::string                 &get_locations_path() { return this->_locations_path; }
    std::vector<std::string>    &get_methods() { return this->_methods; }
    std::string                 &get_root() { return this->_root; }
    int                         &get_client_body_buffer_size() { return this->_client_body_buffer_size; }
    std::vector<std::string>    &get_index() { return this->_index; }

};

#endif
