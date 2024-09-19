#ifndef S21_MAP_H
#define S21_MAP_H

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace s21 {

template <typename Key, typename T>
class Map {
 private:
  struct Node {
    std::pair<const Key, T> data;
    Node *left;
    Node *right;
    Node *parent;
    Node(const Key &key, const T &value)
        : data(key, value), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node *root;
  size_t count;

  Node *findNode(const Key &key) const;

  void clear(Node *node);

  Node *copy(Node *node, Node *parent);

  void eraseNode(Node *node);

 public:
  Map() : root(nullptr), count(0) {}

  Map(const Map &other);

  Map(Map &&other);

  ~Map();

  Map &operator=(const Map &other);

  Map &operator=(Map &&other);

  T &operator[](const Key &key);

  T &at(const Key &key);

  const T &at(const Key &key) const;

  bool insert(const Key &key, const T &value);

  void erase(const Key &key);

  void clear();

  size_t size() const { return count; }

  bool empty() const { return count == 0; }

  class iterator;

  iterator begin();

  iterator end();

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  class iterator {
   private:
    Node *node;
    Map *map;

   public:
    iterator(Node *n, Map *m) : node(n), map(m) {}

    std::pair<const Key, T> &operator*() { return node->data; }

    std::pair<const Key, T> *operator->() { return &(node->data); }

    iterator &operator++();

    iterator &operator--();

    bool operator==(const iterator &other) const { return node == other.node; }

    bool operator!=(const iterator &other) const { return node != other.node; }
  };

 private:
  Node *minimum(Node *node) const;
  Node *maximum(Node *node) const;
  Node *successor(Node *node) const;
  Node *predecessor(Node *node) const;

 public:
  Node *findNodePublic(const Key &key) const { return findNode(key); }
};

// Реализация поиска узла по ключу
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::findNode(const Key &key) const {
  Node *current = root;
  while (current) {
    if (key < current->data.first) {
      current = current->left;
    } else if (key > current->data.first) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

// Реализация рекурсивного очищения дерева
template <typename Key, typename T>
void Map<Key, T>::clear(Node *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

// Реализация рекурсивного копирования дерева
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::copy(Node *node, Node *parent) {
  if (!node) return nullptr;
  Node *new_node = new Node(node->data.first, node->data.second);
  new_node->parent = parent;
  new_node->left = copy(node->left, new_node);
  new_node->right = copy(node->right, new_node);
  return new_node;
}

// Конструктор копирования
template <typename Key, typename T>
Map<Key, T>::Map(const Map &other)
    : root(copy(other.root, nullptr)), count(other.count) {}

// Конструктор перемещения
template <typename Key, typename T>
Map<Key, T>::Map(Map &&other) : root(other.root), count(other.count) {
  other.root = nullptr;
  other.count = 0;
}

// Деструктор
template <typename Key, typename T>
Map<Key, T>::~Map() {
  clear(root);
}

// Реализация оператора присваивания копированием
template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(const Map &other) {
  if (this != &other) {
    clear(root);
    root = copy(other.root, nullptr);
    count = other.count;
  }
  return *this;
}

// Реализация оператора присваивания перемещением
template <typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(Map &&other) {
  if (this != &other) {
    clear(root);
    root = other.root;
    count = other.count;
    other.root = nullptr;
    other.count = 0;
  }
  return *this;
}

// Реализация оператора доступа по ключу
template <typename Key, typename T>
T &Map<Key, T>::operator[](const Key &key) {
  Node *node = findNode(key);
  if (!node) {
    insert(key, T());
    node = findNode(key);
  }
  return node->data.second;
}

// Реализация метода at с неконстантной ссылкой
template <typename Key, typename T>
T &Map<Key, T>::at(const Key &key) {
  Node *node = findNode(key);
  if (!node) throw std::out_of_range("Key not found");
  return node->data.second;
}

// Реализация метода at с константной ссылкой
template <typename Key, typename T>
const T &Map<Key, T>::at(const Key &key) const {
  Node *node = findNode(key);
  if (!node) throw std::out_of_range("Key not found");
  return node->data.second;
}

// Реализация метода вставки элемента
template <typename Key, typename T>
bool Map<Key, T>::insert(const Key &key, const T &value) {
  Node *current = root;
  Node *parent = nullptr;

  while (current) {
    parent = current;
    if (key < current->data.first) {
      current = current->left;
    } else if (key > current->data.first) {
      current = current->right;
    } else {
      return false;
    }
  }

  Node *new_node = new Node(key, value);
  new_node->parent = parent;

  if (!parent) {
    root = new_node;
  } else if (key < parent->data.first) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  count++;
  return true;
}

// Реализация метода вставки нескольких элементов
template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename Map<Key, T>::iterator, bool>>
Map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<typename Map<Key, T>::iterator, bool>> results;
  auto insert_single = [this,
                        &results](const std::pair<const Key, T> &key_value) {
    bool inserted = this->insert(key_value.first, key_value.second);
    results.emplace_back(iterator(findNode(key_value.first), this), inserted);
  };
  (insert_single(std::forward<Args>(args)), ...);
  return results;
}

// Реализация метода удаления элемента по ключу
template <typename Key, typename T>
void Map<Key, T>::erase(const Key &key) {
  Node *node = findNode(key);
  if (!node) return;

  eraseNode(node);
  count--;
}

// Реализация удаления узла из дерева
template <typename Key, typename T>
void Map<Key, T>::eraseNode(Node *node) {
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
    Node *child = node->left ? node->left : node->right;
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
    Node *successor = minimum(node->right);
    const_cast<Key &>(node->data.first) = successor->data.first;
    node->data.second = successor->data.second;
    eraseNode(successor);
  }
}

// Реализация метода очищения дерева
template <typename Key, typename T>
void Map<Key, T>::clear() {
  clear(root);
  root = nullptr;
  count = 0;
}

// Реализация метода begin, возвращающего итератор на минимальный элемент
template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  return iterator(minimum(root), this);
}

// Реализация метода end, возвращающего итератор, указывающий за последний
// элемент
template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return iterator(nullptr, this);
}

// Реализация метода поиска минимального элемента в поддереве
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::minimum(Node *node) const {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

// Реализация метода поиска максимального элемента в поддереве
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::maximum(Node *node) const {
  while (node && node->right) {
    node = node->right;
  }
  return node;
}

// Реализация метода поиска следующего узла в дереве
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::successor(Node *node) const {
  if (node->right) {
    return minimum(node->right);
  }
  Node *parent = node->parent;
  while (parent && node == parent->right) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

// Реализация метода поиска предыдущего узла в дереве
template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::predecessor(Node *node) const {
  if (node->left) {
    return maximum(node->left);
  }
  Node *parent = node->parent;
  while (parent && node == parent->left) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

// Реализация префиксного инкремента итератора
template <typename Key, typename T>
typename Map<Key, T>::iterator &Map<Key, T>::iterator::operator++() {
  node = map->successor(node);
  return *this;
}

// Реализация префиксного декремента итератора
template <typename Key, typename T>
typename Map<Key, T>::iterator &Map<Key, T>::iterator::operator--() {
  node = map->predecessor(node);
  return *this;
}

}  // namespace s21

#endif  // S21_MAP_H
