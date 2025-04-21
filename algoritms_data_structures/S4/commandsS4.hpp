#ifndef COMMANDSS4_hpp
#define COMMANDS4_HPP

#include <iostream>
#include <string>
#include <functional>
#include "stringParseFunctions.hpp"
#include "messages.h"

namespace gruzdev {
  using listOfTrees = AVLTree< std::string, AVLTree< int, std::string > >;

  class AVLPrint {
    public:
    AVLPrint() = delete;
    AVLPrint(std::istream& in, std::ostream& out);
    void operator()(listOfTrees& trees);
    private:
    std::istream& in_;
    std::ostream& out_;
  };

  class AVLComplement {
    public:
    AVLComplement() = delete;
    explicit AVLComplement(std::istream& in);
    void operator()(listOfTrees& trees);
    private:
    std::istream& in_;
  };

  class AVLIntersect {
    public:
    AVLIntersect() = delete;
    explicit AVLIntersect(std::istream& in);
    void operator()(listOfTrees& trees);
    private:
    std::istream& in_;
  };

  class AVLUnite {
    public:
    AVLUnite() = delete;
    explicit AVLUnite(std::istream& in);
    void operator()(listOfTrees& trees);
    private:
    std::istream& in_;
  };
}

#endif
