#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <iterator>
#include "list.h"
#include "memoryAllocation.hpp"

namespace bazhenov {
  template< typename T >
  class ForwardList {
    public:
    template< typename P >
    class ListIterator: public std::iterator< std::forward_iterator_tag, P > {
      public:
      using self = ListIterator< P >;

      friend class ForwardList;

      ListIterator() = default;

      self& operator++()
      {
        assert(node_ != nullptr);
        node_ = node_->next_;
        return *this;
      }

      self operator++(int)
      {
        ListIterator tmp(*this);
        ++(*this);
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

      bool operator==(const ListIterator& other)
      {
        return node_ == other.node_ && list_ == other.list_;
      }

      bool operator!=(const ListIterator& other)
      {
        return !(*this == other);
      }

      void swap(ListIterator& other)
      {
        std::swap(node_, other.node_);
        std::swap(list_, other.list_);
      }

      private:
      detail::List< P >* node_;
      const ForwardList< P >* list_;

      ListIterator(detail::List< P >* node, const ForwardList< P >* list):
        node_(node),
        list_(list)
      {}
    };

    template< typename P >
    class ConstListIterator: public std::iterator< std::forward_iterator_tag, P > {
      public:
      using self = ConstListIterator< P >;

      friend class ForwardList;

      ConstListIterator() = default;

      ConstListIterator(const ListIterator< P >& other):
        node_(other.node_),
        list_(other.list_)
      {}

      self& operator++()
      {
        assert(node_ != nullptr);
        node_ = node_->next_;
        return *this;
      }

      self operator++(int)
      {
        ConstListIterator tmp(*this);
        ++(*this);
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

      bool operator==(const ConstListIterator& other)
      {
        return node_ == other.node_ && list_ == other.list_;
      }

      bool operator!=(const ConstListIterator& other)
      {
        return !(*this == other);
      }

      void swap(ConstListIterator& other)
      {
        std::swap(node_, other.node_);
        std::swap(list_, other.list_);
      }

      private:
      detail::List< P >* node_;
      const ForwardList< P >* list_;

      ConstListIterator(detail::List< P >* node, const ForwardList< P >* list):
        node_(node),
        list_(list)
      {}
    };

    using iterator = ListIterator< T >;
    using citerator = ConstListIterator< T >;
    using list = detail::List< T >*;
    using clist = const detail::List< T >*;

    ForwardList()
    {
      detail::construct(std::addressof(impl_.beforeHead_->data_));
    }

    explicit ForwardList(size_t n):
      impl_(n)
    {
      detail::construct(std::addressof(impl_.beforeHead_->data_));
    }

    ForwardList(size_t n, const T& val):
      impl_(n)
    {
      detail::construct(std::addressof(impl_.beforeHead_->data_));
      list tmp = impl_.beforeHead_->next_;
      while (tmp != nullptr) {
        detail::construct(std::addressof(tmp->data_), val);
        tmp = tmp->next_;
      }
    }

    template< typename Iterator >
    ForwardList(Iterator begin, Iterator end):
      impl_(std::distance(begin, end))
    {
      detail::construct(std::addressof(impl_.beforeHead_->data_));
      list tmp = impl_.beforeHead_->next_;
      Iterator it = begin;
      while (tmp != nullptr || it != end) {
        detail::construct(std::addressof(tmp->data_), *it);
        tmp = tmp->next_;
        ++it;
      }
    }

    ~ForwardList() = default;

    ForwardList(const ForwardList& other):
      impl_(other.impl_)
    {
      clist it1 = other.impl_.beforeHead_;
      list it2 = impl_.beforeHead_;
      while (it1 != nullptr) {
        detail::construct(std::addressof(it2->data_), it1->data_);
        it1 = it1->next_;
        it2 = it2->next_;
      }
    }

    ForwardList& operator=(const ForwardList& other)
    {
      ForwardList tmp(other);
      swap(tmp);
      return *this;
    }

    ForwardList(ForwardList&& other) noexcept:
      impl_(std::move(other.impl_))
    {
      other.impl_.size_ = 0;
    }

    ForwardList& operator=(ForwardList&& other) noexcept
    {
      ForwardList tmp(std::move(other));
      swap(tmp);
      return *this;
    }

    void swap(ForwardList& other)
    {
      impl_.swap(other.impl_);
    }

    size_t getSize() const
    {
      return impl_.size_;
    }

    const T& front() const
    {
      if (impl_.beforeHead_ == nullptr || impl_.beforeHead_->next_ == nullptr) {
        throw std::logic_error("ForwardList is empty!");
      }
      return impl_.beforeHead_->next_->data_;
    }

    T& front()
    {
      return const_cast< T& >(static_cast< const ForwardList< T >& >(*this).front());
    }

    bool isEmpty() const
    {
      return impl_.size_ == 0;
    }

    iterator before_begin()
    {
      return iterator(impl_.beforeHead_, this);
    }

    iterator begin()
    {
      assert(impl_.beforeHead_->next_ != nullptr);
      return iterator(impl_.beforeHead_->next_, this);
    }

    iterator end()
    {
      return iterator(nullptr, this);
    }

    citerator cbefore_begin() const
    {
      return citerator(impl_.beforeHead_, this);
    }

    citerator cbegin() const
    {
      assert(impl_.beforeHead_->next_ != nullptr);
      return citerator(impl_.beforeHead_->next_, this);
    }

    citerator cend() const
    {
      return citerator(nullptr, this);
    }

    template< typename... Args >
    iterator emplaceAfter(citerator position, Args&&... args)
    {
      list node = impl_.allocateAfterPosition(position.node_);
      detail::construct(std::addressof(node->data_), std::forward< Args >(args)...);
      return iterator(node, this);
    }

    template< typename... Args >
    iterator emplaceFront(Args&&... args)
    {
      return emplaceAfter(iterator(impl_.beforeHead_, this), std::forward< Args >(args)...);
    }

    void pushFront(const T& val)
    {
      emplaceFront(val);
    }

    void pushFront(T&& val)
    {
      emplaceFront(std::move(val));
    }

    iterator insertAfter(citerator position, const T& val)
    {
      return emplaceAfter(position, val);
    }

    iterator insertAfter(citerator position, T&& val)
    {
      return emplaceAfter(position, std::move(val));
    }

    iterator eraseAfter(citerator position)
    {
      list node = impl_.deallocateAfterPosition(position.node_);
      return iterator(node, this);
    }

    iterator eraseAfter(citerator first, citerator second)
    {
      list end = second.node_->next_;
      list it = first.node_;
      while (it->next_ != end) {
        impl_.deallocateAfterPosition(it);
        it = first.node_;
      }
      return iterator(it, this);
    }
    void popFront()
    {
      if (impl_.beforeHead_->next_ != nullptr) {
        eraseAfter(before_begin());
      } else {
        throw std::out_of_range("ForwardList is empty!");
      }
    }

    private:
    memoryAllocation< T > impl_;
  };

}
#endif
