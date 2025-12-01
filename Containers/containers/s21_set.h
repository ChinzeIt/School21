#pragma once
#include "s21_tree.h"

namespace s21 {
template <typename Key, typename T>
class Set {
 private:
  RBTree<Key, T> tree_;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = Key&;
  using const_reference = const Key&;
  using iterator = RBTree<Key, T>::TreeIterator;
  using const_iterator = RBTree<Key, T>::ConstTreeIterator;
  using size_type = std::size_t;

  Set() = default;
  ~Set() = default;
  Set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) insert(item);
  }
  Set(const Set& s) : tree_(s.tree_) {}
  Set(Set&& s) noexcept : tree_(std::move(s.tree_)) {}
  Set& operator=(const Set& s) {
    if (this != &s) {
      tree_ = s.tree_;
    }
    return *this;
  }
  Set& operator=(Set&& s) noexcept {
    if (this != &s) {
      tree_ = std::move(s.tree_);
    }
    return *this;
  }
  iterator begin() noexcept { return tree_.begin(); }
  iterator end() noexcept { return tree_.end(); }
  const_iterator begin() const noexcept { return tree_.begin(); }
  const_iterator end() const noexcept { return tree_.end(); }
  bool empty() const noexcept { return tree_.size() == 0; }
  size_type size() const noexcept { return tree_.size(); }
  size_type max_size() const noexcept { return tree_.max_size(); }
  void clear() { tree_.clear(); }
  std::pair<iterator, bool> insert(const value_type& value) {
    bool inserted = tree_.insert(value, true, false);
    iterator it = find(value);
    return {it, inserted};
  }
  void erase(iterator pos) {
    if (pos != end()) tree_.remove(*pos, true);
  }
  void swap(Set& other) noexcept { tree_.swap(other.tree_); }
  void merge(Set& other) {
    for (auto it = other.begin(); it != other.end();) {
      auto current = it++;
      auto res = insert(*current);
      if (res.second) {
        other.erase(current);
      }
    }
  }
  iterator find(const Key& key) {
    auto node = tree_.findNode(tree_.root, key);
    return iterator(node, &tree_);
  }

  const_iterator find(const Key& key) const {
    auto node = tree_.findNode(tree_.root, key);
    return const_iterator(node, &tree_);
  }
  bool contains(const Key& key) const {
    return tree_.findNode(tree_.root, key) != nullptr;
  }
};
}  // namespace s21