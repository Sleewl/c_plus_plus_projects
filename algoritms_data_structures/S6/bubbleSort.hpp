#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

#include <iterator>

namespace gruzdev {
  template< typename Iterator, typename Compare >
  void bubbleSort(Iterator first, Iterator last, Compare cmp)
  {
    bool isSorted = false;
    while (!isSorted) {
      isSorted = true;
      for (auto it = first; it != last; ++it) {
        auto next = std::next(it);
        if (next != last && !cmp(*it, *next)) {
          if (*next != *it) {
            std::swap(*it, *std::next(it));
            isSorted = false;
          }
        }
      }
    }
  }

}
#endif
