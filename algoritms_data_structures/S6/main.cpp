#include <iostream>
#include <messages.h>
#include <streamGuard.hpp>
#include "storage.hpp"

int main(int argv, char** argc)
{
  std::srand(std::time(nullptr));

  if (argv != 4) {
    std::cerr << "Invalid amount of arguments arguments!\n";
    return 1;
  }

  try {
    size_t size = std::stoull(argc[3]);
    std::string direction = argc[1];
    std::string type = argc[2];
    if (type == "ints") {
      gruzdev::Storage< int > storage(size);
      storage.printCollections(std::cout, direction) << "\n";
    } else if (type == "floats") {
      gruzdev::Storage< float > storage(size);
      gruzdev::StreamGuard guard(std::cout);
      std::cout << std::fixed << std::setprecision(1);
      storage.printCollections(std::cout, direction) << "\n";
    } else {
      throw std::logic_error("Invalid type!");
    }
  } catch (...) {
    gruzdev::printInvalidCommand(std::cerr) << "\n";
    return 1;
  }

}
