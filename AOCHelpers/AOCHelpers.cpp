#include "AOCHelpers.h"


namespace AOCHelpers {

std::vector<std::string> splitString(std::string string, std::string_view delimiter) {
  if (string.length() <= 2) {
    // throw std::invalid_argument("String is not long enough to split");
    return {};
  }

  bool endOfString{false}; 
  std::vector<std::string> result{};

  while (!endOfString) {
    // Find the first occurance of the delimiter, if it exists.
    auto delimiterIndex{string.find(delimiter)};

    if ((delimiterIndex != std::string::npos)) {
      // Create a substring up until the delimiter, then erase the substring and delimiter from the string. 
      std::string current{string.substr(0, delimiterIndex)};
      string.erase(0, delimiterIndex + 1);

      result.push_back(current);

      // std::cout << "CurrentSlice:" << current << '\n';
      // std::cout << "CURRENT LEN:" << current.length() << '\n';
    } else {
      // Here we are checking if there is still data past the last delimiter that needs to be added to the result vector
      if (string.length() >= 1) {
        result.push_back(string);
      }
      endOfString = true;
    }
  }

    return result;
  }
}
