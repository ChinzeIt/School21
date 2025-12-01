#pragma once

namespace s21 {

template <typename T>
class List {
 private:
  struct Node {
    T data_;
    Node* prev_ = nullptr;
    Node* next_ = nullptr;

    Node(const T& value) : data_(value), prev_(nullptr), next_(nullptr) {}
  };
  Node* head_;
  Node* tail_;
  size_t size_;

  template <typename Iter>

  class ListIterator {
   public:
    ListIterator() noexcept : current(nullptr) {}
    ListIterator(Iter ptr) noexcept : current(ptr) {}
    ~ListIterator() = default;

    auto& operator*() { return current->data_; }

    ListIterator& operator++() {
      current = current->next_;
      return *this;
    }

    ListIterator& operator--() {
      current = current->prev_;
      return *this;
    }

    bool operator==(const ListIterator& other) const noexcept {
      return current == other.current;
    }

    bool operator!=(const ListIterator& other) const noexcept {
      return current != other.current;
    }

    Iter current;
  };

  template <typename Iter>

  class ConstListIterator {
   public:
    ConstListIterator() noexcept : current(nullptr) {}
    ConstListIterator(Iter ptr) noexcept : current(ptr) {}
    ~ConstListIterator() = default;

    const auto& operator*() const { return current->data_; }

    ConstListIterator& operator++() {
      current = current->next_;
      return *this;
    }

    ConstListIterator& operator--() {
      current = current->prev_;
      return *this;
    }

    bool operator==(const ConstListIterator& other) const noexcept {
      return current == other.current;
    }

    bool operator!=(const ConstListIterator& other) const noexcept {
      return current != other.current;
    }

    Iter current;
  };

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator<Node*>;
  using const_iterator = ConstListIterator<Node*>;
  using size_type = std::size_t;

