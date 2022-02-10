#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

int main() {
    std::vector<std::string> parts;
    std::string str = "fhjksdjhf; ;;fsd fdsfdsfds;fds;fsd;fds;f;dsfdsfdsfds;fds;dsf;dsf;sd;ds;f;d;fds ;fds;f;";
    while (str.length() && str.find(";") != std::string::npos) {
        std::string tmp = str.substr(0, str.find(";"));
        if (tmp.length() > 0) {
            parts.push_back(tmp);
        }
        str.erase(0, str.find(";") + 1);
    }
    if (str.length() > 0) {
        parts.push_back(str);
    }

    for (std::vector<std::string>::iterator it = parts.begin(); it != parts.end(); it++) {
        std::cout << *it << std::endl;
    }
    return (0);
}