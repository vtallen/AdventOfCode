#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
namespace AOC2015 {

// This function was found at https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void findHash(const int numZeros, std::string &secretKey, bool verbose) {
  std::cout << "Finding hashes for " << secretKey << " that start with " << numZeros << " zeros\n";
  int currentNumber{0};
  bool isHashFound{false};
 
  std::string md5Command{"md5 -s "};
  std::string zeros(numZeros, '0');

  while (true) {
    std::string command{md5Command + secretKey + std::to_string(currentNumber)}; 
    
    std::string commandResult{exec(command.c_str())};
    std::size_t delimiterIndex{commandResult.find("=")};

    std::string hash{commandResult.substr(delimiterIndex + 2, commandResult.length())};

    std::string firstCharacters{hash.substr(0, numZeros)};
    
    if (verbose) {
      std::cout << "Hash: " << hash; 
      std::cout << "First chars: " << firstCharacters << '\n';
    } 
    if (firstCharacters == zeros) {
      break;
    }
    ++currentNumber;
  }
  std::cout << "2015 - Day 4 - The first number that combines with the secret key to get " << numZeros << " zeros is "<< currentNumber << '\n'; 
}

void day4(std::string_view inputFile) {
  std::ifstream inputStream{inputFile};

  if (!inputStream) {
    std::cout << "Unable to open file: " << inputFile << '\n';
  }
  
  std::string secretKey{};
  std::getline(inputStream, secretKey);
  
  findHash(5, secretKey, false);
  findHash(6, secretKey, false);
  // stringStream >> secretKey;
/*
  int currentNumber{0};
  bool isHashFound{false};
 
  std::string md5Command{"md5 -s "};
  while (!isHashFound) {
    std::string command{md5Command + secretKey + std::to_string(currentNumber)}; 
    // std::string command{md5Command + std::string{"pqrstuv1048970"}};
    std::string commandResult{exec(command.c_str())};
    std::size_t delimiterIndex{commandResult.find("=")};

    std::string hash{commandResult.substr(delimiterIndex + 2, commandResult.length())};

    std::string firstFiveCharacters{hash.substr(0, 6)};
     
    std::cout << "Hash: " << hash; 
    std::cout << "First chars: " << firstFiveCharacters << '\n';
    
    if (firstFiveCharacters == "000000") {
      isHashFound = true;
      break;
    }
    ++currentNumber;
  }

  std::cout << '\n' << currentNumber << '\n';


*/
}
}

