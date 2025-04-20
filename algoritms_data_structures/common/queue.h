#ifndef QUEUE_H
#define QUEUE_H

#include "memoryImplementation.h"

namespace bazhenov {
  template< typename T >
  class Queue {
    public:
      Queue();
      explicit Queue(size_t capacity);
      Queue(const Queue& other);
      ~Queue() = default;

      Queue& operator=(const Queue& other);

      size_t size() const;
      bool empty() const noexcept;

      void push(const T& other);
      void pop();
      void swap(Queue& other);

      T& front();
      const T& front() const;
      T& back();
      const T& back() const;

    private:
      MemoryImplementation < T > impl_;
      size_t head_, tail_;
  };

  template< typename T >
  Queue< T >::Queue():
    impl_(),
    head_(0),
    tail_(0)
  {}

  template< typename T >
  Queue< T >::Queue(size_t capacity):
    impl_(capacity),
    head_(0),
    tail_(0)
  {}

  template< typename T >
  Queue< T >::Queue(const Queue& other)
  {
    size_t tmp = other.head_;
    while (tmp != other.tail_) {
      constructData(impl_.data_ + tmp, other.impl_.data_[tmp]);
      tmp == other.impl_.capacity_ - 1 ? tmp = 0 : ++tmp;
    }
    head_ = other.head_;
    tail_ = other.tail_;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(const Queue& other)
  {
    Queue tmp(other);
    swap(tmp);
    return *this;
  }

  template< typename T >
  void Queue< T >::push(const T& other)
  {
    if (impl_.size_ == impl_.capacity_ - 1) {
      Queue tmp(2 * impl_.capacity_);
      size_t cur = head_;
      while (cur != tail_) {
        tmp.push(impl_.data_[cur]);
        cur == impl_.capacity_ - 1 ? cur = 0 : ++cur;
      }
      tmp.push(other);
      swap(tmp);
    } else {
      constructData(impl_.data_ + tail_, other);
      impl_.size_++;
      tail_ == impl_.capacity_ - 1 ? tail_ = 0 : ++tail_;
    }
  }

  template< typename T >
  void Queue< T >::pop()
  {
    if (impl_.size_ == 0) {
      throw std::logic_error("Queue is empty!");
    } else {
      destroyData(impl_.data_ + head_);
      head_ == impl_.capacity_ - 1 ? head_ = 0 : head_++;
      impl_.size_--;
    }
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return impl_.size_ == 0;
  }

  template< typename T >
  void Queue< T >::swap(Queue& other)
  {
    impl_.swap(other.impl_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  template< typename T >
  T& Queue< T >::front()
  {
    if (impl_.size_ == 0) {
      throw std::logic_error("Queue is empty!");
    } else {
      return impl_.data_[head_];
    }
  }


  template< typename T >
  T& Queue< T >::back()
  {
    if (impl_.size_ == 0) {
      throw std::logic_error("Queue is empty!");
    } else {
      return impl_.data_[tail_ - 1];
    }
  }

  template< typename T >
  size_t Queue< T >::size() const
  {
    return impl_.size_;
  }

  template< typename T >
  const T& Queue< T >::front() const
  {
    if (impl_.size_ == 0) {
      throw std::logic_error("Queue is empty!");
    } else {
      return impl_.data_[head_];
    }
  }

  template< typename T >
  const T& Queue< T >::back() const
  {
    if (impl_.size_ == 0) {
      throw std::logic_error("Queue is empty!");
    } else {
      return impl_.data_[tail_ - 1];
    }
  }

}

#endif
