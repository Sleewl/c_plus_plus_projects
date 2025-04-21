#ifndef BIDIRECTIONALNODE_HPP
#define BIDIRECTIONALNODE_HPP

namespace gruzdev {
  namespace detail {
    template< typename T >
    struct BidirectionalNode {
      T data_;
      BidirectionalNode< T >* next_;
      BidirectionalNode< T >* prev_;
    };
  }
}
#endif
