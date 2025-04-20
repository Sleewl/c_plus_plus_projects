#include "commandsS2.hpp"

namespace {
  using integerKeyDictionary = bazhenov::Dictionary< int, std::string >;

  integerKeyDictionary complement(const integerKeyDictionary& lhs, const integerKeyDictionary& rhs)
  {
    integerKeyDictionary dictionary;
    if (!lhs.isEmpty()) {
      auto it = lhs.cbegin();
      while (it != lhs.cend()) {
        if (rhs.find(it->first) == rhs.cend()) {
          dictionary.insert(*it);
        }
        ++it;
      }
    }
    return dictionary;
  }

  integerKeyDictionary intersect(const integerKeyDictionary& lhs, const integerKeyDictionary& rhs)
  {
    integerKeyDictionary dictionary;
    if (!lhs.isEmpty()) {
      auto it = lhs.cbegin();
      while (it != lhs.cend()) {
        if (rhs.find(it->first) != rhs.cend()) {
          dictionary.insert(*it);
        }
        ++it;
      }
    }
    return dictionary;
  }

  integerKeyDictionary unite(const integerKeyDictionary& lhs, const integerKeyDictionary& rhs)
  {
    integerKeyDictionary dictionary;
    if (!lhs.isEmpty()) {
      dictionary = lhs;
      if (!rhs.isEmpty()) {
        auto it = rhs.cbegin();
        while (it != rhs.cend()) {
          if (lhs.find(it->first) == lhs.cend()) {
            dictionary.insert(*it);
          }
          ++it;
        }
      }
    }
    return dictionary;
  }
}
bazhenov::print_t::print_t(std::istream& in, std::ostream& out):
  in_(in),
  out_(out)
{}

void bazhenov::print_t::operator()(bazhenov::listOfDictionaries& dictionaries)
{
  std::string name;
  in_ >> name;
  auto tmp = dictionaries.find(name);
  if (tmp == dictionaries.end()) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if (!tmp->second.isEmpty()) {
    out_ << tmp->first;
    auto it = tmp->second.begin();
    while (it != tmp->second.end()) {
      out_ << ' ' << it->first << ' ' << it->second;
      ++it;
    }
    out_ << "\n";
  } else {
    bazhenov::printEmpty(out_) << "\n";
  }
}

bazhenov::complement_t::complement_t(std::istream& in):
  in_(in)
{}

void bazhenov::complement_t::operator()(bazhenov::listOfDictionaries& dictionaries)
{
  std::string arguments;
  std::getline(in_, arguments);
  arguments.erase(0, 1);
  std::string name = getPartOfString(arguments);
  std::string left = getPartOfString(arguments);
  std::string right = getPartOfString(arguments);
  integerKeyDictionary keyDictionary = complement(dictionaries.at(left), dictionaries.at(right));
  if (dictionaries.find(name) == dictionaries.end()) {
    dictionaries.insert(std::make_pair(name, keyDictionary));
  } else {
    dictionaries.at(name) = keyDictionary;
  }
}

bazhenov::intersect_t::intersect_t(std::istream& in):
  in_(in)
{}

void bazhenov::intersect_t::operator()(bazhenov::listOfDictionaries& dictionaries)
{
  std::string arguments;
  std::getline(in_, arguments);
  arguments.erase(0, 1);
  std::string name = getPartOfString(arguments);
  std::string left = getPartOfString(arguments);
  std::string right = getPartOfString(arguments);
  integerKeyDictionary keyDictionary = intersect(dictionaries.at(left), dictionaries.at(right));
  if (dictionaries.find(name) == dictionaries.end()) {
    dictionaries.insert(std::make_pair(name, keyDictionary));
  } else {
    dictionaries.at(name) = keyDictionary;
  }
}

bazhenov::unite_t::unite_t(std::istream& in):
  in_(in)
{}

void bazhenov::unite_t::operator()(bazhenov::listOfDictionaries& dictionaries)
{
  std::string arguments;
  std::getline(in_, arguments);
  arguments.erase(0, 1);
  std::string name = getPartOfString(arguments);
  std::string left = getPartOfString(arguments);
  std::string right = getPartOfString(arguments);
  integerKeyDictionary keyDictionary = unite(dictionaries.at(left), dictionaries.at(right));
  if (dictionaries.find(name) == dictionaries.end()) {
    dictionaries.insert(std::make_pair(name, keyDictionary));
  } else {
    dictionaries.at(name) = keyDictionary;
  }
}
