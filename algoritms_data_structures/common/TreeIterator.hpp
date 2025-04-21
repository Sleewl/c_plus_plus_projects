#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP
#include <iterator>
#include "TreeNode.hpp"

namespace gruzdev {
  namespace detail {
    template< typename T >
    TreeNode< T >* getNext(TreeNode< T >* cur, const TreeNode< T >* nil)
    {
      if (cur == nil) {
        return cur;
      }
      if (cur->right_ != nil) {
        cur = cur->right_;
        while (cur->left_ != nil) {
          cur = cur->left_;
        }
      } else {
        auto p = cur->parent_;
        while (p != nil && cur == p->right_) {
          cur = p;
          p = p->parent_;
        }
        cur = p;
      }
      return cur;
    }

    template< typename T >
    TreeNode< T >* getPrev(TreeNode< T >* cur, const TreeNode< T >* nil)
    {
      if (cur == nil) {
        return cur;
      }
      if (cur->left_ != nil) {
        cur = cur->left_;
        while (cur->right_ != nil) {
          cur = cur->right_;
        }
      } else {
        auto p = cur->parent_;
        while (p != nil && cur == p->left_) {
          cur = p;
          p = p->parent_;
        }
        cur = p;
      }
      return cur;
    }
  }

  template< typename T >
  class ConstTreeIterator;

  template< typename T >
  class TreeIterator: public std::iterator< std::bidirectional_iterator_tag, T > {
    public:
    using self = TreeIterator< T >;

    template< typename >
    friend class ConstTreeIterator;

    template< typename, typename, typename >
    friend class BinarySearchTree;

    template< typename, typename, typename >
    friend class AVLTree;

    TreeIterator() = default;

    T& operator*()
    {
      assert(cur_ && cur_ != nil_);
      return cur_->data_;
    }

    T* operator->()
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

    TreeIterator(detail::TreeNode< T >* cur, const detail::TreeNode< T >* nil, bool reverse):
      cur_(cur),
      nil_(nil),
      reverse_(reverse)
    {}
  };
}
#endif
