#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <cassert>
#include <algorithm>

namespace gruzdev {
  namespace detail {
    template< typename T >
    struct TreeNode {
      using node = TreeNode< T >*;

      T data_;
      int height_;

      node parent_;
      node left_;
      node right_;
    };

    template< typename T >
    int getChildHeightDifference(TreeNode< T >* node)
    {
      return node->left_->height_ - node->right_->height_;
    }

    template< typename T >
    void fixHeight(TreeNode< T >* node)
    {
      int hl = node->left_->height_;
      int hr = node->right_->height_;
      node->height_ = std::max(hl, hr) + 1;
    }
  }
}
#endif

