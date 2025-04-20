#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <cstdlib>
#include <iostream>
#include <functional>
#include <deque>
#include <bidirectionalList.hpp>
#include <forwardList.hpp>
#include <dictionary.hpp>
#include "bubbleSort.hpp"
#include "shellSort.hpp"
#include "bucketSort.hpp"

namespace {
  template< typename T >
  T getRandom()
  {
    return static_cast< T >((std::rand()  * 100.0 / RAND_MAX)) ;
  }

  template< typename T >
  void fillDeque(std::deque< T >& deque, size_t size)
  {
    for (size_t i = 0; i < size; ++i) {
      deque.push_back(getRandom< T >());
    }
  }

  size_t createNumberOfBuckets(size_t size)
  {
    return size > 3 ? size / 2 : 2;
  }

  template< typename Iterator >
  std::ostream& printCollection(std::ostream& out, Iterator begin, Iterator end)
  {
    for (auto it = begin; it != end;) {
      out << *it;
      if (++it != end) {
        out << ' ';
      }
    }
    return out;
  }
}

namespace bazhenov {
  template< typename T >
  class Storage {
    public:
    Storage() = delete;

    explicit Storage(size_t size)
    {
      fillDeque(bubble1_, size);
      shell1_.insert(shell1_.begin(), bubble1_.begin(), bubble1_.end());
      bucket1_.insert(bucket1_.begin(), bubble1_.begin(), bubble1_.end());
      bubble2_.insert(bubble2_.begin(), bubble1_.begin(), bubble1_.end());
      shell2_.insert(shell2_.begin(), bubble1_.begin(), bubble1_.end());
      ForwardList< T > tmp(bubble1_.begin(), bubble1_.end());
      bubble3_ = std::move(tmp);
    }

    void sortStorage(const std::string& str)
    {
      bubbleSort(bubble1_.begin(), bubble1_.end(), cmp_.at(str));
      bubbleSort(bubble2_.begin(), bubble2_.end(), cmp_.at(str));
      bubbleSort(bubble3_.begin(), bubble3_.end(), cmp_.at(str));
      shellSort(shell1_.begin(), shell1_.end(), shell1_.size(), cmp_.at(str));
      shellSort(shell2_.begin(), shell2_.end(), shell2_.getSize(), cmp_.at(str));
      bucketSort(bucket1_.begin(), bucket1_.end(), bucket1_.size(), cmp_.at(str), createNumberOfBuckets);
    }

    std::ostream& printCollections(std::ostream& out, const std::string& str)
    {
      printCollection(out, bubble1_.begin(), bubble1_.end()) << "\n";
      sortStorage(str);
      printCollection(out, bubble1_.begin(), bubble1_.end()) << "\n";
      printCollection(out, bubble2_.begin(), bubble2_.end()) << "\n";
      printCollection(out, bubble3_.begin(), bubble3_.end()) << "\n";
      printCollection(out, shell1_.begin(), shell1_.end()) << "\n";
      printCollection(out, shell2_.begin(), shell2_.end()) << "\n";
      return printCollection(out, bucket1_.begin(), bucket1_.end());
    }

    private:
    std::deque< T > bubble1_;
    std::deque< T > shell1_;
    std::deque< T > bucket1_;
    BidirectionalList< T > bubble2_;
    BidirectionalList< T > shell2_;
    ForwardList< T > bubble3_;
    bazhenov::Dictionary< std::string, std::function< bool(T, T) > > cmp_{
      {"ascending",  std::less<>()},
      {"descending", std::greater<>()}
    };
  };
}

#endif
