#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

int main() {
    std::vector<std::string> parts;
    std::string str = "fhjksdjhf;fsd fdsfdsfds;fds;fsd;fds;f;dsfdsfdsfds;fds;dsf;dsf;sd;ds;f;d;fds ;fds;f";
    while (str.length() && str.find(";") != std::string::npos) {
        parts.push_back(str.substr(0, str.find(";")));
        str.erase(0, str.find(";") + 1);
    }
    parts.push_back(str);

    for (std::vector<std::string>::iterator it = parts.begin(); it != parts.end(); it++) {
        std::cout << *it << std::endl;
    }
    return (0);
}