#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "dictionary.hpp"
#include "splitFunctionsForBidirectional.hpp"

namespace gruzdev {
  using dictionaryOfLists = gruzdev::Dictionary< std::string, gruzdev::BidirectionalList< int > >;

  class printBidirectional_t {
    public:
    printBidirectional_t() = delete;
    printBidirectional_t(std::istream& in, std::ostream& out);
    void operator()(dictionaryOfLists& dictionaries);
    private:
    std::istream& in_;
    std::ostream& out_;
  };

  class replace_t {
    public:
    replace_t() = delete;
    replace_t(std::istream& in);
    void operator()(dictionaryOfLists& dictionaries);
    private:
    std::istream& in_;
  };

  class remove_t {
    public:
    remove_t() = delete;
    remove_t(std::istream& in);
    void operator()(dictionaryOfLists& dictionaries);
    private:
    std::istream& in_;
  };

  class concat_t {
    public:
    concat_t() = delete;
    concat_t(std::istream& in);
    void operator()(dictionaryOfLists& dictionaries);
    private:
    std::istream& in_;
  };

  class equal_t {
    public:
    equal_t() = delete;
    equal_t(std::istream& in, std::ostream& out);
    void operator()(dictionaryOfLists& dictionaries);
    private:
    std::istream& in_;
    std::ostream& out_;
  };

}
#endif
