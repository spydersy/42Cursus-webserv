#include <string>
#include <iostream>

int main() {
    std::string str = "e        fsdj hkfjsjkh jf skdjflk djfkj dslf   f     f";
    for (std::string::iterator it = str.begin(); *it == ' '; it++) {
        str.erase(it);
        it = str.begin();
    }
    if (*(str.begin()) == ' ')
        str.erase(str.begin());
    for (std::string::iterator it = str.end() - 1; *it == ' '; it--) {
        str.erase(it);
    }
    std::cout << "Result: " << str << std::endl;
}