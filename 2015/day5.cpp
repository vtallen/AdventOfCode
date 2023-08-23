#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <regex>

namespace AOC2015 {
void day5(std::string_view inputFile) {
  
  std::ifstream inputStream{inputFile.data()};

  if (!inputStream) {
    std::cout << "Unable to open file: " << inputFile << '\n';
  }
 
  // Part 1 regex patterns
  // Checks if a string has 3 vowels
  std::regex ptOnePattern1{"[aeiou].*[aeiou].*[aeiou]"};
  // Checks if a string contains a repeated letter
  std::regex ptOnePattern2{R"(([a-z])\1)"};
  // Checks if a string contains ab, cd, pq, or xy 
  std::regex ptOnePattern3{"ab|cd|pq|xy"};

  // Part 2 regex patterns
  // Checks if the string contains pairs of any two letters that does not overlap 
  std::regex ptTwoPattern1{R"(([a-z][a-z]).*\1)"};
  // Checks if the string contains a pair of the same letter with exactly one letter inbetween
  std::regex ptTwoPattern2{R"(([a-z]).\1)"};

  int ptOneNiceStrings{0};
  int ptTwoNiceStrings{0};

  while (inputStream) {
    std::string line{};
    std::getline(inputStream, line);
    
    if (std::regex_search(line, ptOnePattern1) && std::regex_search(line, ptOnePattern2) && !std::regex_search(line, ptOnePattern3)) ++ptOneNiceStrings; 
    if (std::regex_search(line, ptTwoPattern1) && std::regex_search(line, ptTwoPattern2)) ++ptTwoNiceStrings; 
  }
  inputStream.close();

  std::cout << "2015 - Day 5(Part 1) - There are " << ptOneNiceStrings << " nice strings\n";
  std::cout << "2015 - Day 5(Part 2) - There are " << ptTwoNiceStrings << " nice strings\n";
}
}
