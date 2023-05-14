#include <iostream>
#include <fstream>
#include <string_view>
#include <string>

namespace AOC2015 {
void dayx(std::string_view inputFile) {
  std::ifstream inputStream{inputFile};

  if (!inputStream) {
    std::cout << "Unable to open file: " << inputFile << '\n';
  }

  while (inputStream) {

  }
}
}
