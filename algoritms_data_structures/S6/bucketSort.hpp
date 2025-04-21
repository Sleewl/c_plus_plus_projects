#ifndef BUCKETSORT_HPP
#define BUCKETSORT_HPP

#include <utility>
#include <AVLTree.hpp>
#include <bidirectionalList.hpp>
#include "shellSort.hpp"

namespace {

  template< typename Iterator>
  std::pair< Iterator, Iterator > getMinMaxElement(Iterator begin, Iterator end)
  {
    if (begin == end) {
      return std::make_pair(end, end);
    }
    Iterator min = begin;
    Iterator max = begin;
    while (begin != end) {
      if (*begin > *max ) {
        max = begin;
      }
      if (*begin < *min) {
        min = begin;
      }
      ++begin;
    }
    return std::make_pair(min, max);
  }
}

namespace gruzdev {
  template< typename Iterator, typename Compare, typename Strategy >
  void bucketSort(Iterator begin, Iterator end, size_t size, Compare cmp, Strategy strategy)
  {
    using value = typename Iterator::value_type;
    if (size < 2) {
      return;
    }

    auto pair = getMinMaxElement(begin, end);
    value min = *pair.first;
    value max = *pair.second;
    if (min == max) {
      return;
    }

    int number = strategy(size);
    double range = (max - min) * 1.0 / number;
    AVLTree< int, BidirectionalList< value > > buckets;
    for (int i = 0; i < number; ++i) {
      buckets.emplace(i, BidirectionalList< value >());
    }

    for (auto it = begin; it != end; ++it) {
      double bucketIndex = (*it- min) / range;
      double diff = bucketIndex - int(bucketIndex);
      if (diff == 0 && *it != min) {
        buckets.at(bucketIndex - 1).pushFront(*it);
      } else {
        buckets.at(bucketIndex).pushFront(*it);
      }
    }

    auto start = begin;
    auto it = (cmp(min, max)) ? buckets.begin() : buckets.rbegin();
    for (; it != buckets.end(); ++it) {
      auto bucket = it->second;
      shellSort(bucket.begin(), bucket.end(), size, cmp);
      for (auto b = bucket.begin(); b != bucket.end(); ++b) {
        *start = *b;
        ++start;
      }
    }

  }
}
#endif
