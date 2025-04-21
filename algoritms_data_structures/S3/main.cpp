#include <iostream>
#include <fstream>
#include <limits>
#include <functional>
#include "commands.hpp"
#include "splitFunctionsForBidirectional.hpp"
#include "messages.h"

int main(int argv, char** argc)
{
  std::ifstream file;
  if (argv == 2) {
    file.open(argc[1]);
    if (!file.is_open()) {
      std::cerr << "Error in opening file!\n";
      return 1;
    }
  } else {
    std::cerr << "Invalid amount of arguments!\n";
    return 1;
  }

  gruzdev::dictionaryOfLists dictionary;
  std::string info;
  while (std::getline(file, info)) {
    if (!info.empty()) {
      try {
        dictionary.insert(gruzdev::getDictionaryOfListsFromString(info));
      } catch (const std::exception& ex) {
        std::cerr << ex.what();
        return 1;
      }
    }
  }
  gruzdev::Dictionary< std::string, std::function< void(gruzdev::dictionaryOfLists&) > > commands
  {
    {"print", gruzdev::printBidirectional_t(std::cin, std::cout)},
    {"replace", gruzdev::replace_t(std::cin)},
    {"equal", gruzdev::equal_t(std::cin, std::cout)},
    {"remove", gruzdev::remove_t(std::cin)},
    {"concat", gruzdev::concat_t(std::cin)}
  };

  std::string command;
  while (std::cin >> command) {
    try {
      if (commands.find(command) != commands.end()) {
        commands.at(command)(dictionary);
      } else {
        gruzdev::printInvalidCommand(std::cout) << "\n";
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    } catch (const std::exception& ex) {
      gruzdev::printInvalidCommand(std::cout) << "\n";
    }
  }
  return 0;
}
