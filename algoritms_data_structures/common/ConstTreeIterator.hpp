#ifndef CONSTTREEITERATOR_HPP
#define CONSTTREEITERATOR_HPP
#include "TreeIterator.hpp"

namespace gruzdev {
  template< typename T >
  class ConstTreeIterator: public std::iterator< std::bidirectional_iterator_tag, T > {
    public:
    using self = ConstTreeIterator< T >;

    template< typename, typename, typename >
    friend class BinarySearchTree;

    template< typename, typename, typename >
    friend class AVLTree;

    ConstTreeIterator() = default;

    ConstTreeIterator(const TreeIterator< T >& other):
      cur_(other.cur_),
      nil_(other.nil_),
      reverse_(other.reverse_)
    {}

    const T& operator*()
    {
      assert(cur_ && cur_ != nil_);
      return cur_->data_;
    }

    const T* operator->()
    {
      assert(cur_ && cur_ != nil_);
      return std::addressof(cur_->data_);
    }

    self& operator++()
    {
      cur_ = (reverse_) ? detail::getPrev(cur_, nil_) : detail::getNext(cur_, nil_);
      return *this;
    }

    self operator++(int)
    {
      self tmp(*this);
      ++(*this);
      return tmp;
    }

    self& operator--()
    {
      cur_ = (reverse_) ? detail::getNext(cur_, nil_) : detail::getPrev(cur_, nil_);
      return *this;
    }

    self operator--(int)
    {
      self tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const self& other)
    {
      return cur_ == other.cur_ && nil_ == other.nil_;
    }

    bool operator!=(const self& other)
    {
      return !(*this == other);
    }

    void swap(self& other)
    {
      std::swap(cur_, other.cur_);
      std::swap(nil_, other.nil_);
    }

    private:
    detail::TreeNode< T >* cur_;
    const detail::TreeNode< T >* nil_;
    bool reverse_;

    ConstTreeIterator(detail::TreeNode< T >* cur, const detail::TreeNode< T >* nil, bool reverse):
      cur_(cur),
      nil_(nil),
      reverse_(reverse)
    {}
  };
}
#endif
