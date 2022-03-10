#ifndef REQUESTLEXER_HPP
#define REQUESTLEXER_HPP
#include "Utils.hpp"
#define RECV_SIZE 4096

class RequestLexer {
	std::string				_requestLine;
	bool					_lineSet;
	std::string				_headers;
	bool					_headersSet;

	public:
		RequestLexer();
		RequestLexer( const RequestLexer &rqstL );
		~RequestLexer();
		RequestLexer 	&operator=( const RequestLexer &rqstL );

		// Getters
		std::string		&getRequestLine();
		bool			&getLineSet();
		std::string		&getHeaders();
		bool			&getHeadersSet();

		// change bool variables state
		void			setLineSet();
		void			setHeadersSet();
};

// std::ostream & operator<<( std::ostream & o, RequestLexer & rqstLexer ) {
// 	o << "Request Line: " << rqstLexer.getRequestLine() << " Headers:\n" << rqstLexer.getHeaders();
// 	return o;
// }

#endif