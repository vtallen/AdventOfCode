#include <string_view>
#include <string>
#include <thread>
#include <mutex>
#include <array>
#include <iostream>
#include <fstream>
#include <vector>

#include "../AOCHelpers/md5.h"

namespace AOC2015 {

std::string secretKey{};

std::mutex g_lock;
long result{};
bool isHashFound{false};
int numZeros{5};

void findHash(int startNum) {
  long currentNum{startNum};
  
  static std::string md5Command{"md5 -s "};
  std::string zeros(numZeros, '0');

  while (!isHashFound) {
    std::string hash{md5(secretKey + std::to_string(currentNum))};
    std::string firstChars{hash.substr(0, numZeros)};
    
    // std::cout << std::this_thread::get_id() << " " << hash << '\n'; 
    if (firstChars == zeros) {
      g_lock.lock();
      isHashFound = true;
      result = currentNum;
      g_lock.unlock();
    }
    ++currentNum;
  }
}

void day4(std::string_view inputFile) {
  std::ifstream inputStream{inputFile};

  if (!inputStream) {
    std::cout << "Unable to open " << inputFile << '\n';
  }
  
  std::getline(inputStream, secretKey);

  std::vector<std::thread> threads;

  for (int i{0}; i < 60; ++i) {
    threads.push_back(std::thread(&findHash, i * 10000));
  }
  for (auto &thread : threads) {
    thread.join();
  }
  
  long part1Result{result};

  // Reset our global variables to solve part 2
  isHashFound = false;
  result = 0;
  numZeros = 6;
  threads.clear();

  for (int i{0}; i < 100; ++i) {
    threads.push_back(std::thread(&findHash, i * 100'000));  
  }
  for (auto &thread : threads) {
    thread.join();
  }

  long part2Result{result};

  std::cout << "2015 - Day 4 - Part 1: The number resulting in a hash starting with 00000 is: " << part1Result << '\n';
  std::cout << "2015 - Day 4 - Part 2: The number resulting in a hash starting with 000000 is: " << part2Result << '\n';
}
}
