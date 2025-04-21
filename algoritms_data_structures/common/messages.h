#ifndef MESSAGES_H
#define MESSAGES_H

#include <iosfwd>

namespace gruzdev {
  std::ostream& printInvalidCommand(std::ostream& out);
  std::ostream& printEmpty(std::ostream& out);
  std::ostream& printTrue(std::ostream& out);
  std::ostream& printFalse(std::ostream& out);
}
#endif
