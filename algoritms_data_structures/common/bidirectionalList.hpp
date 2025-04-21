#ifndef BIDIRECTIONAL_LIST_HPP
#define BIDIRECTIONAL_LIST_HPP

#include "memoryAllocation.hpp"
#include "bidirectionalNode.hpp"

namespace gruzdev {
  template< typename T >
  class BidirectionalList {
    public:
    template< typename P >
    class BidirectionalListIterator: public std::iterator< std::bidirectional_iterator_tag, P > {
      public:
      friend class BidirectionalList;

      using self = BidirectionalListIterator< P >;

      BidirectionalListIterator() = default;

      self& operator++()
      {
        assert(node_ != nullptr);
        node_ = (reversibility_) ? node_->prev_ : node_->next_;
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
        assert(node_ != nullptr);
        node_ = (reversibility_) ? node_->next_ : node_->prev_;
        return *this;
      }

      self operator--(int)
      {
        self tmp(*this);
        --(*this);
        return tmp;
      }

      P& operator*()
      {
        assert(node_ != nullptr);
        return node_->data_;
      }

      P* operator->()
      {
        assert(node_ != nullptr);
        return std::addressof(node_->data_);
      }

      bool operator==(const BidirectionalListIterator& other)
      {
        return node_ == other.node_ && list_ == other.list_;
      }

      bool operator!=(const BidirectionalListIterator& other)
      {
        return !(*this == other);
      }

      void swap(BidirectionalListIterator& other)
      {
        std::swap(node_, other.node_);
        std::swap(list_, other.list_);
      }

      private:
      detail::BidirectionalNode< P >* node_;
      const BidirectionalList< P >* list_;
      bool reversibility_;

      BidirectionalListIterator(detail::BidirectionalNode< P >* node, const BidirectionalList< P >* list, bool reversibility):
        node_(node),
        list_(list),
        reversibility_(reversibility)
      {}
    };

    template< typename P >
    class ConstBidirectionalListIterator: public std::iterator< std::bidirectional_iterator_tag, P > {
      public:
      using self = ConstBidirectionalListIterator< P >;

      friend class BidirectionalList;

      ConstBidirectionalListIterator() = default;

      ConstBidirectionalListIterator(const BidirectionalListIterator< P >& other):
        node_(other.node_),
        list_(other.list_),
        reversibility_(other.reversibility_)
      {}

      self& operator++()
      {
        assert(node_ != nullptr);
        node_ = (reversibility_) ? node_->prev_ : node_->next_;
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
        assert(node_ != nullptr);
        node_ = (reversibility_) ? node_->next_ : node_->prev_;
        return *this;
      }

      self operator--(int)
      {
        self tmp(*this);
        --(*this);
        return tmp;
      }

      const P& operator*() const
      {
        assert(node_ != nullptr);
        return node_->data_;
      }

      const P* operator->() const
      {
        assert(node_ != nullptr);
        return std::addressof(node_->data_);
      }

      bool operator==(const ConstBidirectionalListIterator& other)
      {
        return node_ == other.node_ && list_ == other.list_;
      }

      bool operator!=(const ConstBidirectionalListIterator& other)
      {
        return !(*this == other);
      }

      void swap(ConstBidirectionalListIterator& other)
      {
        std::swap(node_, other.node_);
        std::swap(list_, other.list_);
      }

      private:
      detail::BidirectionalNode< P >* node_;
      const BidirectionalList< P >* list_;
      bool reversibility_;

      ConstBidirectionalListIterator(detail::BidirectionalNode< P >* node, const BidirectionalList< P >* list, bool reversibility):
        node_(node),
        list_(list),
        reversibility_(reversibility)
      {}
    };

    using iterator = BidirectionalListIterator< T >;
    using citerator = ConstBidirectionalListIterator< T >;
    using node = detail::BidirectionalNode< T >*;
    using cnode = const detail::BidirectionalNode< T >*;

    iterator begin()
    {
      return iterator(beforeHead_->next_, this, false);
    }

    citerator cbegin() const
    {
      return citerator(beforeHead_->next_, this, false);
    }

    iterator end()
    {
      return iterator(beforeHead_, this, false);
    }

    citerator cend() const
    {
      return citerator(beforeHead_, this, false);
    }

    iterator rbegin()
    {
      return iterator(beforeHead_->prev_, this, true);
    }

    citerator crbegin() const
    {
      return citerator(beforeHead_->prev_, this, true);
    }

    iterator rend()
    {
      return iterator(beforeHead_, this, true);
    }

    citerator crend() const
    {
      return citerator(beforeHead_, this, true);
    }

    BidirectionalList():
      beforeHead_(allocateEmptyNode()),
      size_(0)
    {}

    BidirectionalList(size_t n):
      beforeHead_(allocateStorage(n)),
      size_(n)
    {}

    BidirectionalList(size_t n, const T& val):
      beforeHead_(allocateStorage(n, val)),
      size_(n)
    {}

    BidirectionalList(std::initializer_list< T > il):
      size_(il.size())
    {
      beforeHead_ = allocateStorage(0);
      auto begin = beforeHead_;
      auto tmp = il.begin();
      while (tmp != il.end()) {
        begin = allocateAtPosition(begin->next_, *tmp);
        ++tmp;
      }
    }

