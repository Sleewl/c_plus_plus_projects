#include "messages.h"
#include <iostream>

std::ostream& gruzdev::printInvalidCommand(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}

std::ostream& gruzdev::printEmpty(std::ostream& out)
{
  return out << "<EMPTY>";
}

std::ostream& gruzdev::printTrue(std::ostream& out)
{
  return out << "<TRUE>";
}

std::ostream& gruzdev::printFalse(std::ostream& out)
{
  return out << "<FALSE>";
}
