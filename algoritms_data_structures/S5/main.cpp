#include <iostream>
#include <fstream>
#include <functional>
#include <AVLTree.hpp>
#include <dictionary.hpp>
#include "messages.h"
#include "functors.hpp"


int main(int argv, char** argc)
{
  std::ifstream file;
  std::string direction = "";
  if (argv == 3) {
    direction = argc[1];
    file.open(argc[2]);
    if (!file.is_open()) {
      std::cerr << "Error in opening file!\n";
      return 1;
    }
  } else {
    std::cerr << "Invalid amount of arguments!\n";
    return 1;
  }

  gruzdev::AVLTree< long long, std::string > tree;
  long long value = 0;
  std::string str = "";
  while (!file.eof()) {
    file >> value >> str;
    if (!file.fail()) {
      tree.emplace(value, str);
    }
  }

  if (tree.isEmpty()) {
    gruzdev::printEmpty(std::cout) << "\n";
    return 0;
  }

  try {
    using namespace std::placeholders;
    gruzdev::pairSum result{};
    gruzdev::Dictionary< std::string, std::function< gruzdev::pairSum(gruzdev::pairSum) > > dictionary
    {
      {"ascending", std::bind(&gruzdev::AVLTree< long long, std::string >::traverse_lnr< gruzdev::pairSum >, &tree, _1)},
      {"descending", std::bind(&gruzdev::AVLTree< long long, std::string >::traverse_rnl< gruzdev::pairSum >, &tree, _1)},
      {"breadth", std::bind(&gruzdev::AVLTree< long long, std::string >::traverse_breadth< gruzdev::pairSum >, &tree, _1)}
    };
    std::cout << dictionary.at(direction)(result).getResult() << "\n";
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << "\n";
    return 1;
  }

  return 0;
}
