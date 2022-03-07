#include <iostream>     // std::cout, std::dec, std::hex, std::oct
#include <sstream>
int main () {
  int n;
  std::istringstream(" 700f") >> std::hex >> n;
  std::cout << n << '\n';
  return 0;
}