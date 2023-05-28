#include <iostream>
#include <fstream>
#include <string_view>
#include <string>

#include "../AOCHelpers/AOCHelpers.h"

namespace AOC2015 {
enum class LightAction {
  TURN_ON,
  TURN_OFF,
  TOGGLE,
};

void drawRectangle(bool **lightsMatrix, int width, int height, LightAction action, int x1, int y1, int x2, int y2) {
  if ((x1 >= width) || (y1 >= height) || (x2 >= width) || (y2 >= height)) {
    std::cout << "Tried to draw a rectangle outside the matrix" << '\n';
    return;
  }
  
  for (int y{y1}; y <= y2; ++y) {
    for (int x{x1}; x <= x2; ++x) {
      if (action == LightAction::TURN_ON) {
        lightsMatrix[y][x] = true;
      } else if (action == LightAction::TURN_OFF) {
        lightsMatrix[y][x] = false;
      } else if (action == LightAction::TOGGLE) {
        lightsMatrix[y][x] = (lightsMatrix[y][x] == true) ? false : true;
      }
    }
  }

}

void printMatrix(bool **lightsMatrix, int width, int height) {
  for (int y{0}; y < height; ++y) {
    for (int x{0}; x < width; ++x) {
      std::cout << lightsMatrix[y][x] << " ";
    }
    std::cout << '\n';
  }
}

int numLightsOn(bool **lightsMatrix, int width, int height) {
  int numLights{};
  for (int y{0}; y < height; ++y) {
    for (int x{0}; x < width; ++x) {
      if (lightsMatrix[y][x] == true) ++numLights;
    }
  }
  return numLights;
}

void day6(std::string_view inputFile) {
  std::ifstream inputStream{inputFile};

  if (!inputStream) {
    std::cout << "Unable to open file: " << inputFile << '\n';
  }
  
  // Create the matrix for the lights. Doing this as a normal array since we know the
  // dimensions. We will have to allocate heap memory as we can't create this on the stack while also being able to pass it into a function.
  constexpr int rows = 1000;
  constexpr int cols = 1000;

  bool** lights {new bool*[rows]};

  for (int i = 0; i < rows; ++i) {
    lights[i] = new bool[cols];
  }
  
  while (inputStream) {
    std::string line;
    std::getline(inputStream, line);
    
    std::vector<std::string> splitLine{AOCHelpers::splitString(line, " ")};

    // PART ONE
    // if the length of the split input line is 4,
    // we know that we need to toggle, otherwise we need to do an on or off action
    if (splitLine.size() == 4) {
      // Split the string again at ',' to get two ordered pairs
      std::vector<std::string> orderedPairOne{AOCHelpers::splitString(splitLine.at(1), ",")}; 
      std::vector<std::string> orderedPairTwo{AOCHelpers::splitString(splitLine.at(3), ",")};

      drawRectangle(lights, 1000, 1000, LightAction::TOGGLE, std::stoi(orderedPairOne[0]), std::stoi(orderedPairOne[1]), std::stoi(orderedPairTwo[0]), std::stoi(orderedPairTwo[1]));

    } else if (splitLine.size() == 5) {

      std::vector<std::string> orderedPairOne{AOCHelpers::splitString(splitLine[2], ",")};
      std::vector<std::string> orderedPairTwo{AOCHelpers::splitString(splitLine[4], ",")};
      std::string action{splitLine[1]};

      if (action == "on") {
        drawRectangle(lights, 1000, 1000, LightAction::TURN_ON, std::stoi(orderedPairOne[0]), std::stoi(orderedPairOne[1]), std::stoi(orderedPairTwo[0]), std::stoi(orderedPairTwo[1]));
      }
      else if (action == "off") {
        drawRectangle(lights, 1000, 1000, LightAction::TURN_OFF, std::stoi(orderedPairOne[0]), std::stoi(orderedPairOne[1]), std::stoi(orderedPairTwo[0]), std::stoi(orderedPairTwo[1]));
      }

    }
  }

  inputStream.close();

  std::cout << "2015 - Day 6 - Part 1 - There are " << numLightsOn(lights, 1000, 1000) << " lights turned on\n";

// Deallocate the matrix of lights
  for (int i = 0; i < rows; ++i) {
    delete[] lights[i];
  }
  delete[] lights;

}
}
