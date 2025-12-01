#pragma once

namespace s21 {
template <typename T>

class Queue {
 private:
  struct Node {
    T data_;
    Node* next_ = nullptr;

    Node(const T& value) : data_(value), next_(nullptr) {}
  };
  Node* front_;
  Node* back_;
  size_t size_;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  Queue() noexcept : front_(nullptr), back_(nullptr), size_(0) {}
  ~Queue() {
    while (front_) {
      Node* temp = front_;
      front_ = front_->next_;
      delete temp;
    }
    back_ = nullptr;
    size_ = 0;
  }
  Queue(std::initializer_list<value_type> const& items) noexcept : Queue() {
    for (const auto item : items) push(item);
  }
  Queue(const Queue& q) : Queue() {
    Node* current = q.front_;
    while (current) {
      push(current->data_);
      current = current->next_;
    }
  }
  Queue(Queue&& q) noexcept : front_(q.front_), back_(q.back_), size_(q.size_) {
    q.front_ = nullptr;
    q.back_ = nullptr;
    q.size_ = 0;
  }
  Queue& operator=(Queue&& q) noexcept {
    if (this != &q) {
      clear();
      front_ = q.front_;
      back_ = q.back_;
      size_ = q.size_;
      q.front_ = nullptr;
      q.back_ = nullptr;
      q.size_ = 0;
    }
    return *this;
  }
  const_reference front() const {
    if (empty()) throw std::out_of_range("Queue is empty");
    return front_->data_;
  }

  const_reference back() const {
    if (empty()) throw std::out_of_range("Queue is empty");
    return back_->data_;
  }
  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  void clear() {
    while (!empty()) pop();
  }
  void push(const_reference value) {
    Node* node = new Node(value);
    if (empty()) {
      front_ = back_ = node;
    } else {
      back_->next_ = node;
      back_ = node;
    }
    ++size_;
  }
  void pop() {
    if (empty()) throw std::out_of_range("Queue is empty");
    Node* temp = front_;
    front_ = front_->next_;
    delete temp;
    --size_;
    if (size_ == 0) back_ = nullptr;
  }
  void swap(Queue& other) noexcept {
    std::swap(front_, other.front_);
    std::swap(back_, other.back_);
    std::swap(size_, other.size_);
  }
};
}  // namespace s21