#ifndef STRINGPARSEFUNCTIONS_HPP
#define STRINGPARSEFUNCTIONS_HPP

#include <utility>
#include <dictionary.hpp>
#include <AVLTree.hpp>

namespace bazhenov {
  using dictionaryPair = std::pair< std::string, Dictionary< int, std::string > >;
  using treePair = std::pair< std::string, AVLTree< int, std::string > >;

  std::string getPartOfString(std::string& info);
  template< typename Pair >
  Pair getPairContainerFromString(std::string& info)
  {
    Pair dictionary;
    dictionary.first = getPartOfString(info);
    while (!info.empty()) {
      int key = std::stoi(getPartOfString(info));
      std::string value = getPartOfString(info);
      dictionary.second.insert(std::make_pair(key, value));
    }
    return dictionary;
  }
}
#endif
