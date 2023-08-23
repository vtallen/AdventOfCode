#include "AOC2015.h" 

#include <sstream>
#include <string_view>
#include <iostream>
#include <fstream>

namespace AOC2015 {

std::string lookAndSay(std::string_view inputLine, int iteration) {
  std::stringstream sstream{};
  std::string newInput{}; 

  // Iterate over the whole input line
  for (int i{0}; i < inputLine.length(); ++i) {
    char currentChar{inputLine[i]};
    
    // Now check how many occuraces in a row there are for the number
    // Each time an occurace is found, we should jump i to that index
    // to avoid double counting
    int occuraces{1};
    for (int j{i + 1}; j < inputLine.length(); ++j) {
      char nextChar{inputLine[j]}; 

      if (currentChar == nextChar) {
        ++occuraces;
        i = j;
      } else {
        break;
      }

    }
    // std::cout << occuraces << " occuraces of " << currentChar << '\n';
    sstream << occuraces << currentChar;
  }
  
  sstream >> newInput;

  if (iteration == 1) {
    return newInput; 
  } else {
    return lookAndSay(newInput, iteration - 1);
  }
}

void day10(std::string_view inputFile) {
  std::ifstream input{inputFile.data()};

  std::string inputLine{};
  std::getline(input, inputLine);
  
  std::string partOneResult{lookAndSay(inputLine, 40)}; 
  std::string partTwoResult{lookAndSay(inputLine, 50)}; 

  std::cout << "AOC 2015 - Day 10 - Part 1 - The phrase is " << partOneResult.length() << " digits long\n";
  std::cout << "AOC 2015 - Day 10 - Part 2 - The phrase is " << partTwoResult.length() << " digits long\n";

}
}
