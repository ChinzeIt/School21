#pragma once
#include "s21_tree.h"

namespace s21 {
template <typename Key, typename T>
class Map {
 private:
  RBTree<Key, T> tree_;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = RBTree<Key, T>::TreeIterator;
  using const_iterator = RBTree<Key, T>::ConstTreeIterator;
  using size_type = std::size_t;

  Map() = default;
  ~Map() = default;
  Map(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item.first, item.second);
    }
  }
  Map(const Map& m) : tree_(m.tree_) {}
  Map(Map&& m) noexcept : tree_(std::move(m.tree_)) {}
  Map& operator=(const Map& m) {
    if (this != &m) {
      tree_ = m.tree_;
    }
    return *this;
  }
  Map& operator=(Map&& m) noexcept {
    if (this != &m) {
      tree_ = std::move(m.tree_);
    }
    return *this;
  }
  T& at(const Key& key) {
    auto node = tree_.findNode(tree_.root, key);
    if (node == nullptr) {
      throw std::out_of_range("Key not found");
    }
    return node->data;
  }
  T& operator[](const Key& key) {
    auto node = tree_.findNode(tree_.root, key);
    if (node) {
      return node->data;
    } else {
      tree_.insert(key, T{}, false, true);
      node = tree_.last_inserted_;
      return node->data;
    }
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
    bool inserted = tree_.insert(value.first, value.second, false, true);
    auto it = find(value.first);
    return {it, inserted};
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    bool inserted = tree_.insert(key, obj, false, true);
    auto it = find(key);
    return {it, inserted};
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    auto it = find(key);
    if (it != end()) {
      it.getData() = obj;
      return {it, false};
    } else {
      return insert(std::make_pair(key, obj));
    }
  }
  void erase(iterator pos) {
    if (pos != end()) {
      const Key& key = pos.getKey();
      tree_.remove(key, false);
    }
  }
  void swap(Map& other) noexcept { tree_.swap(other.tree_); }
  void merge(Map& other) {
    for (auto it = other.begin(); it != other.end();) {
      auto current = it++;
      const Key& key = current.getKey();
      const T& value = *current;

      auto res = insert(key, value);
      if (res.second) {
        other.erase(current);
      }
    }
  }
  bool contains(const Key& key) const {
    return tree_.findNode(tree_.root, key) != nullptr;
  }
  iterator find(const Key& key) {
    auto node = tree_.findNode(tree_.root, key);
    return iterator(node, &tree_);
  }
  const_iterator find(const Key& key) const {
    auto node = tree_.findNode(tree_.root, key);
    return const_iterator(node, &tree_);
  }
};
}  // namespace s21