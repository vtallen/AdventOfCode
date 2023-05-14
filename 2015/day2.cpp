#include <algorithm>
#include <numeric>
#include <sstream>
#include <string_view>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace AOC2015 {
void day2(std::string_view inputFile) {

  std::ifstream inputStream{inputFile.data()};
 
  if (!inputStream) {
    std::cout << "Unable to open: " << inputFile << '\n';
    return;
  }
  
  std::string line;
  std::string delimiter{'x'}; // This will allow us to split each line into dimensions
  long totalWrappingPaperArea{};
  long totalRibbion{};

  while (std::getline(inputStream, line)) {
    std::stringstream stringStream;
    
    std::size_t delimiterIndex{line.find(delimiter)};
    stringStream << line.substr(0, delimiterIndex);
    
    // First we are going to extract each dimension.
    // This works by finding where the 'x' is, putting that substring into a stringstrem, then extracting from the string stream into
    // an int. After this the number we have parsed gets removed from the string so that the next number can be parsed.
    
    int l{};
    stringStream >> l;
    line.erase(0, delimiterIndex + 1);
    stringStream.clear();

    int w{};
    delimiterIndex = line.find(delimiter);
    stringStream << line.substr(0, delimiterIndex);
    stringStream >> w;
    line.erase(0, delimiterIndex + 1);
    stringStream.clear();

    int h{};
    delimiterIndex = line.find(delimiter);
    stringStream << line.substr(0, delimiterIndex);
    stringStream >> h;
    stringStream.clear();

    // std::cout << "Sides: " << l << " " << w << " " << h << '\n';

    std::vector<int> sidesArea {
      l*w,
      w*h,
      h*l
    };

    std::vector<int> sidesPerimiter {
      l+l+w+w,
      l+l+h+h,
      h+h+w+w
    };

    int volume{l*w*h};

    int smallestSideArea{*std::min_element(sidesArea.begin(), sidesArea.end())};
    int smallestSidePerimiter{*std::min_element(sidesPerimiter.begin(), sidesPerimiter.end())};

    // std::cout << "Area of sides: " << sidesArea[0] << " " << sidesArea[1] << " " << sidesArea[2] << '\n';
    // std::cout << "Smallest side: " << smallestSideArea << '\n' << '\n';
    
    int neededWrappignPaper{(sidesArea[0] * 2) + (sidesArea[1] * 2) + (sidesArea[2] * 2) + smallestSideArea};
    int neededRibbon{smallestSidePerimiter + volume};

    totalWrappingPaperArea += neededWrappignPaper;
    totalRibbion += neededRibbon;

    stringStream.clear();
  }

  std::cout << "2015 - Day 2 - Needed wrapping paper: " << totalWrappingPaperArea << '\n';
  std::cout << "2015 - Day 2 - Needed ribbion: " << totalRibbion << '\n';
}
}
