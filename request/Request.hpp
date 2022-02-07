#ifndef REQUEST_CLASS_HPP
#define REQUEST_CLASS_HPP

#include <iostream>
#include <vector>
#include <utility>

class Request {
    private:
        typedef std::pair<std::string, std::string>		string_pair;
		std::string										method;
		std::string										path;
		std::string										query_string;
		std::string										version;
        std::vector<string_pair>						headers;
		std::string										body;
	public:
		Request();
		~Request();
		void	setRequest(std::string request);
};

#endif