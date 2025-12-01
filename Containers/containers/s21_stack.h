#pragma once

namespace s21 {
template <typename T>
class Stack {
 private:
  struct Node {
    T data_;
    Node* prev_ = nullptr;

    Node(const T& value) : data_(value), prev_(nullptr) {}
  };
  Node* front_;
  Node* back_;
  size_t size_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  Stack() noexcept : front_(nullptr), back_(nullptr), size_(0) {}
  ~Stack() {
    while (back_) {
      Node* temp = back_;
      back_ = back_->prev_;
      delete temp;
    }
    front_ = nullptr;
    size_ = 0;
  }
  Stack(std::initializer_list<value_type> const& items) noexcept : Stack() {
    for (const auto item : items) push(item);
  }
  Stack(const Stack& s) : Stack() {
    size_type count = 0;
    for (Node* curr = s.back_; curr != nullptr; curr = curr->prev_) count++;

    T* buffer = new T[count];
    Node* curr = s.back_;
    for (size_type i = 0; i < count; ++i, curr = curr->prev_)
      buffer[count - i - 1] = curr->data_;
    for (size_type i = 0; i < count; ++i) push(buffer[i]);
    delete[] buffer;
  }
  Stack(Stack&& s) noexcept : front_(s.front_), back_(s.back_), size_(s.size_) {
    s.front_ = nullptr;
    s.back_ = nullptr;
    s.size_ = 0;
  }
  Stack& operator=(Stack&& s) noexcept {
    if (this != &s) {
      clear();
      front_ = s.front_;
      back_ = s.back_;
      size_ = s.size_;
      s.front_ = nullptr;
      s.back_ = nullptr;
      s.size_ = 0;
    }
    return *this;
  }
  const_reference top() const {
    if (!back_) throw std::out_of_range("Stack is empty");
    return back_->data_;
  }
  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  void push(const_reference value) noexcept {
    Node* node = new Node(value);
    if (empty()) {
      front_ = back_ = node;
    } else {
      node->prev_ = back_;
      back_ = node;
    }
    ++size_;
  }
  void pop() {
    if (empty()) throw std::out_of_range("Stack is empty");
    Node* temp = back_;
    back_ = back_->prev_;
    delete temp;
    --size_;
    if (size_ == 0) front_ = nullptr;
  }
  void swap(Stack& other) noexcept {
    std::swap(front_, other.front_);
    std::swap(back_, other.back_);
    std::swap(size_, other.size_);
  }
  void clear() {
    while (back_) {
      Node* temp = back_;
      back_ = back_->prev_;
      delete temp;
    }
    front_ = nullptr;
    size_ = 0;
  }
};
}  // namespace s21