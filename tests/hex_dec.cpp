#include <iostream>     // std::cout, std::dec, std::hex, std::oct

int main () {
  std::string n = " \t700f";
  std::cout << std::dec << std::stoi(n) << '\n';
  std::cout << std::hex << std::stoi(n) << '\n';
  std::cout << std::oct << std::stoi(n) << '\n';
  return 0;
}