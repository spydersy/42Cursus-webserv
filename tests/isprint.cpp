#include <iostream>     // std::cout, std::dec, std::hex, std::oct

int main () {
  for (int i = 0; i < 128; i++) {
      if (isprint(i)) {
          std::cout << (char)i << ", ";
      }
  }
  std::cout << std::endl;
  return 0;
}