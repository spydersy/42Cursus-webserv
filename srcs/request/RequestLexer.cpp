#include "RequestLexer.hpp"

RequestLexer::RequestLexer() {
	this->_requestLine = "";
	this->_headers = "";
	this->_lineSet = false;
	this->_headersSet = false;
}

RequestLexer::~RequestLexer() {
}

std::string		&RequestLexer::getRequestLine() {
	return this->_requestLine;
}

bool			&RequestLexer::getLineSet() {
	return this->_lineSet;
}

std::string		&RequestLexer::getHeaders() {
	return this->_headers;
}

bool			&RequestLexer::getHeadersSet() {
	return this->_headersSet;
}

void			RequestLexer::setLineSet() {
	this->_lineSet = true;
}

void			RequestLexer::setHeadersSet() {
	this->_headersSet = true;
}