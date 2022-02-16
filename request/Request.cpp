#include "Request.hpp"

Request::Request (): error(false) {}

Request::Request (const Request &rqst ) {
	*this = rqst;
}

Request::~Request () {}

Request	&Request::operator= ( const Request &rqst ) {
	this->method = rqst.method;
	this->path = rqst.path;
	this->query_string = rqst.query_string;
	this->version = rqst.version;
	this->host = rqst.host;
	this->port = rqst.port;
	this->headers = rqst.headers;
	this->error = rqst.error;

	return *this;
}

void	Request::setRequest(std::string &request) {
	
}

void		Request::setMethod ( std::string &firstLine ) {
	if (firstLine.find(' ') != std::string::npos) {
		this->method = firstLine.substr(0, firstLine.find(' '));
		// test for supported methods
		firstLine.erase(0, firstLine.find(' ') + 1);
	}
	else {
		this->error = true;
	}
}

void		Request::setPath ( std::string &firstLine ) {
	if (firstLine.find("http://") != std::string::npos && firstLine.find("http://") == 0) {
		firstLine.erase(0, 7);
		std::string	tmpHost = firstLine.substr(0, firstLine.find("/"));
		firstLine.erase(0, firstLine.find("/"));
		this->setHost(tmpHost);
	}
	if (firstLine.find(' ') != std::string::npos) {
		this->path = firstLine.substr(0, firstLine.find(' '));
		// test for supported methods
		firstLine.erase(0, firstLine.find(' ') + 1);
	}
	if (this->path[0] != '/') {
		this->path = "/" + this->path;
	}
	else {
		this->error = true;
	}
}

void		Request::setQuery ( std::string &firstLine ) {

}

void		Request::setVersion ( std::string &firstLine ) {
	if (firstLine.length() > 0) {
		this->version = firstLine;
	}
	else {
		this->error = true;
	}
}

void		Request::setHost ( std::string &hostString ) {
	if (hostString.find(':') != std::string::npos) {
		std::string tmpPort = hostString.substr(hostString.find(':') + 1);
		this->setPort(tmpPort);
		this->host = hostString.substr(0, hostString.find(':'));
	}
	else {
		this->host = hostString;
		this->setPort("");
	}
}

void		Request::setPort ( std::string  portString ) {
	if (portString != "") {
		this->port = std::stoi(portString);
	}
	else {
		this->port = 80;
	}
}

void		Request::addHeader ( std::string header ) {
	std::string key = header.substr(0, header.find(":"));
	std::string value = header.substr(header.find(":") + 1);
	this->headers.push_back(std::make_pair(key, value));
}

void		Request::setBodyfile ( std::string filename ) {
	this->bodyfilename = filename;
}



std::string		Request::getMethod () {
	return this->method;
}

std::string		Request::getPath () {
	return this->path;
}

std::string		Request::getVersion () {
	return this->version;
}

std::string		Request::getHost () {
	return this->host;
}

int				Request::getPort () {
	return this->port;
}

std::string		Request::getBodyfile () {
	return this->bodyfilename;
}

// std::pair< std::string, std::ofstream & >		Request::getRequestfile () {
// 	return this->requestfile;
// }

// std::vector<std::pair<std::string, std::string> >	Request::splitRequest( std::string request ) {
	
// }