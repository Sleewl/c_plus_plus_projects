#ifndef SHELLSORT_HPP
#define SHELLSORT_HPP

#include <iterator>

namespace bazhenov {
  template< typename Iterator, typename Compare >
  void shellSort(Iterator first, Iterator last, size_t n, Compare cmp)
  {
    while (n > 0) {
      for (auto it = std::next(first, n); it != last; ++it) {
        auto tmp = it;
        while (static_cast< size_t >(std::distance(first, tmp)) >= n && !cmp(*std::prev(tmp, n), *tmp)) {
          auto prev = std::prev(tmp, n);
          std::swap(*prev, *tmp);
          tmp = prev;
        }
      }
      n /= 2;
    }
  }
}
#endif
