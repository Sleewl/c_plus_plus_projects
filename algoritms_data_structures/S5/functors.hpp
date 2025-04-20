#ifndef FUNCTORS_HPP
#define FUNCTORS_HPP
#include <string>

namespace bazhenov {
  struct keySum {
    void operator()(const std::pair< const long long, std::string >& pair);
    long long result_ = 0;
  };

  struct pairSum {
    void operator()(const std::pair< const long long, std::string >& pair);
    std::string getResult() const;
    std::string result_ = "";
    keySum key_;
  };
}
#endif
