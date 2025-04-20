#include "stringParseFunctions.hpp"

std::string bazhenov::getPartOfString(std::string& info)
{
  size_t pos = info.find(' ');
  std::string part = info.substr(0, pos);
  pos == std::string::npos ? pos : ++pos;
  info.erase(0, pos);
  return part;
}


