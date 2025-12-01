#pragma once

namespace s21 {

template <typename T>
class Vector {
 private:
  T* data_;
  size_t size_;
  size_t capacity_;

  template <typename Iter>

  class VectorIterator {
   public:
    VectorIterator() noexcept
        : current(nullptr), begin_(nullptr), end_(nullptr) {}
    VectorIterator(Iter ptr, Iter begin, Iter end)
        : current(ptr), begin_(begin), end_(end) {}
    ~VectorIterator() = default;

    auto& operator*() { return *current; }

    VectorIterator& operator++() {
      if (current == end_) throw std::out_of_range("Iterator can not work");
      ++current;
      return *this;
    }

    VectorIterator& operator--() {
      if (current == begin_) throw std::out_of_range("Iterator can not work");
      --current;
      return *this;
    }
    bool operator==(const VectorIterator& other) const noexcept {
      return current == other.current;
    }

    bool operator!=(const VectorIterator& other) const noexcept {
      return current != other.current;
    }

    // CUSTOM

    size_t operator-(const VectorIterator& other) const {
      return current - other.current;
    }

    Iter current;
    Iter begin_;
    Iter end_;
  };

  template <typename Iter>

  class ConstVectorIterator {
   public:
    ConstVectorIterator() noexcept
        : current(nullptr), begin_(nullptr), end_(nullptr) {}
    ConstVectorIterator(Iter ptr, Iter begin, Iter end)
        : current(ptr), begin_(begin), end_(end) {}
    ~ConstVectorIterator() = default;

    const auto& operator*() const { return *current; }

    ConstVectorIterator& operator++() {
      if (current == end_) throw std::out_of_range("Iterator can not work");
      ++current;
      return *this;
    }

    ConstVectorIterator& operator--() {
      if (current == begin_) throw std::out_of_range("Iterator can not work");
      --current;
      return *this;
    }

    bool operator==(const ConstVectorIterator& other) const noexcept {
      return current == other.current;
    }

    bool operator!=(const ConstVectorIterator& other) const noexcept {
      return current != other.current;
    }

    // CUSTOM

    size_t operator-(const ConstVectorIterator& other) const {
      return current - other.current;
    }

    Iter current;
    Iter begin_;
    Iter end_;
  };

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator<T*>;
  using const_iterator = ConstVectorIterator<const T*>;
  using size_type = std::size_t;

  Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}
  Vector(size_type n) : data_(new T[n]), size_(0), capacity_(0) {
    for (size_type i = 0; i < n; ++i) data_[i] = T();
  }
  ~Vector() noexcept { delete[] data_; }
  Vector(std::initializer_list<value_type> items)
      : data_(new T[items.size()]),
        size_(items.size()),
        capacity_(items.size()) {
    size_type i = 0;
    for (const auto& item : items) data_[i++] = item;
  }
  Vector(const Vector& other) noexcept
      : data_(new T[other.capacity_]),
        size_(other.size_),
        capacity_(other.capacity_) {
    for (size_type i = 0; i < size_; ++i) data_[i] = other.data_[i];
  }
  Vector(Vector&& other) noexcept
      : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }
  reference at(size_type pos) const {
    if (pos >= size_) throw std::out_of_range("Index out of range");
    return data_[pos];
  }
  reference operator[](size_type pos) noexcept { return data_[pos]; }
  const_reference front() const {
    if (size_ == 0) throw std::out_of_range("Empty vector");
    return data_[0];
  }
  const_reference back() const {
    if (size_ == 0) throw std::out_of_range("Empty vector");
    return data_[size_ - 1];
  }
  T* data() const noexcept { return data_; }
  iterator begin() noexcept {
    return iterator(data_, data_, data_ + capacity_);
  }
  iterator end() noexcept {
    return iterator(data_ + size_, data_, data_ + capacity_);
  }
  const_iterator begin() const noexcept {
    return const_iterator(data_, data_, data_ + capacity_);
  }
  const_iterator end() const noexcept {
    return const_iterator(data_ + size_, data_, data_ + capacity_);
  }
  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type capacity() const noexcept { return capacity_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }
  void reserve(size_type new_size) {
    if (new_size > capacity_) {
      T* new_data_ = new T[new_size];
      for (size_type i = 0; i < size_; ++i) new_data_[i] = data_[i];
      delete[] data_;
      data_ = new_data_;
      capacity_ = new_size;
    } else {
      throw std::out_of_range("Nothing reserve");
    }
  }
  void shrink_to_fit() {
    if (capacity_ > size_) {
      T* new_data_ = new T[size_];
      for (size_type i = 0; i < size_; ++i) new_data_[i] = data_[i];
      delete[] data_;
      data_ = new_data_;
      capacity_ = size_;
    } else {
      throw std::out_of_range("Nothing shrink to fit");
    }
  }
  void clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - begin();
    if (index > size_) {
      throw std::out_of_range("Nothing insert");
    }
    if (size_ >= capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

    for (size_type i = size_; i > index; --i) data_[i] = data_[i - 1];

    data_[index] = value;
    ++size_;

    return iterator(data_ + index, data_, data_ + capacity_);
  }
  void erase(iterator pos) {
    size_type index = pos - begin();
    if (index > size_) {
      throw std::out_of_range("Nothing erase");
    }
    for (size_type i = index; i < size_ - 1; ++i) data_[i] = data_[i + 1];
    --size_;
  }
  void push_back(const_reference value) noexcept {
    if (size_ >= capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
  }
  void pop_back() {
    if (size_ == 0) throw std::out_of_range("Nothing pop back");
    --size_;
  }
  void swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }
};
}  // namespace s21