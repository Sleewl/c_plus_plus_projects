#include "splitFunctionsForBidirectional.hpp"

gruzdev::listOfDictionariesPair gruzdev::getDictionaryOfListsFromString(std::string& info)
{
  listOfDictionariesPair dictionaryPair;
  dictionaryPair.first = getPartOfString(info);
  BidirectionalList< int > tmp;
  while (!info.empty()) {
    int val = std::stoi(getPartOfString(info));
    tmp.emplaceBack(val);
  }
  dictionaryPair.second = std::move(tmp);
  return dictionaryPair;
}
