#include <string_view>
#include <iostream>
#include <fstream>

#include "AOC2015.h"

namespace AOC2015 {
void day1(std::string_view inputFile) {
  std::ifstream inputStream{inputFile.data()};
  
  if (!inputStream) {
    std::cout << "Unable to open: " << inputFile << '\n';
    return;
  }
  
  int currentFloor{0};
  int currentCharPosition{1};
  int firstEnteredBasementPosition{};
  bool hasEnteredBasement{false};

  while (inputStream) {
    char c{};
    inputStream >> c;

    if (c == '(') {
      ++currentFloor;
    } else if (c == ')') {
      --currentFloor;
    }
    
    if ((currentFloor == -1) && (!hasEnteredBasement)) {
      hasEnteredBasement = true;
      firstEnteredBasementPosition = currentCharPosition;
    }
    ++currentCharPosition;
  }
  
  std::cout << "2015 - Day 1 - The instructions take santa to floor ";
  std::cout << currentFloor << '\n';
  std::cout << "2015 - Day 1 - Santa first enters the basement at char " << firstEnteredBasementPosition << '\n';

  inputStream.close();
}
}
