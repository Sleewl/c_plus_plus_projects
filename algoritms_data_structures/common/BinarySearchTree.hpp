#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <queue.h>
#include <stack.h>
#include "ConstTreeIterator.hpp"
#include "memoryAllocation.hpp"


namespace bazhenov {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BinarySearchTree {
    public:
    using pair = std::pair< const Key, Value >;
    using node = detail::TreeNode< pair >;
    using nptr = detail::TreeNode< pair >*;
    using iterator = TreeIterator< pair >;
    using citerator = ConstTreeIterator< pair >;

    iterator begin()
    {
      return iterator(getMostLeftNode(), nil_, false);
    }

    citerator begin() const
    {
      return citerator(getMostLeftNode(), nil_, false);
    }

    iterator rbegin()
    {
      return iterator(getMostRightNode(), nil_, true);
    }

    citerator rbegin() const
    {
      return citerator(getMostRightNode(), nil_, true);
    }

    citerator cbegin() const
    {
      return citerator(getMostLeftNode(), nil_, false);
    }

    citerator crbegin() const
    {
      return citerator(getMostRightNode(), nil_, true);
    }

    iterator end()
    {
      return iterator(nil_, nil_, false);
    }

    citerator end() const
    {
      return citerator(nil_, nil_, false);
    }

    iterator rend()
    {
      return iterator(nil_, nil_, true);
    }

    citerator rend() const
    {
      return citerator(nil_, nil_, true);
    }

    citerator cend() const
    {
      return citerator(nil_, nil_, false);
    }

    citerator crend() const
    {
      return citerator(nil_, nil_, true);
    }

    BinarySearchTree(const Compare& cmp = Compare()):
      nil_(makeEmptyNode()),
      root_(nil_),
      cmp_(cmp),
      size_(0)
    {}

    BinarySearchTree(std::initializer_list< pair > il, const Compare& cmp = Compare()):
      nil_(makeEmptyNode()),
      root_(nil_),
      cmp_(cmp),
      size_(0)
    {
      insert(il.begin(), il.end());
    }

    BinarySearchTree(const BinarySearchTree& other):
      nil_(makeEmptyNode()),
      root_(nil_),
      cmp_(other.cmp_),
      size_(0)
    {
      auto it = other.cbegin();
      while (it != other.cend()) {
        emplace(*(it++));
      }
    }

    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
      BinarySearchTree tmp(other);
      swap(tmp);
      return *this;
    }

    BinarySearchTree(BinarySearchTree&& other):
      nil_(other.nil_),
      root_(other.root_),
      cmp_(std::move(other.cmp_)),
      size_(other.size_)
    {
      other.nil_ = nullptr;
      other.root_ = nullptr;
      other.size_ = 0;
    }

    BinarySearchTree& operator=(BinarySearchTree&& other)
    {
      BinarySearchTree tmp(std::move(other));
      swap(tmp);
      return *this;
    }

    ~BinarySearchTree()
    {
      destroyTree(root_);
      detail::destroy(std::addressof(nil_->height_));
      detail::deallocate(nil_);
    }

    bool isEmpty() const
    {
      return size_ == 0;
    }

    size_t getSize() const
    {
      return size_;
    }

    void swap(BinarySearchTree& other)
    {
      std::swap(size_, other.size_);
      std::swap(nil_, other.nil_);
      std::swap(root_, other.root_);
      std::swap(cmp_, other.cmp_);
    }

    template< typename... Args >
    iterator emplace(Args&& ... args)
    {
      nptr node = createNodeWithData(std::forward< Args >(args)...);
      if (size_ == 0) {
        root_ = node;
        nil_->right_ = root_;
        nil_->left_ = root_;
      } else {
        nptr parent = findParentForNode(node);
        if (!isNill(parent)) {
          if (cmp_(getKey(node), getKey(parent))) {
            parent->left_ = node;
          } else {
            parent->right_ = node;
          }
          node->parent_ = parent;
          fixHeightOfAllTree(node);
        } else {
          destroyNode(node);
          return iterator(nil_, nil_, false);
        }
      }
      ++size_;
      return iterator(node, nil_, false);
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
      if (position == cend()) {
        return end();
      }
      auto del = position.cur_;
      auto parent = del->parent_;
      iterator pos(position.cur_, nil_, false);
      ++pos;
      switch (getAmountOfChildren(del)) {
        case 0: {
          deleteTiesBetweenRelatives(parent, del);
          fixHeightOfAllTree(parent);
          if (root_ == del) {
            root_ = nil_;
          }
          break;
        }
        case 1: {
          nptr orphan = (del->left_ == nil_) ? del->right_ : del->left_;
          (parent->left_ == del) ? parent->left_ = orphan : parent->right_ = orphan;
          orphan->parent_ = parent;
          fixHeightOfAllTree(orphan);
          if (root_ == del) {
            root_ = orphan;
          }
          break;
        }
        case 2: {
          nptr successor = pos.cur_;
          nptr tmp = successor->parent_;
          del = replaceNodeWithAnotherData(del, successor->data_);
          if (isLeftChild(successor, successor->parent_)) {
            successor->parent_->left_ = successor->right_;
          } else {
            successor->parent_->right_ = successor->right_;
          }
          if (successor->right_ != nil_) {
            successor->right_->parent_ = successor->parent_;
          }
          fixHeightOfAllTree(tmp);
          pos = iterator(del, nil_, false);
          if (root_ == position.cur_) {
            root_ = del;
          }
          del = successor;
        }
      }
      destroyNode(del);
      --size_;
      return pos;
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
      return iterator(static_cast< const BinarySearchTree* >(this)->find(key).cur_, nil_, false);
    }

