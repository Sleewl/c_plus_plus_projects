#ifndef SPLITFUNCTIONSFOFBIDIRECTIONAL_HPP
#define SPLITFUNCTIONSFOFBIDIRECTIONAL_HPP

#include "bidirectionalList.hpp"
#include "stringParseFunctions.hpp"

namespace bazhenov {
  using listOfDictionariesPair = std::pair< std::string, BidirectionalList< int > >;
  listOfDictionariesPair getDictionaryOfListsFromString(std::string& info);
}
#endif
