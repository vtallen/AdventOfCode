#include <cstdint>
#include <iostream>
#include <fstream>
#include <string_view>
#include <string>
#include <regex>
#include <sstream>
#include <stdint.h>

#include "../AOCHelpers/AOCHelpers.h"

namespace AOC2015 {

struct Wire {
  std::string id;
  uint16_t signal;
};

std::vector<Wire> wires{};

// Function to so I dont have to type std::find a bunch of times
bool wireExists(const std::string &wireId) {
  auto exists {std::find_if(wires.begin(), wires.end(), [&wireId](const Wire &x) {
    return wireId == x.id; 
  })};

  return exists != wires.end();
}

void addWireIfNotExists(const std::string &wireId) {
  // Here we are checking if the passed in ID could be an int as AND OR gates have the possibility of having an int as the first argument
  if (!AOCHelpers::isConvertableToNum<uint16_t>(wireId)) {
    if (!wireExists(wireId)) wires.push_back(Wire{wireId, 0});
  }
}

auto getWire(const std::string &wireId) {
  return std::find_if(wires.begin(), wires.end(), [wireId](Wire &wire){
    return wireId == wire.id;
  });
}

std::ostream &operator<<(std::ostream &out, std::vector<Wire> &vec) {
  for (auto item : vec) {
    out << item.id << ": " << item.signal << '\n';
  } 
  return out;
}

void day7(std::string_view inputFile) {
  // Regex patterns for matching each possible input line
  
  // Checks if the line is an AND or an OR gate. ex. x AND y -> z or 1 OR y -> z
  const std::regex AND_OR_GATE{R"((\w+|\d+)\s(OR|AND)\s(\w+|\d+)\s->\s(\w+))"};

  // Checks if the line is sending a signal to a wire ex. 1000 -> x
  const std::regex SEND_SIGNAL{R"((\d+)\s->\s(\w+))"};
  
  // Checks if a bit shifted signal needs to be sent to a wire ex. x RSHIFT 3 -> y
  const std::regex BIT_SHIFT{R"((\w+)\s(RSHIFT|LSHIFT)\s(\d+)\s->\s(\w+))"};
  
  // Checks if there is a NOT gate ex. x NOT -> y
  const std::regex NOT{R"(NOT\s(\w+)\s->\s(\w+))"};  

  // Checks if a wire needs connected to another wire
  const std::regex WIRE_TO_WIRE{R"((\w+)\s->\s(\w+))"};

  std::ifstream inputStream{inputFile.data()};

  if (!inputStream) {
    std::cout << "Unable to open file: " << inputFile << '\n';
  }
  
    while (inputStream) {
    std::string line;
    std::getline(inputStream, line);
    if (line == "") continue;

    if (std::regex_match(line, AND_OR_GATE)) {
      std::smatch match;
      std::regex_search(line, match, AND_OR_GATE);
      
      std::string opr1{match[1]};
      std::string op{match[2]};
      std::string opr2{match[3]};
      std::string dest{match[4]};
      
      addWireIfNotExists(opr1);
      addWireIfNotExists(opr2);
      addWireIfNotExists(dest);

      auto wire1{getWire(opr1)};
      auto wire2{getWire(opr2)};
      auto destWire{getWire(dest)};

    } else if (std::regex_match(line, SEND_SIGNAL)) {
      std::smatch match;
      std::regex_search(line, match, SEND_SIGNAL);
      
      std::string value{match[1]};
      std::string dest{match[2]};

    } else if (std::regex_match(line, BIT_SHIFT)) {
      std::smatch match;
      std::regex_search(line, match, BIT_SHIFT);

      std::string source{match[1]};
      std::string op{match[2]};
      std::string shiftAmt{match[3]};
      std::string dest{match[4]};
      
      addWireIfNotExists(source);
      addWireIfNotExists(dest);
      
      auto sourceWire{getWire(source)};
      auto destWire{getWire(dest)};

    } else if (std::regex_match(line, NOT)){
      std::smatch match;
      std::regex_search(line, match, NOT);

      std::string source{match[1]};
      std::string dest{match[2]};

      addWireIfNotExists(source);
      addWireIfNotExists(dest);

    } else if (std::regex_match(line, WIRE_TO_WIRE)){
      std::smatch match;
      std::regex_search(line, match, WIRE_TO_WIRE);


    }
  }

  // std::cout << wires;
  //
  //
  auto wireA{getWire("lx")};
  std::cout << "The value on wire a is " << wireA->signal;

  inputStream.close();
}
}
