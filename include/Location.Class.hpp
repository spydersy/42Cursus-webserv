/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:57:42 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/06 14:29:38 by abelarif         ###   ########.fr       */
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
    std::vector<std::string>    _locations_path;
    unsigned int                _methods;
    std::string                 _root;
    int                         _client_body_buffer_size;
    std::vector<std::string>    _index;
    int                         _location_level;
public:
    Location() : _methods(0), _client_body_buffer_size(0), _location_level(1) {
        std::cout << "Location Constructor Called" << std::endl;
        if (_methods || _client_body_buffer_size || _location_level) {}
    }
    ~Location() {
        std::cout << "Location Destructor Called" << std::endl;
    }
};

#endif
