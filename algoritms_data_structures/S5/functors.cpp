#include "functors.hpp"
#include <limits>
#include <stdexcept>
#include "operations.h"


void bazhenov::keySum::operator()(const std::pair< const long long int, std::string >& pair)
{
  result_ = summarize(result_, pair.first);
}

void bazhenov::pairSum::operator()(const std::pair< const long long int, std::string >& pair)
{
  key_(pair);
  if (!result_.empty()) {
    result_ += " ";
  }
  result_ += pair.second;
}

std::string bazhenov::pairSum::getResult() const
{
  return std::to_string(key_.result_) + " " + result_;
}
