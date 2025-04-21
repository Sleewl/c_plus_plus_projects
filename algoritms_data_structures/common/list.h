#ifndef LIST_H
#define LIST_H

namespace gruzdev {
  namespace detail {
    template< typename T >
    struct List {
      T data_;
      List< T >* next_;
    };
  }
}
#endif
