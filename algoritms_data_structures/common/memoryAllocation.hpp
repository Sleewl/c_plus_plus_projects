#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cstdlib>
#include <utility>
#include <cassert>
#include <stdexcept>
#include "list.h"

namespace gruzdev {
  namespace detail {
    template< typename T >
    T* allocate(size_t n)
    {
      return static_cast< T* >(::operator new(n * sizeof(T)));
    }

    template< typename T >
    void deallocate(T* ptr)
    {
      ::operator delete(ptr);
    }

    template< typename T, typename... Args >
    void construct(T* ptr, Args&& ...args)
    {
      new(static_cast< void* >(ptr)) T(std::forward< Args >(args)...);
    }

    template< typename T >
    void destroy(T* ptr)
    {
      ptr->~T();
    }
  }

  template< typename T >
  struct memoryAllocation {
    memoryAllocation():
      size_(0),
      beforeHead_(allocateStorage(0))
    {}

    explicit memoryAllocation(size_t n):
      size_(n),
      beforeHead_(allocateStorage(n))
    {}

    memoryAllocation(const memoryAllocation& other):
      size_(other.size_),
      beforeHead_(allocateStorage(other.size_))
    {}

    memoryAllocation(memoryAllocation&& other) noexcept:
      size_(other.size_),
      beforeHead_(other.beforeHead_)
    {
      other.beforeHead_ = nullptr;
    }

    ~memoryAllocation()
    {
      deallocateStorage(beforeHead_);
    }

    void swap(memoryAllocation& other)
    {
      std::swap(beforeHead_, other.beforeHead_);
      std::swap(size_, other.size_);
    }

    detail::List< T >* allocateAfterPosition(detail::List< T >* pos)
    {
      assert(pos != nullptr);
      auto node = detail::allocate< detail::List< T > >(1);
      detail::construct(std::addressof(node->next_), pos->next_);
      pos->next_ = node;
      size_++;
      return node;
    }

    detail::List< T >* allocateStorage(size_t n)
    {
      auto begin = detail::allocate< detail::List< T > >(1);
      try {
        auto it = begin;
        for (size_t i = 0; i < n; ++i) {
          detail::construct(std::addressof(it->next_), nullptr);
          it->next_ = detail::allocate< detail::List< T > >(1);
          it = it->next_;
        }
        detail::construct(std::addressof(it->next_), nullptr);
        size_ = n;
      } catch (...) {
        deallocateStorage(begin);
        throw;
      }
      return begin;
    }

    detail::List< T >* deallocateAfterPosition(detail::List< T >* pos)
    {
      if (pos != nullptr) {
        detail::List< T >* tmp = pos->next_;
        pos->next_ = tmp->next_;
        detail::destroy(std::addressof(tmp->data_));
        detail::destroy(std::addressof(tmp->next_));
        detail::deallocate(tmp);
        size_--;
        return pos->next_;
      } else {
        throw std::out_of_range("Delete from nullptr list is impossible");
      }
    }

    void deallocateStorage(detail::List< T >* head)
    {
      if (head != nullptr) {
        while (head->next_ != nullptr) {
          deallocateAfterPosition(head);
        }
        detail::destroy(std::addressof(head->data_));
        detail::destroy(std::addressof(head->next_));
        detail::deallocate(head);
      }
    }

    size_t size_;
    detail::List< T >* beforeHead_;
  };
}
#endif
