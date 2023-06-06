#ifndef AOCHelpers_H
#define AOCHelpers_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <string_view>

namespace AOCHelpers {

template<typename T>
bool isConvertableToNum(const std::string &string) {
  std::istringstream ss{string};
  T value;
  char remainingChars;
  return (ss >> value) && !(ss >> remainingChars);
}

std::vector<std::string> splitString(std::string string, std::string_view delimiter);
}

#endif
