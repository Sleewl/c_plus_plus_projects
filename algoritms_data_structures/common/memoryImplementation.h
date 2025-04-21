#ifndef MEMORYIMPLEMENTATION_H
#define MEMORYIMPLEMENTATION_H

#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace gruzdev {
  template< typename T >
  class MemoryImplementation {
    public:
      T* data_;
      size_t capacity_;
      size_t size_;

      MemoryImplementation();
      explicit MemoryImplementation(size_t capacity);
      ~MemoryImplementation();

      void swap(MemoryImplementation& other);

    private:
      MemoryImplementation(const MemoryImplementation& other) = delete;
      MemoryImplementation& operator=(const MemoryImplementation& other) = delete;
  };

  template< typename T1, typename T2 >
  void constructData(T1* data, const T2& value )
  {
    new (data) T2(value);
  }

  template< typename T >
  void destroyData(T* data)
  {
    data->~T();
  }

  template< typename T >
  MemoryImplementation< T >::MemoryImplementation():
    data_(static_cast< T* >(operator new(sizeof(T) * 10))),
    capacity_(10),
    size_(0)
  {}

  template< typename T >
  MemoryImplementation< T >::MemoryImplementation(size_t capacity):
    data_(static_cast< T* >(operator new(sizeof(T) * capacity))),
    capacity_(capacity),
    size_(0)
  {}

  template< typename T >
  MemoryImplementation< T >::~MemoryImplementation()
  {
    T* tmp = data_;
    while (tmp != data_ + capacity_) {
      destroyData(tmp);
      ++tmp;
    }
    operator delete(data_);
  }

  template<typename T>
  void MemoryImplementation< T >::swap(MemoryImplementation& other)
  {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
  }

}

#endif
