#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

class Request {
    private:
        typedef std::pair<std::string, std::string>		string_pair;
		std::string										method;
		std::string										path;
		std::string										query_string;
		std::string										version;
		std::string										host;
		int												port;
        std::vector<string_pair>						headers;
		std::string										bodyfilename;
		bool											error;

		// private methods
		// split request
		std::vector<string_pair>						splitRequest( std::string request );
	public:
		Request ();
		Request ( const Request &rqst );
		~Request ();
		Request											&operator= ( const Request &rqst );
		// Setters
		void											setRequest ( std::string &request );
		void											setMethod ( std::string &firstLine );
		void											setPath ( std::string &firstLine );
		void											setQuery ( std::string &firstLine );
		void											setVersion ( std::string &firstLine );
		void											setHost ( std::string &hostString );
		void											setPort ( std::string  portString );
		void											addHeader ( std::string header );
		// void											setHeaders ( std::vector<std::string> &headers );
		void											setBodyfile ( std::string filename );
		
		// Getters
		std::string										getMethod ();
		std::string										getPath ();
		std::string										getQuery ();
		std::string										getVersion ();
		std::string										getHost ();
		int												getPort ();
		std::vector<string_pair>						getHeaders ();
		std::string										getBodyfile ();
};

#endif