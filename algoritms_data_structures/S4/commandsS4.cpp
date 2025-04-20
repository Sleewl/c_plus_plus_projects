#include "commandsS4.hpp"

namespace {
  using integerKeyAVLTree = bazhenov::AVLTree< int, std::string >;

  integerKeyAVLTree complement(const integerKeyAVLTree& lhs, const integerKeyAVLTree& rhs)
  {
    integerKeyAVLTree dictionary;
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

  integerKeyAVLTree intersect(const integerKeyAVLTree& lhs, const integerKeyAVLTree& rhs)
  {
    integerKeyAVLTree dictionary;
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

  integerKeyAVLTree unite(const integerKeyAVLTree& lhs, const integerKeyAVLTree& rhs)
  {
    integerKeyAVLTree dictionary;
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
bazhenov::AVLPrint::AVLPrint(std::istream& in, std::ostream& out):
  in_(in),
  out_(out)
{}

void bazhenov::AVLPrint::operator()(bazhenov::listOfTrees& trees)
{
  std::string name;
  in_ >> name;
  auto tmp = trees.find(name);
  if (tmp == trees.end()) {
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

bazhenov::AVLComplement::AVLComplement(std::istream& in):
  in_(in)
{}

void bazhenov::AVLComplement::operator()(bazhenov::listOfTrees& trees)
{
  std::string arguments;
  std::getline(in_, arguments);
  arguments.erase(0, 1);
  std::string name = getPartOfString(arguments);
  std::string left = getPartOfString(arguments);
  std::string right = getPartOfString(arguments);
  integerKeyAVLTree keyDictionary = complement(trees.at(left), trees.at(right));
  if (trees.find(name) == trees.end()) {
    trees.insert(std::make_pair(name, keyDictionary));
  } else {
    trees.at(name) = keyDictionary;
  }
}

bazhenov::AVLIntersect::AVLIntersect(std::istream& in):
  in_(in)
{}

void bazhenov::AVLIntersect::operator()(bazhenov::listOfTrees& trees)
{
  std::string arguments;
  std::getline(in_, arguments);
  arguments.erase(0, 1);
  std::string name = getPartOfString(arguments);
  std::string left = getPartOfString(arguments);
  std::string right = getPartOfString(arguments);
  integerKeyAVLTree keyDictionary = intersect(trees.at(left), trees.at(right));
  if (trees.find(name) == trees.end()) {
    trees.insert(std::make_pair(name, keyDictionary));
  } else {
    trees.at(name) = keyDictionary;
  }
}

bazhenov::AVLUnite::AVLUnite(std::istream& in):
  in_(in)
{}

void bazhenov::AVLUnite::operator()(bazhenov::listOfTrees& trees)
{
  std::string arguments;
  std::getline(in_, arguments);
  arguments.erase(0, 1);
  std::string name = getPartOfString(arguments);
  std::string left = getPartOfString(arguments);
  std::string right = getPartOfString(arguments);
  integerKeyAVLTree keyDictionary = unite(trees.at(left), trees.at(right));
  if (trees.find(name) == trees.end()) {
    trees.insert(std::make_pair(name, keyDictionary));
  } else {
    trees.at(name) = keyDictionary;
  }
}