  List() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}
  List(size_type n) noexcept : head_(nullptr), tail_(nullptr), size_(0) {
    while (n--) push_back(T{});
  }
  ~List() noexcept {
    while (head_) {
      Node* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
  }
  List(std::initializer_list<value_type> const& items)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto& item : items) push_back(item);
  }
  List(const List& l) : head_(nullptr), tail_(nullptr), size_(0) {
    if (l.size_ == 0) {
      throw std::out_of_range("Not have elements for copy");
    } else {
      Node* current = l.head_;
      while (current) {
        push_back(current->data_);
        current = current->next_;
      }
    }
  }
  List(List&& l) noexcept : head_(l.head_), tail_(l.tail_), size_(l.size_) {
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }
  List& operator=(List&& l) {
    if (this != &l) {
      clear();
      head_ = l.head_;
      tail_ = l.tail_;
      size_ = l.size_;

      l.head_ = nullptr;
      l.tail_ = nullptr;
      l.size_ = 0;
    }

    return *this;
  }
  const_reference front() const {
    if (!head_) throw std::out_of_range("No front");
    return head_->data_;
  }
  const_reference back() const {
    if (!tail_) throw std::out_of_range("No back");
    return tail_->data_;
  }
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(nullptr); }
  const_iterator begin() const { return const_iterator(head_); }
  const_iterator end() const { return const_iterator(nullptr); }
  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }
  iterator insert(iterator pos, const_reference value) noexcept {
    Node* current = pos.current;
    Node* newNode = new Node(value);

    if (!current) {
      newNode->prev_ = tail_;
      if (tail_) tail_->next_ = newNode;
      tail_ = newNode;
      if (!head_) head_ = newNode;
    } else {
      newNode->next_ = current;
      newNode->prev_ = current->prev_;
      if (current->prev_)
        current->prev_->next_ = newNode;
      else
        head_ = newNode;
      current->prev_ = newNode;
    }
    ++size_;
    return iterator(newNode);
  }
  void erase(iterator pos) {
    Node* current = pos.current;
    if (pos == end() || !current) {
      throw std::out_of_range("Problem to erase");
    } else {
      if (current->prev_)
        current->prev_->next_ = current->next_;
      else
        head_ = current->next_;

      if (current->next_)
        current->next_->prev_ = current->prev_;
      else
        tail_ = current->prev_;

      delete current;
      --size_;

      if (size_ == 0) {
        head_ = nullptr;
        tail_ = nullptr;
      }
    }
  }
  void pop_back() {
    if (!tail_) throw std::out_of_range("Problem to pop back");
    erase(iterator(tail_));
  }
  void pop_front() {
    if (!head_) throw std::out_of_range("Problem to pop front");
    erase(iterator(head_));
  }
  void push_front(const_reference value) noexcept {
    Node* new_node = new Node(value);
    new_node->next_ = head_;
    head_ = new_node;
    if (size_ == 0) {
      tail_ = new_node;
    }
    ++size_;
  }
  void swap(List& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }
  void push_back(const_reference value) noexcept {
    Node* newNode = new Node(value);

    if (!head_) {
      head_ = tail_ = newNode;
    } else {
      tail_->next_ = newNode;
      newNode->prev_ = tail_;
      tail_ = newNode;
    }

    ++size_;
  }
  void clear() noexcept {
    while (head_) {
      Node* temp = head_;
      head_ = head_->next_;
      delete temp;
    }

    tail_ = nullptr;
    size_ = 0;
  }
  void merge(List& other) {
    if (this == &other || !other.head_) {
      throw std::out_of_range("Problem to merge");
    } else {
      Node* a = head_;
      Node* b = other.head_;
      List result;
      while (a && b) {
        if (a->data_ < b->data_) {
          result.push_back(a->data_);
          a = a->next_;
        } else {
          result.push_back(b->data_);
          b = b->next_;
        }
      }
      while (a) {
        result.push_back(a->data_);
        a = a->next_;
      }
      while (b) {
        result.push_back(b->data_);
        b = b->next_;
      }
      *this = std::move(result);
      other.clear();
    }
  }
  void splice(const_iterator pos, List& other) {
    if (other.empty()) {
      throw std::out_of_range("Problem to splice");
    } else {
      Node* insertPos = pos.current;
      Node* first = other.head_;
      Node* last = other.tail_;

      if (!insertPos) {
        if (tail_) {
          tail_->next_ = first;
          first->prev_ = tail_;
          tail_ = last;
        } else {
          head_ = first;
          tail_ = last;
        }
      } else {
        Node* before = insertPos->prev_;
        if (before)
          before->next_ = first;
        else
          head_ = first;

        first->prev_ = before;
        last->next_ = insertPos;
        insertPos->prev_ = last;
      }
    }

    size_ += other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
  void reverse() noexcept {
    Node* current = head_;
    Node* temp = nullptr;
    while (current) {
      temp = current->prev_;
      current->prev_ = current->next_;
      current->next_ = temp;
      current = current->prev_;
    }
    std::swap(head_, tail_);
  }
  void unique() {
    if (!head_) {
      throw std::out_of_range("Problem to unique");
    } else {
      Node* current = head_;
      while (current->next_) {
        if (current->data_ == current->next_->data_) {
          Node* duplicate = current->next_;
          current->next_ = duplicate->next_;
          if (duplicate->next_)
            duplicate->next_->prev_ = current;
          else
            tail_ = current;
          delete duplicate;
          --size_;
        } else {
          current = current->next_;
        }
      }
    }
  }
  void sort() {
    if (!head_ || !head_->next_) {
      throw std::out_of_range("Problem to sort");
    } else {
      for (bool swapped = true; swapped;) {
        swapped = false;
        Node* current = head_;
        while (current->next_) {
          if (current->data_ > current->next_->data_) {
            std::swap(current->data_, current->next_->data_);
            swapped = true;
          }
          current = current->next_;
        }
      }
    }
  }
};
}  // namespace s21