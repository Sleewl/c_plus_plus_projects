#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include "BinarySearchTree.hpp"

namespace gruzdev {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLTree {
    public:
    using BST = BinarySearchTree< Key, Value, Compare >;
    using pair = typename BST::pair;
    using nptr = typename BST::nptr;
    using iterator = typename BST::iterator;
    using citerator = typename BST::citerator;

    iterator begin()
    {
      return tree_.begin();
    }

    citerator begin() const
    {
      return tree_.begin();
    }

    iterator rbegin()
    {
      return tree_.rbegin();
    }

    citerator rbegin() const
    {
      return tree_.rbegin();
    }

    citerator cbegin() const
    {
      return tree_.cbegin();
    }

    citerator crbegin() const
    {
      return tree_.cbegin();
    }

    iterator end()
    {
      return tree_.end();
    }

    citerator end() const
    {
      return tree_.end();
    }

    iterator rend()
    {
      return tree_.rend();
    }

    citerator rend() const
    {
      return tree_.rend();
    }

    citerator cend() const
    {
      return tree_.crend();
    }

    citerator crend() const
    {
      return tree_.crend();
    }

    AVLTree(const Compare& cmp = Compare()):
      tree_(cmp)
    {}

    AVLTree(std::initializer_list< pair > il, const Compare& cmp = Compare()):
      tree_(il, cmp)
    {}

    AVLTree(const AVLTree& other) = default;

    AVLTree(AVLTree&& other) = default;


    ~AVLTree() = default;

    AVLTree& operator=(const AVLTree& other) = default;

    AVLTree& operator=(AVLTree&& other) = default;


    bool isEmpty() const
    {
      return tree_.isEmpty();
    }

    size_t getSize() const
    {
      return tree_.getSize();
    }

    void swap(AVLTree& other)
    {
      tree_.swap(other.tree_);
    }

    template< typename... Args >
    iterator emplace(Args&& ... args)
    {
      auto it = tree_.emplace(std::forward< Args >(args)...);
      doBalance(it);
      return it;
    }

    iterator insert(const pair& val)
    {
      return emplace(val);
    }

    iterator insert(pair&& val)
    {
      return emplace(std::move(val));
    }

    template< typename Pointer >
    iterator insert(Pointer first, Pointer last)
    {
      auto tmp = first;
      auto iter = iterator();
      while (tmp != last) {
        iter = emplace(*tmp);
        ++tmp;
      }
      return iter;
    }

    iterator erase(citerator position)
    {
      if (position.cur_ == position.nil_) {
        return end();
      }
      nptr balance = position.cur_;
      if (tree_.getAmountOfChildren(balance) == 0) {
        balance = balance->parent_;
      } else if (tree_.getAmountOfChildren(balance) == 1) {
        balance = (balance->right_ == position.nil_) ? balance->left_ : balance->right_;
      } else {
        auto ret = tree_.erase(position);
        doBalance(ret);
        return ret;
      }
      auto ret = tree_.erase(position);
      auto iter = iterator(balance, position.nil_, false);
      doBalance(iter);
      return ret;
    }

    iterator erase(const Key& key)
    {
      return erase(find(key));
    }

    iterator erase(citerator first, citerator last)
    {
      auto iter = first;
      while (iter != last) {
        iter = erase(iter);
      }
      return iterator(iter.cur_, iter.nil_, iter.reverse_);
    }

    iterator find(const Key& key)
    {
      return tree_.find(key);
    }

    citerator find(const Key& key) const
    {
      return tree_.find(key);
    }

    iterator getLowerBound(const Key& key)
    {
      return find(key);
    }

    citerator getLowerBound(const Key& key) const
    {
      return find(key);
    }

    iterator getUpperBound(const Key& key)
    {
      return ++find(key);
    }

    citerator getUpperBound(const Key& key) const
    {
      return ++find(key);
    }

    const Value& at(const Key& key) const
    {
      return tree_.at(key);
    }

    Value& at(const Key& key)
    {
      return const_cast< Value& >(static_cast< const AVLTree& >(*this).at(key));
    }

    template< typename F >
    F traverse_lnr(F f) const
    {
      return tree_.traverse_lnr(f);
    }

    template< typename F >
    F traverse_rnl(F f) const
    {
      return tree_.traverse_rnl(f);
    }

    template< typename F >
    F traverse_breadth(F f) const
    {
      return tree_.traverse_breadth(f);
    }

    private:
    BST tree_;

    void fixHeightOfAllTree(iterator node)
    {
      detail::fixHeight(node.cur_);
      if (node.cur_->parent_ != node.nil_) {
        fixHeightOfAllTree(iterator(node.cur_->parent_, node.nil_, false));
      }
    }

    void doBalance(iterator node)
    {
      if (node == end()) {
        return;
      }
      int factor = detail::getChildHeightDifference(node.cur_);
      if (factor < -1) {
        if (detail::getChildHeightDifference(node.cur_->right_) > 0) {
          tree_.rotateRight(node.cur_->right_);
          tree_.rotateLeft(node.cur_);
        } else {
          tree_.rotateLeft(node.cur_);
        }
      } else if (factor > 1) {
        if (detail::getChildHeightDifference(node.cur_->left_) < 0) {
          tree_.rotateLeft(node.cur_->left_);
          tree_.rotateRight(node.cur_);
        } else {
          tree_.rotateRight(node.cur_);
        }
      }
      doBalance(iterator(node.cur_->parent_, node.nil_, false));
    }
  };
}
#endif
