#ifndef S21_SET_H
#define S21_SET_H

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace s21 {

template <typename Key>
class Set {
 private:
  struct Node {
    Key data;
    Node* left;
    Node* right;
    Node* parent;
    Node(const Key& key)
        : data(key), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node* root;
  size_t count;

  Node* findNode(const Key& key) const;

  void clear(Node* node);

  Node* copy(Node* node, Node* parent);

  void eraseNode(Node* node);

 public:
  Set() : root(nullptr), count(0) {}

  Set(const Set& other);

  Set(Set&& other);

  ~Set();

  Set& operator=(const Set& other);

  Set& operator=(Set&& other);

  bool insert(const Key& key);

  void erase(const Key& key);

  void clear();

  size_t size() const { return count; }

  bool empty() const { return count == 0; }

  bool operator<(const Set<Key>& other) const;
  bool operator==(const Set<Key>& other) const;
  bool operator>(const Set<Key>& other) const { return other < *this; }
  bool operator<=(const Set<Key>& other) const { return !(other < *this); }
  bool operator>=(const Set<Key>& other) const { return !(*this < other); }
  bool operator!=(const Set<Key>& other) const { return !(*this == other); }

  class iterator;

  iterator begin() const;

  iterator end() const;

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  class iterator {
   private:
    Node* node;
    const Set* set;

   public:
    iterator(Node* n, const Set* s) : node(n), set(s) {}

    const Key& operator*() { return node->data; }

    const Key* operator->() { return &(node->data); }

    iterator& operator++();

    iterator& operator--();

    bool operator==(const iterator& other) const { return node == other.node; }

    bool operator!=(const iterator& other) const { return node != other.node; }
  };

 private:
  Node* minimum(Node* node) const;

  Node* maximum(Node* node) const;

  Node* successor(Node* node) const;

  Node* predecessor(Node* node) const;

 public:
  Node* findNodePublic(const Key& key) const { return findNode(key); }
};

// Реализация поиска узла по ключу
template <typename Key>
typename Set<Key>::Node* Set<Key>::findNode(const Key& key) const {
  Node* current = root;
  while (current) {
    if (key < current->data) {
      current = current->left;
    } else if (key > current->data) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

// Реализация рекурсивного очищения дерева
template <typename Key>
void Set<Key>::clear(Node* node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

// Реализация рекурсивного копирования дерева
template <typename Key>
typename Set<Key>::Node* Set<Key>::copy(Node* node, Node* parent) {
  if (!node) return nullptr;
  Node* new_node = new Node(node->data);
  new_node->parent = parent;
  new_node->left = copy(node->left, new_node);
  new_node->right = copy(node->right, new_node);
  return new_node;
}

// Конструктор копирования
template <typename Key>
Set<Key>::Set(const Set& other)
    : root(copy(other.root, nullptr)), count(other.count) {}

// Конструктор перемещения
template <typename Key>
Set<Key>::Set(Set&& other) : root(other.root), count(other.count) {
  other.root = nullptr;
  other.count = 0;
}

// Деструктор
template <typename Key>
Set<Key>::~Set() {
  clear(root);
}

// Реализация оператора присваивания копированием
template <typename Key>
Set<Key>& Set<Key>::operator=(const Set& other) {
  if (this != &other) {
    clear(root);
    root = copy(other.root, nullptr);
    count = other.count;
  }
  return *this;
}

// Реализация оператора присваивания перемещением
template <typename Key>
Set<Key>& Set<Key>::operator=(Set&& other) {
  if (this != &other) {
    clear(root);
    root = other.root;
    count = other.count;
    other.root = nullptr;
    other.count = 0;
  }
  return *this;
}

// Реализация оператора сравнения "<" для множеств
template <typename Key>
bool Set<Key>::operator<(const Set<Key>& other) const {
  auto it1 = this->begin();
  auto it2 = other.begin();
  while (it1 != this->end() && it2 != other.end()) {
    if (*it1 < *it2) return true;
    if (*it2 < *it1) return false;
    ++it1;
    ++it2;
  }
  return (it1 == this->end() && it2 != other.end());
}

// Реализация оператора сравнения "==" для множеств
template <typename Key>
bool Set<Key>::operator==(const Set<Key>& other) const {
  if (this->size() != other.size()) return false;
  auto it1 = this->begin();
  auto it2 = other.begin();
  while (it1 != this->end()) {
    if (*it1 != *it2) return false;
    ++it1;
    ++it2;
  }
  return true;
}

// Реализация метода вставки элемента
template <typename Key>
bool Set<Key>::insert(const Key& key) {
  Node* current = root;
  Node* parent = nullptr;

  while (current) {
    parent = current;
    if (key < current->data) {
      current = current->left;
    } else if (key > current->data) {
      current = current->right;
    } else {
      return false;
    }
  }

  Node* new_node = new Node(key);
  new_node->parent = parent;

  if (!parent) {
    root = new_node;
  } else if (key < parent->data) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  count++;
  return true;
}

// Реализация метода вставки нескольких элементов
template <typename Key>
template <typename... Args>
std::vector<std::pair<typename Set<Key>::iterator, bool>> Set<Key>::insert_many(
    Args&&... args) {
  std::vector<std::pair<typename Set<Key>::iterator, bool>> results;
  auto insert_single = [this, &results](const Key& key) {
    bool inserted = this->insert(key);
    results.emplace_back(iterator(findNode(key), this), inserted);
  };
  (insert_single(std::forward<Args>(args)), ...);
  return results;
}

// Реализация метода удаления элемента по ключу
template <typename Key>
void Set<Key>::erase(const Key& key) {
  Node* node = findNode(key);
  if (!node) return;

  eraseNode(node);
  count--;
}

// Реализация удаления узла из дерева
template <typename Key>
void Set<Key>::eraseNode(Node* node) {
  if (!node->left && !node->right) {
    if (node == root) {
      root = nullptr;
    } else if (node == node->parent->left) {
      node->parent->left = nullptr;
    } else {
      node->parent->right = nullptr;
    }
    delete node;
  } else if (!node->left || !node->right) {
    Node* child = node->left ? node->left : node->right;
    if (node == root) {
      root = child;
    } else if (node == node->parent->left) {
      node->parent->left = child;
    } else {
      node->parent->right = child;
    }
    child->parent = node->parent;
    delete node;
  } else {
    Node* successor = minimum(node->right);
    std::swap(node->data, successor->data);
    eraseNode(successor);
  }
}

// Реализация метода очищения дерева
template <typename Key>
void Set<Key>::clear() {
  clear(root);
  root = nullptr;
  count = 0;
}

// Реализация метода begin, возвращающего итератор на минимальный элемент
template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() const {
  return iterator(minimum(root), this);
}

// Реализация метода end, возвращающего итератор, указывающий за последний
// элемент
template <typename Key>
typename Set<Key>::iterator Set<Key>::end() const {
  return iterator(nullptr, this);
}

// Реализация метода поиска минимального элемента в поддереве
template <typename Key>
typename Set<Key>::Node* Set<Key>::minimum(Node* node) const {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

// Реализация метода поиска максимального элемента в поддереве
template <typename Key>
typename Set<Key>::Node* Set<Key>::maximum(Node* node) const {
  while (node && node->right) {
    node = node->right;
  }
  return node;
}

// Реализация метода поиска следующего узла в дереве
template <typename Key>
typename Set<Key>::Node* Set<Key>::successor(Node* node) const {
  if (node->right) {
    return minimum(node->right);
  }
  Node* parent = node->parent;
  while (parent && node == parent->right) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

// Реализация метода поиска предыдущего узла в дереве
template <typename Key>
typename Set<Key>::Node* Set<Key>::predecessor(Node* node) const {
  if (node->left) {
    return maximum(node->left);
  }
  Node* parent = node->parent;
  while (parent && node == parent->left) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

// Реализация префиксного инкремента итератора
template <typename Key>
typename Set<Key>::iterator& Set<Key>::iterator::operator++() {
  node = set->successor(node);
  return *this;
}

// Реализация префиксного декремента итератора
template <typename Key>
typename Set<Key>::iterator& Set<Key>::iterator::operator--() {
  node = set->predecessor(node);
  return *this;
}

}  // namespace s21

#endif  // S21_SET_H
