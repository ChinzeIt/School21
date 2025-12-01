#pragma once

namespace s21 {
enum Color { RED, BLACK };

template <typename Key, typename T>
class RBTree {
 private:
  struct Node {
    Key key;  // Для map key а для set значение-ключ
    T data;   // Для map значение
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(Key key, T val)
        : key(key),
          data(val),
          color(RED),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
    Node(Key key)
        : key(key),
          data(key),
          color(RED),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

 public:
  Node* root;

 private:
  size_t tree_size;
  void fixInsert(Node* node) {
    while (node != root && node->parent->color == RED) {
      Node* parent = node->parent;
      Node* grandparent = parent->parent;
      if (parent == grandparent->left) {
        Node* uncle = grandparent->right;
        if (uncle && uncle->color == RED) {
          parent->color = BLACK;
          uncle->color = BLACK;
          grandparent->color = RED;
          node = grandparent;
        } else {
          if (node == parent->right) {
            node = parent;
            rotateLeft(node);
            parent = node->parent;
          }
          parent->color = BLACK;
          grandparent->color = RED;
          rotateRight(grandparent);
        }
      } else {
        Node* uncle = grandparent->left;
        if (uncle && uncle->color == RED) {
          parent->color = BLACK;
          uncle->color = BLACK;
          grandparent->color = RED;
          node = grandparent;
        } else {
          if (node == parent->left) {
            node = parent;
            rotateRight(node);
            parent = node->parent;
          }
          parent->color = BLACK;
          grandparent->color = RED;
          rotateLeft(grandparent);
        }
      }
    }
    root->color = BLACK;
  }
  void rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }
  void rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent)
      root = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    y->right = x;
    x->parent = y;
  }
  Node* copyTree(Node* otherNode) {
    if (otherNode == nullptr) {
      return nullptr;
    }

    Node* newNode = new Node(otherNode->key, otherNode->data);
    newNode->color = otherNode->color;

    newNode->left = copyTree(otherNode->left);
    if (newNode->left != nullptr) {
      newNode->left->parent = newNode;
    }

    newNode->right = copyTree(otherNode->right);
    if (newNode->right != nullptr) {
      newNode->right->parent = newNode;
    }

    return newNode;
  }
  void clearTree(Node* node) {
    if (node) {
      clearTree(node->left);
      clearTree(node->right);
      delete node;
    }
  }
  void transplant(Node* u, Node* v) {
    if (!u->parent)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;

    if (v) v->parent = u->parent;
  }
  Node* minimum(Node* node) {
    while (node && node->left) node = node->left;
    return node;
  }
  Node* maximum(Node* node) {
    while (node && node->right) node = node->right;
    return node;
  }
  Node* successor(Node* node) {
    if (node->right) return minimum(node->right);
    Node* p = node->parent;
    while (p && node == p->right) {
      node = p;
      p = p->parent;
    }
    return p;
  }
  Node* predecessor(Node* node) {
    if (node->left) return maximum(node->left);
    Node* p = node->parent;
    while (p && node == p->left) {
      node = p;
      p = p->parent;
    }
    return p;
  }
  const Node* successor(const Node* node) const {
    if (!node) return nullptr;
    if (node->right) {
      node = node->right;
      while (node->left) node = node->left;
      return node;
    }
    const Node* parent = node->parent;
    while (parent && node == parent->right)
      node = parent, parent = parent->parent;
    return parent;
  }

  const Node* predecessor(const Node* node) const {
    if (!node) return nullptr;
    if (node->left) {
      node = node->left;
      while (node->right) node = node->right;
      return node;
    }
    const Node* parent = node->parent;
    while (parent && node == parent->left)
      node = parent, parent = parent->parent;
    return parent;
  }
  void fixDelete(Node* x, Node* parent) {
    while (x != root && (!x || x->color == BLACK)) {
      if (x == parent->left) {
        Node* sibling = parent->right;
        if (sibling && sibling->color == RED) {
          sibling->color = BLACK;
          parent->color = RED;
          rotateLeft(parent);
          sibling = parent->right;
        }

        if ((!sibling->left || sibling->left->color == BLACK) &&
            (!sibling->right || sibling->right->color == BLACK)) {
          sibling->color = RED;
          x = parent;
          parent = x->parent;
        } else {
          if (!sibling->right || sibling->right->color == BLACK) {
            if (sibling->left) sibling->left->color = BLACK;
            sibling->color = RED;
            rotateRight(sibling);
            sibling = parent->right;
          }
          sibling->color = parent->color;
          parent->color = BLACK;
          if (sibling->right) sibling->right->color = BLACK;
          rotateLeft(parent);
          x = root;
        }
      } else {
        Node* sibling = parent->left;
        if (sibling && sibling->color == RED) {
          sibling->color = BLACK;
          parent->color = RED;
          rotateRight(parent);
          sibling = parent->left;
        }

        if ((!sibling->left || sibling->left->color == BLACK) &&
            (!sibling->right || sibling->right->color == BLACK)) {
          sibling->color = RED;
          x = parent;
          parent = x->parent;
        } else {
          if (!sibling->left || sibling->left->color == BLACK) {
            if (sibling->right) sibling->right->color = BLACK;
            sibling->color = RED;
            rotateLeft(sibling);
            sibling = parent->left;
          }
          sibling->color = parent->color;
          parent->color = BLACK;
          if (sibling->left) sibling->left->color = BLACK;
          rotateRight(parent);
          x = root;
        }
      }
    }

    if (x) x->color = BLACK;
  }
  Node* removeBinary(Node* node, T data) {
    if (!node) return nullptr;

    if (node->data == data) {
      if (!node->left && !node->right) {
        delete node;
        return nullptr;
      }
      if (!node->left) {
        Node* temp = node->right;
        delete node;
        return temp;
      }
      if (!node->right) {
        Node* temp = node->left;
        delete node;
        return temp;
      }

      Node* min = minimum(node->right);
      node->data = min->data;
      node->right = removeBinary(node->right, min->data);
    } else {
      node->left = removeBinary(node->left, data);
      node->right = removeBinary(node->right, data);
    }
    return node;
  }
  bool insertNode(Node* newNode, bool use_rbtree, bool allow_duplicates) {
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
      y = x;
      if (newNode->data < x->data) {
        x = x->left;
      } else if (x->data < newNode->data) {
        x = x->right;
      } else {
        if (!allow_duplicates) {
          delete newNode;
          last_inserted_ = nullptr;
          return false;
        } else {
          x = x->right;
        }
      }
    }

    if (use_rbtree) newNode->parent = y;
    if (y == nullptr) {
      root = newNode;
    } else if (newNode->data < y->data) {
      y->left = newNode;
    } else {
      y->right = newNode;
    }

    if (use_rbtree) fixInsert(newNode);
    tree_size++;
    last_inserted_ = newNode;
    return true;
  }

 public:
  Node* last_inserted_ = nullptr;
  RBTree() : root(nullptr), tree_size(0) {}
  ~RBTree() {
    clearTree(root);
    root = nullptr;
  }

  RBTree(const RBTree& other) {
    root = copyTree(other.root);
    tree_size = other.tree_size;
  }

  RBTree& operator=(const RBTree& other) {
    if (this != &other) {
      clear();
      root = copyTree(other.root);
      tree_size = other.tree_size;
    }
    return *this;
  }

  RBTree(RBTree&& other) noexcept
      : root(other.root), tree_size(other.tree_size) {
    other.root = nullptr;
    other.tree_size = 0;
  }

  RBTree& operator=(RBTree&& other) noexcept {
    if (this != &other) {
      clear();
      root = other.root;
      tree_size = other.tree_size;
      other.root = nullptr;
      other.tree_size = 0;
    }
    return *this;
  }

  void clear() {
    clearTree(root);
    root = nullptr;
    tree_size = 0;
  }

  size_t size() const { return tree_size; }

  size_t max_size() const {
    return std::allocator_traits<std::allocator<Node>>::max_size(
        std::allocator<Node>());
  }

  class TreeIterator {
   public:
    TreeIterator() : current(nullptr), tree(nullptr) {}
    TreeIterator(Node* node, RBTree* tree) : current(node), tree(tree) {}
    TreeIterator(const TreeIterator& other)
        : current(other.current), tree(other.tree) {}

    T& operator*() const {
      if (!current) throw std::runtime_error("Null iterator");
      return current->data;
    }

    T* operator->() { return &operator*(); }

    Key& getKey() const {
      if (!current) throw std::runtime_error("Invalid iterator");
      return current->key;
    }

    T& getData() const {
      if (!current) throw std::runtime_error("Invalid iterator");
      return current->data;
    }

    TreeIterator& operator++() {
      if (current) current = tree->successor(current);
      return *this;
    }

    TreeIterator operator++(int) {
      TreeIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    TreeIterator& operator--() {
      if (current) current = tree->predecessor(current);
      return *this;
    }

    TreeIterator operator--(int) {
      TreeIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const TreeIterator& other) const {
      return current == other.current;
    }
    bool operator!=(const TreeIterator& other) const {
      return current != other.current;
    }

    TreeIterator& operator=(const TreeIterator& other) {
      if (this != &other) {
        current = other.current;
        tree = other.tree;
      }
      return *this;
    }

   private:
    Node* current;
    RBTree* tree;
    friend class RBTree;
  };
  class ConstTreeIterator {
   public:
    ConstTreeIterator() : current(nullptr), tree(nullptr) {}
    ConstTreeIterator(const Node* node, const RBTree* tree)
        : current(node), tree(tree) {}
    ConstTreeIterator(const ConstTreeIterator& other)
        : current(other.current), tree(other.tree) {}

    const T& operator*() const {
      if (!current) throw std::runtime_error("Null iterator");
      return current->data;
    }

    const T* operator->() const { return &operator*(); }

    const Key& getKey() const {
      if (!current) throw std::runtime_error("Invalid iterator");
      return current->key;
    }

    const T& getData() const {
      if (!current) throw std::runtime_error("Invalid iterator");
      return current->data;
    }

    ConstTreeIterator& operator++() {
      if (current) current = tree->successor(current);
      return *this;
    }

    ConstTreeIterator operator++(int) {
      ConstTreeIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ConstTreeIterator& operator--() {
      if (current) current = tree->predecessor(current);
      return *this;
    }

    ConstTreeIterator operator--(int) {
      ConstTreeIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const ConstTreeIterator& other) const {
      return current == other.current;
    }
    bool operator!=(const ConstTreeIterator& other) const {
      return current != other.current;
    }

    ConstTreeIterator& operator=(const ConstTreeIterator& other) {
      if (this != &other) {
        current = other.current;
        tree = other.tree;
      }
      return *this;
    }

   private:
    const Node* current;
    const RBTree* tree;
    friend class RBTree;
  };
  bool insert(const Key& key, const T& data, bool use_rbtree,
              bool allow_duplicates) {
    Node* newNode = new Node(key, data);
    return insertNode(newNode, use_rbtree, allow_duplicates);
  }
  bool insert(const Key& key, bool use_rbtree, bool allow_duplicates) {
    Node* newNode = new Node(key);
    newNode->color = RED;
    return insertNode(newNode, use_rbtree, allow_duplicates);
  }
  void remove(const Key& key, bool use_rbtree) {
    Node* node = findNode(root, key);
    if (!use_rbtree) {
      root = removeBinary(root, node->data);
      tree_size--;
      return;
    }
    if (!node) return;

    Node* y = node;
    Node* x = nullptr;
    Node* parent = nullptr;
    Color originalColor = y->color;

    if (!node->left) {
      x = node->right;
      parent = node->parent;
      transplant(node, node->right);
    } else if (!node->right) {
      x = node->left;
      parent = node->parent;
      transplant(node, node->left);
    } else {
      y = minimum(node->right);
      originalColor = y->color;
      x = y->right;

      if (y->parent == node) {
        parent = y;
        if (x) x->parent = y;
      } else {
        transplant(y, y->right);
        y->right = node->right;
        if (y->right) y->right->parent = y;
        parent = y->parent;
      }

      transplant(node, y);
      y->left = node->left;
      if (y->left) y->left->parent = y;
      y->color = node->color;
    }

    delete node;
    tree_size--;

    if (originalColor == BLACK) fixDelete(x, parent);
  }
  TreeIterator begin() {
    if (!root) return end();
    return TreeIterator(minimum(root), this);
  }
  TreeIterator end() { return TreeIterator(nullptr, this); }
  ConstTreeIterator begin() const {
    if (!root) return end();
    return ConstTreeIterator(minimum(root), this);
  }
  ConstTreeIterator end() const { return ConstTreeIterator(nullptr, this); }
  Node* findNode(Node* node, const Key& key) const {
    if (!node) return nullptr;

    if (node->key == key) return node;

    Node* leftResult = findNode(node->left, key);
    if (leftResult) return leftResult;

    return findNode(node->right, key);
  }
  const Node* findNode(const Node* node, const Key& key) const {
    if (!node) return nullptr;

    if (node->key == key) return node;

    Node* leftResult = findNode(node->left, key);
    if (leftResult) return leftResult;

    return findNode(node->right, key);
  }
  void swap(RBTree& other) noexcept {
    std::swap(root, other.root);
    std::swap(tree_size, other.tree_size);
  }
  TreeIterator lower_bound(const T& key) {
    Node* current = root;
    Node* result = nullptr;

    while (current) {
      if (!(current->data < key)) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return TreeIterator(result, this);
  }
  ConstTreeIterator lower_bound(const T& key) const {
    Node* current = root;
    Node* result = nullptr;

    while (current) {
      if (!(current->data < key)) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return ConstTreeIterator(result, this);
  }
  TreeIterator upper_bound(const T& key) {
    Node* current = root;
    Node* result = nullptr;

    while (current) {
      if (key < current->data) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return TreeIterator(result, this);
  }
  ConstTreeIterator upper_bound(const T& key) const {
    Node* current = root;
    Node* result = nullptr;

    while (current) {
      if (key < current->data) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return ConstTreeIterator(result, this);
  }
};
}  // namespace s21