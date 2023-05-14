#include <algorithm>
#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <vector>

namespace AOC2015 {
void part1(std::string_view inputFile) {
  std::ifstream inputStream{inputFile};

  if (!inputStream) {
    std::cout << "Unable to open file: " << inputFile << '\n';
  }
  
  // For each movement, the x and y will be changed. The visitedCoords vector will be checked to see
  // if it contains that coordinate already. If it doesn't, the visitedHouses will be incremented
  // and the coordinate will be added to the vector. If the coordinate is found in the vector, the 
  // house will be ignored.
  
  // Normal Santa's location
  int x{0};
  int y{0};
  
  std::vector<std::string> visitedCoords;
  visitedCoords.push_back("0,0");
  int uniqueHousesVisisted{1};
  

  while (inputStream) {
    char direction{};
    inputStream >> direction;
    
    std::string currentCoordinate{};
    
    switch(direction) {
      // North
      case '^':
        ++y;
        break;
      // South 
      case 'v':
        --y;
        break;
      // East 
      case '>':
        ++x;
        break;
      // West
      case '<':
        --x;
        break;
    }

    currentCoordinate.append(std::to_string(x)).append(",").append(std::to_string(y));

    if (std::any_of(visitedCoords.begin(), visitedCoords.end(), [currentCoordinate](std::string coord){
      return currentCoordinate == coord; 
    })) {
        // std::Cout << "Exists\n"
    } else {
      // std::cout << "Does not exist\n";
      visitedCoords.push_back(currentCoordinate);
      ++uniqueHousesVisisted;
    }

  }

  std::cout << uniqueHousesVisisted << " houses were visisted\n";
}

void day3(std::string_view inputFile) {
  part1(inputFile);
  std::ifstream inputStream{inputFile};

  if (!inputStream) {
    std::cout << "Unable to open file: " << inputFile << '\n';
  }
  
  // For each movement, the x and y will be changed. The visitedCoords vector will be checked to see
  // if it contains that coordinate already. If it doesn't, the visitedHouses will be incremented
  // and the coordinate will be added to the vector. If the coordinate is found in the vector, the 
  // house will be ignored.
  
  // Normal Santa's location
  int x{0};
  int y{0};
  
  // Robo-santa's location
  int rx{0};
  int ry{0};
  std::vector<std::string> visitedCoords;
  visitedCoords.push_back("0,0");
  int uniqueHousesVisisted{1};
  
  bool isRoboSantaTurn{false};

  while (inputStream) {
    if (isRoboSantaTurn) std::cout << "ROBO\n";
    else std::cout << "NORMAL\n";
    char direction{};
    inputStream >> direction;
    
    std::string currentCoordinate{};
    
    switch(direction) {
      // North
      case '^':
        if (isRoboSantaTurn) ++ry;
        else ++y;
        break;
      // South 
      case 'v':
        if (isRoboSantaTurn) --ry;
        else --y;
        break;
      // East 
      case '>':
        if (isRoboSantaTurn) ++rx;
        else ++x;
        break;
      // West
      case '<':
        if (isRoboSantaTurn) --rx;
        else --x;
        break;
    }

    if (isRoboSantaTurn) {
      currentCoordinate.append(std::to_string(rx)).append(",").append(std::to_string(ry));
    } else {
      currentCoordinate.append(std::to_string(x)).append(",").append(std::to_string(y));
    }

    std::cout << currentCoordinate << '\n';

    if (std::any_of(visitedCoords.begin(), visitedCoords.end(), [currentCoordinate](std::string coord){
      return currentCoordinate == coord; 
    })) {
        // std::Cout << "Exists\n"
    } else {
      // std::cout << "Does not exist\n";
      visitedCoords.push_back(currentCoordinate);
      ++uniqueHousesVisisted;
    }

    if (isRoboSantaTurn) {
      isRoboSantaTurn = false;
    } else {
      isRoboSantaTurn = true;
    }
  }

  std::cout << uniqueHousesVisisted << " houses were visisted\n";
}
}
