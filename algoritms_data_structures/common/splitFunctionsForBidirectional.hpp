#ifndef SPLITFUNCTIONSFOFBIDIRECTIONAL_HPP
#define SPLITFUNCTIONSFOFBIDIRECTIONAL_HPP

#include "bidirectionalList.hpp"
#include "stringParseFunctions.hpp"

namespace gruzdev {
  using listOfDictionariesPair = std::pair< std::string, BidirectionalList< int > >;
  listOfDictionariesPair getDictionaryOfListsFromString(std::string& info);
}
#endif
