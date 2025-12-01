#pragma once
#include "../containers/s21_tree.h"

namespace s21 {
template <typename Key, typename T>
class MultiSet {
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

  MultiSet() = default;
  ~MultiSet() = default;
  MultiSet(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) insert(item);
  }
  MultiSet(const MultiSet& ms) : tree_(ms.tree_) {}
  MultiSet(MultiSet&& ms) noexcept : tree_(std::move(ms.tree_)) {}
  MultiSet& operator=(const MultiSet& ms) {
    if (this != &ms) {
      tree_ = ms.tree_;
    }
    return *this;
  }
  MultiSet& operator=(MultiSet&& ms) noexcept {
    if (this != &ms) {
      tree_ = std::move(ms.tree_);
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
  iterator insert(const value_type& value) {
    tree_.insert(value, true, true);
    return iterator(tree_.last_inserted_, &tree_);
  }
  void erase(iterator pos) {
    if (pos != end()) tree_.remove(*pos, true);
  }
  void swap(MultiSet& other) noexcept { tree_.swap(other.tree_); }
  void merge(MultiSet& other) {
    for (auto it = other.begin(); it != other.end();) {
      auto current = it++;
      insert(*current);
      other.erase(current);
    }
    other.clear();
  }
  size_type count(const Key& key) const {
    auto first = lower_bound(key);
    auto last = upper_bound(key);
    size_type cnt = 0;
    for (auto it = first; it != last; ++it) ++cnt;
    return cnt;
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
  std::pair<iterator, iterator> equal_range(const Key& key) {
    return {lower_bound(key), upper_bound(key)};
  }
  iterator lower_bound(const Key& key) { return tree_.lower_bound(key); }
  iterator upper_bound(const Key& key) { return tree_.upper_bound(key); }
  const_iterator lower_bound(const Key& key) const {
    return tree_.lower_bound(key);
  }
  const_iterator upper_bound(const Key& key) const {
    return tree_.upper_bound(key);
  }
};
}  // namespace s21