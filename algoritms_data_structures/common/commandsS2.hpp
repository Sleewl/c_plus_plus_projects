#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <functional>
#include "stringParseFunctions.hpp"
#include "messages.h"

namespace gruzdev {
  using listOfDictionaries = Dictionary< std::string, Dictionary< int, std::string > >;

  class print_t {
    public:
    print_t() = delete;
    print_t(std::istream& in, std::ostream& out);
    void operator()(listOfDictionaries& dictionaries);
    private:
    std::istream& in_;
    std::ostream& out_;
  };

  class complement_t {
    public:
    complement_t() = delete;
    explicit complement_t(std::istream& in);
    void operator()(listOfDictionaries& dictionaries);
    private:
    std::istream& in_;
  };

  class intersect_t {
    public:
    intersect_t() = delete;
    explicit intersect_t(std::istream& in);
    void operator()(listOfDictionaries& dictionaries);
    private:
    std::istream& in_;
  };

  class unite_t {
    public:
    unite_t() = delete;
    explicit unite_t(std::istream& in);
    void operator()(listOfDictionaries& dictionaries);
    private:
    std::istream& in_;
  };
}
#endif
