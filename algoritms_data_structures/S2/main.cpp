#include <fstream>
#include <limits>
#include <vector>
#include <iostream>
#include "commandsS2.hpp"

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

  gruzdev::Dictionary< std::string, gruzdev::Dictionary< int, std::string > > listOfDictionaries;
  std::string info;
  while (std::getline(file, info)) {
    if (!info.empty()) {
      try {
        gruzdev::dictionaryPair keyDictionary = gruzdev::getPairContainerFromString< gruzdev::dictionaryPair >(info);
        listOfDictionaries.insert(keyDictionary);
      } catch (const std::exception& ex) {
        std::cerr << ex.what();
        return 1;
      }
    }
  }

  gruzdev::Dictionary< std::string, std::function< void(gruzdev::listOfDictionaries&) > > commands
  {
    {"print", gruzdev::print_t(std::cin, std::cout)},
    {"complement", gruzdev::complement_t(std::cin)},
    {"intersect", gruzdev::intersect_t(std::cin)},
    {"union", gruzdev::unite_t(std::cin)}
  };

  std::string command;
  while (std::cin >> command) {
    try {
      commands.at(command)(listOfDictionaries);
    } catch (const std::exception& ex) {
      gruzdev::printInvalidCommand(std::cout) << "\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;

}
