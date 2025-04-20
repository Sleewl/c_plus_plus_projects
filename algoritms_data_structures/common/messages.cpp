#include "messages.h"
#include <iostream>

std::ostream& bazhenov::printInvalidCommand(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}

std::ostream& bazhenov::printEmpty(std::ostream& out)
{
  return out << "<EMPTY>";
}

std::ostream& bazhenov::printTrue(std::ostream& out)
{
  return out << "<TRUE>";
}

std::ostream& bazhenov::printFalse(std::ostream& out)
{
  return out << "<FALSE>";
}
