#pragma once

namespace s21 {
template <typename T, std::size_t N>
class Array {
 private:
  T data_[N];

  template <typename Iter>
  class ArrayIterator {
   public:
    ArrayIterator() noexcept : ptr_(nullptr) {}
    ArrayIterator(Iter ptr) noexcept : ptr_(ptr) {}
    ~ArrayIterator() = default;
    auto& operator*() { return *ptr_; }

    ArrayIterator& operator++() {
      ++ptr_;
      return *this;
    }
    ArrayIterator& operator--() {
      --ptr_;
      return *this;
    }
    bool operator==(const ArrayIterator& other) const noexcept {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ArrayIterator& other) const noexcept {
      return ptr_ != other.ptr_;
    }
    Iter ptr_;
  };

  template <typename Iter>
  class ConstArrayIterator {
   public:
    ConstArrayIterator() noexcept : ptr_(nullptr) {}
    ConstArrayIterator(Iter ptr) noexcept : ptr_(ptr) {}
    ~ConstArrayIterator() = default;
    auto& operator*() const { return *ptr_; }
    ConstArrayIterator& operator++() {
      ++ptr_;
      return *this;
    }
    ConstArrayIterator& operator--() {
      --ptr_;
      return *this;
    }
    bool operator==(const ConstArrayIterator& other) const noexcept {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ConstArrayIterator& other) const noexcept {
      return ptr_ != other.ptr_;
    }
    Iter ptr_;
  };

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ArrayIterator<T*>;
  using const_iterator = ConstArrayIterator<const T*>;
  using size_type = std::size_t;

  Array() noexcept {
    for (size_type i = 0; i < N; ++i) data_[i] = value_type{};
  }
  ~Array() noexcept = default;
  Array(std::initializer_list<value_type> const& items) {
    if (items.size() > N) throw std::out_of_range("Problems to init");

    size_type i = 0;
    for (const auto& item : items) data_[i++] = item;

    for (; i < N; i++) data_[i] = value_type{};
  }
  Array(const Array& other) {
    for (size_type i = 0; i < N; i++) data_[i] = other.data_[i];
  }
  Array(Array&& other) noexcept {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = std::move(other.data_[i]);
    }
  }
  Array& operator=(Array&& other) noexcept {
    if (this != &other) {
      for (size_type i = 0; i < N; ++i) data_[i] = std::move(other.data_[i]);
    }
    return *this;
  }
  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Index out");
    }
    return data_[pos];
  }
  const_reference at(size_type pos) const {
    if (pos >= N) {
      throw std::out_of_range("Index out");
    }
    return data_[pos];
  }
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }
  const_reference front() const {
    if (N == 0) throw std::out_of_range("No size");
    return data_[0];
  }
  const_reference back() const {
    if (N == 0) throw std::out_of_range("No size");
    return data_[N - 1];
  }
  iterator data() noexcept { return iterator(data_); }
  const_iterator data() const noexcept { return const_iterator(data_); }
  iterator begin() { return iterator(data_); }
  iterator end() { return iterator(data_ + N); }
  const_iterator begin() const { return const_iterator(data_); }
  const_iterator end() const { return const_iterator(data_ + N); }
  bool empty() const noexcept { return N == 0; }
  size_type size() const noexcept { return N; }
  size_type max_size() const noexcept { return N; }
  void swap(Array& other) noexcept {
    for (size_type i = 0; i < N; ++i) std::swap(data_[i], other.data_[i]);
  }
  void fill(const_reference value) {
    for (size_type i = 0; i < N; ++i) data_[i] = value;
  }
};
}  // namespace s21