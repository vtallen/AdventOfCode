#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <regex>

namespace AOC2015 {
void day8(std::string_view inputFile) {
  std::ifstream inputStream{inputFile.data()};

  if (!inputStream) {
    std::cout << "Unable to open file: " << inputFile << '\n';
  }
  
  int charsInCode{0};
  int charsInMemory{0};
  int charsInNewStrings{0};

  std::regex strLiteralRegex{R"([a-z]|(\\")|(\\\\)|(\\x([0-9a-f]{2})))"};
  auto tokenListEnd = std::sregex_iterator();

  while (inputStream) {
    std::string line;
    std::getline(inputStream, line);
    if (line == "") continue;
    
    auto tokenList = std::sregex_iterator{line.begin(), line.end(), strLiteralRegex};
    
    for (std::sregex_iterator i = tokenList; i != tokenListEnd; ++i) {
      std::smatch match = *i;
      std::string match_str{match.str()};
      
      // Accounting for the extra characters added by the new encodeing for strings. We're basically escaping every special character like \ or "   
      if (match_str.length() == 4) ++charsInNewStrings;
      if (match_str == "\\\"") charsInNewStrings += 2;
      if (match_str == "\\\\") charsInNewStrings += 2;

      ++charsInMemory;
    }
    charsInCode += line.length();

    // Accounting for the characters added by the new encoding for "
    charsInNewStrings += line.length() + 4;
  }

  std::cout << "2015 - Part 1 - Chars in code - chars in memory: " << charsInCode - charsInMemory << '\n';
  std::cout << "2015 - Part 1 - Chars in code - chars in new encoding: " << charsInNewStrings - charsInCode << '\n';
}
}