    ~BidirectionalList()
    {
      deallocateStorage(beforeHead_);
    }

    BidirectionalList(const BidirectionalList& other):
      size_(other.size_)
    {
      beforeHead_ = allocateStorage(0);
      auto begin = beforeHead_;
      auto tmp = other.cbegin();
      while (tmp != other.cend()) {
        begin = allocateAtPosition(begin->next_, *tmp);
        ++tmp;
      }
    }

    BidirectionalList(BidirectionalList&& other):
      beforeHead_(std::move(other.beforeHead_)),
      size_(other.size_)
    {
      other.beforeHead_ = nullptr;
      other.size_ = 0;
    }

    BidirectionalList& operator=(const BidirectionalList& other)
    {
      BidirectionalList tmp(other);
      swap(tmp);
      return *this;
    }

    BidirectionalList& operator=(BidirectionalList&& other)
    {
      BidirectionalList tmp(std::move(other));
      swap(tmp);
      return *this;
    }

    bool isEmpty() const
    {
      return size_ == 0;
    }

    size_t getSize() const
    {
      return size_;
    }

    T& getFront()
    {
      return *begin();
    }

    const T& getFront() const
    {
      return *cbegin();
    }

    T& getBack()
    {
      return *rbegin();
    }

    const T& getBack() const
    {
      return *crbegin();
    }

    void swap(BidirectionalList& other)
    {
      std::swap(beforeHead_, other.beforeHead_);
      std::swap(size_, other.size_);
    }

    template< typename... Args >
    iterator emplace(citerator position, Args&& ... args)
    {
      node node = allocateAtPosition(position.node_, std::forward< Args >(args)...);
      ++size_;
      return iterator(node, this, false);
    }

    template< class... Args >
    void emplaceFront(Args&& ... args)
    {
      emplace(cbegin(), std::forward< Args >(args)...);
    }

    template< class... Args >
    void emplaceBack(Args&& ... args)
    {
      emplace(cend(), std::forward< Args >(args)...);
    }

    template< typename Iterator >
    void insert(iterator pos, Iterator first, Iterator second)
    {
      auto iter = first;
      while (iter != second) {
        pos = emplace(pos, *iter);
        ++pos;
        ++iter;
      }
    }

    void pushFront(const T& value)
    {
      emplaceFront(value);
    }

    void pushFront(T&& val)
    {
      emplaceFront(std::move(val));
    }

    iterator erase(citerator position)
    {
      if (position == cend()) {
        throw std::logic_error("Invalid pointer to delete!");
      }
      node node = deallocateAtPosition(position.node_);
      return iterator(node, this, false);
    }

    citerator erase(citerator first, citerator second)
    {
      auto tmp = first;
      auto end = second;
      ++end;
      while (tmp != cend() && tmp != end) {
        tmp = erase(tmp);
      }
      return tmp;
    }

    void popFront()
    {
      erase(cbegin());
    }

    void popBack()
    {
      erase(--cend());
    }

    private:
    node beforeHead_;
    size_t size_;

    void deleteNodeCompletely(node tmp)
    {
      detail::destroy(std::addressof(tmp->data_));
      detail::destroy(std::addressof(tmp->next_));
      detail::destroy(std::addressof(tmp->prev_));
      detail::deallocate(tmp);
    }

    node allocateEmptyNode()
    {
      auto tmp = detail::allocate< detail::BidirectionalNode< T > >(1);
      detail::construct(std::addressof(tmp->next_), tmp);
      detail::construct(std::addressof(tmp->prev_), tmp);
      detail::construct(std::addressof(tmp->data_));
      return tmp;
    }

    template< class... Args >
    node allocateStorage(size_t n, Args&& ... args)
    {
      auto begin = allocateEmptyNode();
      try {
        auto tmp = begin;
        for (size_t i = 0; i < n; ++i) {
          tmp = allocateAtPosition(tmp->next_, std::forward< Args >(args)...);
        }
        tmp->next_ = begin;
        begin->prev_ = tmp;
      } catch (...) {
        deallocateStorage(begin);
        throw;
      }
      return begin;
    }

    void deallocateStorage(node head)
    {
      if (head != nullptr) {
        while (head != head->next_) {
          head = deallocateAtPosition(head);
        }
        deleteNodeCompletely(head);
      }
    }

    template< class... Args >
    node allocateAtPosition(node pos, Args&& ... args)
    {
      assert(pos != nullptr);
      auto node = detail::allocate< detail::BidirectionalNode< T > >(1);
      detail::construct(std::addressof(node->data_), std::forward< Args >(args)...);
      detail::construct(std::addressof(node->next_), pos);
      detail::construct(std::addressof(node->prev_), pos->prev_);
      auto tmp = pos->prev_;
      pos->prev_ = node;
      if (tmp != nullptr) {
        tmp->next_ = node;
      }
      return node;
    }

    node deallocateAtPosition(node pos)
    {
      if (pos != nullptr) {
        auto tmp = pos;
        if (pos->prev_ != nullptr) {
          pos->prev_->next_ = pos->next_;
        }
        if (pos->next_ != nullptr) {
          pos->next_->prev_ = pos->prev_;
        }
        pos = pos->next_;
        deleteNodeCompletely(tmp);
        return pos;
      } else {
        throw std::out_of_range("Delete from nullptr node is impossible");
      }
    }
  };
}
#endif