    citerator find(const Key& key) const
    {
      nptr tmp = root_;
      while (tmp != nil_ && !equal(getKey(tmp), key)) {
        if (cmp_(key, getKey(tmp))) {
          tmp = tmp->left_;
        } else {
          tmp = tmp->right_;
        }
      }
      return iterator(tmp, nil_, false);
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

    nptr rotateLeft(nptr node)
    {
      nptr tmp = node->right_;
      nptr parent = node->parent_;
      node->right_ = tmp->left_;
      tmp->left_->parent_ = node;
      tmp->left_ = node;
      tmp->parent_ = parent;
      node->parent_ = tmp;
      if (node == root_) {
        root_ = tmp;
        tmp->parent_ = nil_;
        nil_->left_ = tmp;
        nil_->right_ = tmp;
      } else {
        (isRightChild(node, parent)) ? parent->right_ = tmp : parent->left_ = tmp;
      }
      auto fix = node;
      fixHeightOfAllTree(fix);
      return node;
    }

    nptr rotateRight(nptr node)
    {
      nptr tmp = node->left_;
      nptr parent = node->parent_;
      node->left_ = tmp->right_;
      tmp->right_->parent_ = node;
      tmp->right_ = node;
      tmp->parent_ = parent;
      node->parent_ = tmp;
      if (node == root_) {
        root_ = tmp;
        tmp->parent_ = nil_;
        nil_->left_ = tmp;
        nil_->right_ = tmp;
      } else {
        (isRightChild(node, parent) ? parent->right_ = tmp : parent->left_ = tmp);
      }
      auto fix = node;
      fixHeightOfAllTree(fix);
      return node;
    }

    size_t getAmountOfChildren(nptr node)
    {
      if (node->left_ != nil_ || node->right_ != nil_) {
        return (node->left_ != nil_ && node->right_ != nil_) ? 2 : 1;
      }
      return 0;
    }

    const Value& at(const Key& key) const
    {
      auto it = find(key);
      if (it == cend()) {
        throw std::logic_error("No key in dictionary");
      }
      return it->second;
    }

    Value& at(const Key& key)
    {
      return const_cast< Value& >(static_cast< const BinarySearchTree& >(*this).at(key));
    }

    template< typename F >
    F traverse_lnr(F f) const
    {
      if (root_ != nil_) {
        Stack< nptr > stack;
        stack.push(root_);
        nptr tmp = root_;
        while (!stack.empty()) {
          while (tmp->left_ != nil_) {
            stack.push(tmp->left_);
            tmp = tmp->left_;
          }
          tmp = stack.top();
          stack.pop();
          f(tmp->data_);
          if (tmp->right_ != nil_) {
            stack.push(tmp->right_);
            tmp = tmp->right_;
          }
        }
      }
      return f;
    }

    template< typename F >
    F traverse_rnl(F f) const
    {
      if (root_ != nil_) {
        Stack< nptr > stack;
        stack.push(root_);
        nptr tmp = root_;
        while (!stack.empty()) {
          while (tmp->right_ != nil_) {
            stack.push(tmp->right_);
            tmp = tmp->right_;
          }
          tmp = stack.top();
          stack.pop();
          f(tmp->data_);
          if (tmp->left_ != nil_) {
            stack.push(tmp->left_);
            tmp = tmp->left_;
          }
        }
      }
      return f;
    }

    template< typename F >
    F traverse_breadth(F f) const
    {
      if (root_ != nil_) {
        Queue< nptr > queue;
        queue.push(root_);
        while (!queue.empty()) {
          nptr node = queue.front();
          queue.pop();
          f(node->data_);
          if (node->left_ != nil_) {
            queue.push(node->left_);
          }
          if (node->right_ != nil_) {
            queue.push(node->right_);
          }
        }
      }
      return f;
    }

    private:
    nptr nil_;
    nptr root_;
    Compare cmp_;
    size_t size_;

    nptr makeEmptyNode()
    {
      nptr tmp = detail::allocate< node >(1);
      detail::construct(std::addressof(tmp->parent_), tmp);
      detail::construct(std::addressof(tmp->left_), tmp);
      detail::construct(std::addressof(tmp->right_), tmp);
      detail::construct(std::addressof(tmp->height_), 0);
      return tmp;
    }

    template< typename... Args >
    nptr createNodeWithData(Args&& ... args)
    {
      auto tmp = makeEmptyNode();
      try {
        detail::construct(std::addressof(tmp->data_), std::forward< Args >(args)...);
        tmp->height_ = 1;
      } catch (...) {
        detail::deallocate(tmp);
        throw std::logic_error("Error in constructing node!");
      }
      tmp->parent_ = nil_;
      tmp->left_ = nil_;
      tmp->right_ = nil_;
      return tmp;
    }

    void destroyNode(nptr node)
    {
      detail::destroy(std::addressof(node->data_));
      detail::destroy(std::addressof(node->height_));
      detail::destroy(std::addressof(node->right_));
      detail::destroy(std::addressof(node->left_));
      detail::destroy(std::addressof(node->parent_));
      detail::deallocate(node);
    }

    void destroyTree(nptr node)
    {
     if (node != nil_) {
       destroyTree(node->left_);
       destroyTree(node->right_);
       destroyNode(node);
       size_--;
     }
    }

    void fixHeightOfAllTree(nptr node)
    {
      detail::fixHeight(node);
      if (node->parent_ != nil_) {
        fixHeightOfAllTree(node->parent_);
      }
    }

    const Key& getKey(nptr node) const
    {
      return node->data_.first;
    }

    bool equal(const Key& k1, const Key& k2) const
    {
      return !cmp_(k1, k2) && !cmp_(k2, k1);
    }

    bool isNill(nptr node)
    {
      return node == nil_;
    }

    nptr getMostLeftNode() const
    {
      if (root_ == nil_) {
        return nil_;
      }
      nptr tmp = root_;
      while (tmp->left_ != nil_) {
        tmp = tmp->left_;
      }
      return tmp;
    }

    nptr getMostRightNode() const
    {
      if (root_ == nil_) {
        return nil_;
      }
      nptr tmp = root_;
      while (tmp->right_ != nil_) {
        tmp = tmp->right_;
      }
      return tmp;
    }

    bool canBeRelative(nptr node, nptr relative)
    {
      return !equal(getKey(node), getKey(relative));
    }

    bool isDirectRelative(nptr node, nptr relative)
    {
      if (cmp_(getKey(node), getKey(relative)) && isNill(relative->left_)) {
        return true;
      } else if (cmp_(getKey(relative), getKey(node)) && isNill(relative->right_)) {
        return true;
      } else {
        return false;
      }
    }

    bool isLeftChild(nptr child, nptr parent)
    {
      return parent->left_ == child;
    }

    bool isRightChild(nptr child, nptr parent)
    {
      return parent->right_ == child;
    }

    nptr findParentForNode(nptr node)
    {
      auto tmp = root_;
      while (!isDirectRelative(node, tmp)) {
        if (!canBeRelative(node, tmp)) {
          return nil_;
        } else {
          tmp = (cmp_(getKey(node), getKey(tmp))) ? tmp->left_ : tmp->right_;
        }
      }
      return tmp;
    }

    void deleteTiesBetweenRelatives(nptr parent, nptr child)
    {
      if (child->parent_ == parent) {
        if (parent->right_ == child) {
          parent->right_ = nil_;
        }
        if (parent->left_ == child) {
          parent->left_ = nil_;
        }
      }
    }

    template< typename... Args >
    nptr replaceNodeWithAnotherData(nptr node, Args&& ... args)
    {
      nptr change = createNodeWithData(std::forward< Args >(args)...);
      change->parent_ = node->parent_;
      change->left_ = node->left_;
      change->right_ = node->right_;
      change->height_ = node->height_;

      if (node->left_ != nil_) {
        node->left_->parent_ = change;
      }
      if (node->right_ != nil_) {
        node->right_->parent_ = change;
      }

      nptr parent = node->parent_;
      if (isLeftChild(node, parent)) {
        parent->left_ = change;
      }
      if (isRightChild(node, parent)) {
        parent->right_ = change;
      }
      return change;
    }
  };
}
#endif
