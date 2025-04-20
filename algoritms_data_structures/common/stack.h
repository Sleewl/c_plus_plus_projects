#ifndef STACK_H
#define STACK_H

#include "memoryImplementation.h"

namespace bazhenov {
  template< typename T >
  class Stack {
    public:
      Stack() = default;
      explicit Stack(size_t capacity);
      Stack(const Stack& other);
      ~Stack() = default;

      Stack& operator=(const Stack& other);

      void push(const T& other);
      void pop();

      size_t count() const;
      bool empty() const noexcept;

      T& top();
      const T& top() const;
    private:
      MemoryImplementation< T > impl_;
  };

  template< typename T >
  Stack< T >::Stack(size_t capacity):
    impl_(capacity)
  {}

  template< typename T >
  Stack< T >::Stack(const Stack& other)
  {
    while (impl_.size_ < other.impl_.size_) {
      constructData(impl_.data_ + impl_.size_, other.impl_.data_[impl_.size_]);
      ++impl_.size_;
    }
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack& other)
  {
    Stack tmp(other);
    impl_.swap(tmp.impl_);
    return *this;
  }

  template< typename T >
  bool Stack< T >::empty() const noexcept
  {
    return impl_.size_ == 0;
  }

  template< typename T >
  void Stack< T >::push(const T& other)
  {
    if (impl_.size_ == impl_.capacity_) {
      Stack tmp(2 * impl_.capacity_ + 1);
      while (tmp.count() < impl_.size_) {
        tmp.push(impl_.data_[tmp.count()]);
      }
      tmp.push(other);
      impl_.swap(tmp.impl_);
    } else {
      constructData(impl_.data_ + impl_.size_,other);
      ++impl_.size_;
    }
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (impl_.size_ == 0) {
      throw std::logic_error("Stack is empty!");
    } else {
      impl_.size_--;
      destroyData(impl_.data_ + impl_.size_);
    }
  }

  template< typename T >
  T& Stack< T >::top()
  {
    if (impl_.size_ == 0) {
      throw std::logic_error("Stack is empty!");
    } else {
      return impl_.data_[impl_.size_ - 1];
    }
  }

  template< typename T >
  size_t Stack< T >::count() const
  {
    return impl_.size_;
  }

  template< typename T >
  const T& Stack< T >::top() const
  {
    if (impl_.size_ == 0) {
      throw std::logic_error("Stack is empty!");
    } else {
      return impl_.data_[impl_.size_ - 1];
    }
  }

}

#endif
