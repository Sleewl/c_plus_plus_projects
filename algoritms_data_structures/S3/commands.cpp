#include "commands.hpp"
#include <iostream>
#include "messages.h"

namespace {
  using blist = gruzdev::BidirectionalList< int >;
  bool equalBidirectionalLists(const blist& first, const blist& second)
  {
    if (first.getSize() == second.getSize()) {
      auto it1 = first.cbegin();
      auto it2 = second.cbegin();
      while (it1 != first.cend()) {
        if (*it1 != *it2) {
          return false;
        }
        ++it1;
        ++it2;
      }
      return true;
    }
    return false;
  }

  bool findElementInBidirectionalList(const int& value, const blist& list)
  {
    auto tmp = list.cbegin();
    while (tmp != list.cend()) {
      if (*tmp == value) {
        return true;
      }
      ++tmp;
    }
    return false;
  }
}

gruzdev::printBidirectional_t::printBidirectional_t(std::istream& in, std::ostream& out):
  in_(in),
  out_(out)
{}

void gruzdev::printBidirectional_t::operator()(gruzdev::dictionaryOfLists& dictionaries)
{
  std::string name = "";
  in_ >> name;
  auto tmp = dictionaries.find(name);
  if (tmp == dictionaries.end()) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if (!tmp->second.isEmpty()) {
    out_ << tmp->first;
    auto it = tmp->second.begin();
    while (it != tmp->second.end()) {
      out_ << " " << *it;
      ++it;
    }
    out_ << "\n";
  } else {
    printEmpty(out_) << "\n";
  }
}

gruzdev::replace_t::replace_t(std::istream& in):
  in_(in)
{}

void gruzdev::replace_t::operator()(gruzdev::dictionaryOfLists& dictionaries)
{
  std::string arguments;
  std::getline(in_, arguments);
  arguments.erase(0, 1);
  std::string name = gruzdev::getPartOfString(arguments);
  int value1 = std::stoi(gruzdev::getPartOfString(arguments));
  std::string source = gruzdev::getPartOfString(arguments);

  auto tmp = dictionaries.find(name);
  if (tmp == dictionaries.end()) {
    throw std::logic_error("<INVALID COMMAND>");
  }

  auto it = dictionaries.find(source);
  auto step = tmp->second.begin();
  if (it == dictionaries.end()) {
    int value2 = std::stoi(source);
    while (step != tmp->second.end()) {
      *step = (*step == value1) ? value2 : *step;
      ++step;
    }
  } else {
    while (step != tmp->second.end()) {
      if (*step == value1) {
        step = tmp->second.erase(step);
        tmp->second.insert(step, it->second.begin(), it->second.end());
      } else {
        ++step;
      }
    }
  }
}

gruzdev::remove_t::remove_t(std::istream& in):
  in_(in)
{}

void gruzdev::remove_t::operator()(gruzdev::dictionaryOfLists& dictionaries)
{
  std::string arguments;
  std::getline(in_, arguments);
  arguments.erase(0, 1);
  std::string name = gruzdev::getPartOfString(arguments);
  std::string source = gruzdev::getPartOfString(arguments);

  auto tmp = dictionaries.find(name);
  if (tmp == dictionaries.end()) {
    throw std::logic_error("<INVALID COMMAND>");
  }

  auto it = dictionaries.find(source);
  auto step = tmp->second.begin();
  while (step != tmp->second.end()) {
    bool condition = (it == dictionaries.end()) ? *step == std::stoi(source) : findElementInBidirectionalList(*step, it->second);
    if (condition) {
      step = tmp->second.erase(step);
    } else {
      ++step;
    }
  }
}

gruzdev::equal_t::equal_t(std::istream& in, std::ostream& out):
  in_(in),
  out_(out)
{}

void gruzdev::equal_t::operator()(gruzdev::dictionaryOfLists& dictionaries)
{
  gruzdev::BidirectionalList< std::string > list;
  std::string names = "";
  std::getline(in_, names);
  names.erase(0, 1);
  while (!names.empty()) {
    list.emplaceBack(gruzdev::getPartOfString(names));
  }
  if (list.getSize() < 2) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto it1 = list.begin();
  auto it2 = ++list.begin();
  for (; it2 != list.end(); ++it1, ++it2) {
    if (!equalBidirectionalLists(dictionaries.at(*(it1)), dictionaries.at(*(it2)))) {
      gruzdev::printFalse(out_) << "\n";
      return;
    }
  }
  gruzdev::printTrue(out_) << "\n";
}

gruzdev::concat_t::concat_t(std::istream& in):
  in_(in)
{}

void gruzdev::concat_t::operator()(gruzdev::dictionaryOfLists& dictionaries)
{
  gruzdev::BidirectionalList< std::string > list;
  std::string names = "";
  std::getline(in_, names);
  names.erase(0, 1);
  std::string newList = gruzdev::getPartOfString(names);
  if (newList.empty()) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  while (!names.empty()) {
    list.emplaceBack(gruzdev::getPartOfString(names));
  }

  if (list.getSize() < 2) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  blist tmp;
  auto iter = list.begin();
  auto it = tmp.begin();
  while (iter != list.end()) {
    tmp.insert(it, dictionaries.at(*iter).begin(), dictionaries.at(*iter).end());
    ++iter;
  }
  dictionaries.insert(std::make_pair(newList, std::move(tmp)));
}
