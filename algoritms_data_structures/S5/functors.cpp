#include "functors.hpp"
#include <limits>
#include <stdexcept>
#include "operations.h"


void gruzdev::keySum::operator()(const std::pair< const long long int, std::string >& pair)
{
  result_ = summarize(result_, pair.first);
}

void gruzdev::pairSum::operator()(const std::pair< const long long int, std::string >& pair)
{
  key_(pair);
  if (!result_.empty()) {
    result_ += " ";
  }
  result_ += pair.second;
}

std::string gruzdev::pairSum::getResult() const
{
  return std::to_string(key_.result_) + " " + result_;
}
