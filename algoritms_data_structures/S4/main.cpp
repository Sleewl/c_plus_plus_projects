#include <fstream>
#include <limits>
#include <iostream>
#include "commandsS4.hpp"

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

  gruzdev::listOfTrees dictionaryTree;
  std::string info;
  while (std::getline(file, info)) {
    if (!info.empty()) {
      try {
        gruzdev::treePair keyDictionary = gruzdev::getPairContainerFromString< gruzdev::treePair >(info);
        dictionaryTree.insert(keyDictionary);
      } catch (const std::exception& ex) {
        std::cerr << ex.what();
        return 1;
      }
    }
  }

  gruzdev::AVLTree< std::string, std::function< void(gruzdev::listOfTrees&) > > commands
  {
    {"print", gruzdev::AVLPrint(std::cin, std::cout)},
    {"complement", gruzdev::AVLComplement(std::cin)},
    {"intersect", gruzdev::AVLIntersect(std::cin)},
    {"union", gruzdev::AVLUnite(std::cin)}
  };

  std::string command;
  while (std::cin >> command) {
    try {
      commands.at(command)(dictionaryTree);
    } catch (const std::exception& ex) {
      gruzdev::printInvalidCommand(std::cout) << "\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
