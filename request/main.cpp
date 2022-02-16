#include "Request.hpp"
#include "Utils.hpp"

int main() {
	Request rqst;
	std::vector< std::string >	parts;
	std::ofstream				bodyFile("request_1Body.txt", std::ofstream::out);
	std::ifstream				requestFile("request_2.txt", std::ifstream::in);
	std::string					rqstLine;
	getline(requestFile, rqstLine);
	std::cout << rqstLine << std::endl;
	rqst.setMethod(rqstLine);
	rqst.setPath(rqstLine);
	rqst.setVersion(rqstLine);

	while (getline(requestFile, rqstLine)) {
		if (rqstLine == "\r") {
			std::cout << "end of headers" << std::endl;
			break ;
		}
		else {
			rqst.addHeader(rqstLine);
		}
	}
	while (getline(requestFile, rqstLine)) {
		bodyFile << rqstLine << std::endl;
	}
	rqst.setBodyfile("request_1Body.txt");
	return (0);
}