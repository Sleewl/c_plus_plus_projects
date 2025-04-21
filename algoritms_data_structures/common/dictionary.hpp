#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <AVLTree.hpp>

namespace gruzdev {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary {
    public:
    using pair = typename AVLTree< Key, Value >::pair;
    using iterator = typename AVLTree< Key, Value >::iterator;
    using citerator = typename AVLTree< Key, Value >::citerator;

    Dictionary(const Compare& cmp = Compare()):
      tree_(cmp)
    {}

    Dictionary(std::initializer_list< pair > il, const Compare& cmp = Compare()):
      tree_(il, cmp)
    {}

    Dictionary(const Dictionary& other) = default;

    Dictionary(Dictionary&& other) = default;

    ~Dictionary() = default;

    Dictionary& operator=(const Dictionary& other) = default;

    Dictionary& operator=(Dictionary&& other) = default;


    iterator begin()
    {
      return tree_.begin();
    }

    citerator begin() const
    {
      return tree_.begin();
    }

    iterator end()
    {
      return tree_.end();
    }

    citerator end() const
    {
      return tree_.end();
    }

    citerator cbegin() const
    {
      return tree_.cbegin();
    }

    citerator cend() const
    {
      return tree_.cend();
    }

    bool isEmpty() const
    {
      return tree_.isEmpty();
    }

    size_t getSize() const
    {
      return tree_.getSize();
    }

    iterator insert(const pair& val)
    {
      return tree_.insert(val);
    }


    iterator insert(pair&& val)
    {
      return tree_.insert(std::move(val));
    }


    iterator find(const Key& key)
    {
      return tree_.find(key);
    }

    citerator find(const Key& key) const
    {
      return tree_.find(key);
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
      return const_cast< Value& >(static_cast< const Dictionary& >(*this).at(key));
    }

    void swap(Dictionary& other)
    {
      tree_.swap(other.forwardList_);
    }

    iterator erase(const Key& key)
    {
      return tree_.erase(key);
    }

    private:
    AVLTree< Key, Value, Compare > tree_;
    Compare cmp_;
  };
}
#endif
