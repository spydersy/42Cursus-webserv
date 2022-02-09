// #include "Request.hpp"
// #include "Utils.hpp"
#include "../response.hpp"

void requestHandler(std::string rqstLine, int sock)
{
    std::cout << KBLU << "------------------ START: REQUEST_HANDLER -------------------" << std::endl;
    Request rqst;
    std::vector< std::string > parts;
    std::vector< std::string > headers;
    std::vector< std::string > body;

    // std::string rqstLine = "GET / HTTP/1.1\nHost: localhost:8080\nConnection: keep-alive\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.14; rv:94.0) Gecko/20100101 Firefox/94.0\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate\nUpgrade-Insecure-Requests: 1\nSec-Fetch-Dest: document\nSec-Fetch-Mode: navigate\nSec-Fetch-Site: none\nSec-Fetch-User: ?1\n\n{\n\"name\": \"LACH\",\n\"surname\": \"amine\"\n}\n";
    
    parts = StringSplit(rqstLine, "\n");
    rqst.setMethod(parts[0]);
    rqst.setPath(parts[0]);
    rqst.setVersion(parts[0]);
    std::cout << "Method: " << rqst.getMethod() << ", Host: " << rqst.getHost() << ", Port: " << rqst.getPort() << ", Path: " << rqst.getPath() << ", Version: " << rqst.getVersion() << std::endl;
    parts.erase(parts.begin());
    std::vector<std::string>::iterator it;
    for ( it = parts.begin(); it != parts.end(); it++) {
        if ((*it).find(":") != std::string::npos) {
            headers.push_back(*it);
            continue;
        }
        break ;
    }

    for (std::vector< std::string >::iterator it = headers.begin(); it != headers.end(); it++) {
		std::cout << *it << std::endl;
	}
    std::cout << "------------------   END: REQUEST_HANDLER -------------------" << KNRM << std::endl;
    responseHandler(rqst, sock);
}
