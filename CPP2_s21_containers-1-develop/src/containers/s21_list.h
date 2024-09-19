/**
 * @file s21_list.h
 * @brief Реализация двусвязного списка на шаблоне C++.
 *
 * @author sejuanif
 */

#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

/**
 * @brief Класс двусвязного списка.
 *
 * @tparam T Тип хранимых значений.
 */
template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T&;
  using const_reference = T const&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

 private:
  struct Node;

 public:
  list() : head_(new Node()), tail_(new Node()) {
    head_->next_ = tail_;
    head_->prev_ = tail_;
    tail_->next_ = head_;
    tail_->prev_ = head_;
  }

  list(size_type n) : list() {
    if (n >= max_size() - 1) {
      throw std::invalid_argument(
          "The size of the list exceeds the memory limit or"
          " the number of elements is smaller than zero.");
    }
    for (size_type i = 0; i < n; ++i) {
      const_reference v{};
      push_front(v);
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (auto const& i : items) push_back(i);
  }

  list(list const& l) : list() {
    Node* element = l.head_->next_;
    while (element != l.tail_) {
      push_back(element->data_);
      element = element->next_;
    }
  }

  list& operator=(list const& l) {
    if (this != &l) {
      clear();
      Node* element = l.head_->next_;
      while (element != l.tail_) {
        push_back(element->data_);
        element = element->next_;
      }
    }
    return *this;
  }

  list(list&& l) noexcept : list() { swap(l); }

  list& operator=(list&& l) noexcept {
    if (this != &l) swap(l);
    return *this;
  }

  ~list() {
    clear();
    delete head_;
    delete tail_;
  }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / (sizeof(Node));
  }

  class ListIterator final {
   private:
    friend list;
    Node* ptr_;
    ListIterator(Node* ptr) noexcept : ptr_(ptr) {};

   public:
    using iterator_category =
        std::bidirectional_iterator_tag;  // Категория итератора
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    ListIterator() : ptr_(nullptr) {};
    ListIterator(iterator const& other) = default;
    ListIterator(iterator&& other) = default;
    ~ListIterator() = default;
    iterator& operator=(iterator const& other) = default;
    iterator& operator=(iterator&& other) = default;

    value_type& operator*() const { return ptr_->data_; }

    iterator& operator++() {
      ptr_ = ptr_->next_;
      return *this;
    }

    iterator operator++(int) {
      iterator old = *this;
      ptr_ = ptr_->next_;
      return old;
    }

    iterator& operator--() {
      ptr_ = ptr_->prev_;
      return *this;
    }

    iterator operator--(int) {
      iterator old = *this;
      ptr_ = ptr_->prev_;
      return old;
    }

    bool operator==(iterator const& other) const {
      return (ptr_ == other.ptr_) ? true : false;
    }

    bool operator!=(iterator const& other) const {
      return (ptr_ != other.ptr_) ? true : false;
    }
  };

  class ListConstIterator final {
   private:
    friend list;
    iterator c_ptr_;

   public:
    ListConstIterator() : c_ptr_() {};
    ListConstIterator(const_iterator const& other) = default;
    ListConstIterator(iterator const& other) { c_ptr_ = other; }
    ListConstIterator(const_iterator&& other) = default;
    ~ListConstIterator() = default;
    const_iterator& operator=(const_iterator const& other) = default;
    const_iterator& operator=(iterator const& other) {
      c_ptr_ = other;
      return *this;
    }
    const_iterator& operator=(const_iterator&& other) = default;
    value_type const& operator*() const { return *c_ptr_; }

    const_iterator& operator++() {
      ++c_ptr_;
      return *this;
    }

    const_iterator operator++(int) { return c_ptr_++; }

    const_iterator& operator--() {
      --c_ptr_;
      return *this;
    }

    const_iterator operator--(int) { return c_ptr_--; }

    bool operator==(const_iterator const& other) const {
      return (c_ptr_ == other.c_ptr_) ? true : false;
    }

    bool operator!=(const_iterator const& other) const {
      return (c_ptr_ != other.c_ptr_) ? true : false;
    }

    bool operator==(iterator const& other) const {
      return (c_ptr_ == other) ? true : false;
    }

    bool operator!=(iterator const& other) const {
      return (c_ptr_ != other) ? true : false;
    }
  };

  const_reference front() const { return head_->next_->data_; }
  const_reference back() const { return tail_->prev_->data_; }
  bool empty() const { return list_size_ ? false : true; };
  size_type size() const { return list_size_; }
  iterator begin() { return iterator(head_->next_); }
  iterator end() { return iterator(tail_); }
  const_iterator begin() const { return const_iterator(head_->next_); }
  const_iterator end() const { return const_iterator(tail_); }
  void push_back(const_reference value) { insert(end(), value); }
  void push_front(const_reference value) { insert(begin(), value); }
  void pop_back() { erase(--end()); }
  void pop_front() { erase(begin()); }

  void swap(list& other) noexcept {
    Node* temp_head = other.head_;
    Node* temp_tail = other.tail_;
    size_type temp_size = other.list_size_;

    other.head_ = head_;
    other.tail_ = tail_;
    other.list_size_ = list_size_;

    head_ = temp_head;
    tail_ = temp_tail;
    list_size_ = temp_size;
  }

  /**
   * @brief Вставляет элемент в указанную позицию.
   *
   * @param pos Итератор, указывающий на позицию вставки.
   * @param value Значение для вставки.
   * @return Итератор, указывающий на вставленный элемент.
   */
  iterator insert(iterator pos, const_reference value) {
    Node* new_elem = new Node();
    Node* old_elem = pos.ptr_;
    new_elem->data_ = value;
    new_elem->next_ = old_elem;
    new_elem->prev_ = old_elem->prev_;
    new_elem->prev_->next_ = new_elem;
    old_elem->prev_ = new_elem;
    ++list_size_;
    iterator pos_new(new_elem);
    return pos_new;
  }

  /**
   * @brief Обращает порядок следования элементов в списке.
   */
  void reverse() {
    if (size() > 1) {
      Node* element = tail_->prev_;
      while (element != head_) {
        Node* temp = element->prev_;
        element->prev_ = element->next_;
        element->next_ = temp;
        element = element->next_;
      }
      Node* temp = head_->next_;
      head_->next_ = tail_->prev_;
      tail_->prev_ = temp;
      head_->prev_ = tail_;
      tail_->next_ = head_;
      head_->next_->prev_ = head_;
      tail_->prev_->next_ = tail_;
    }
  }
  /**
   * @brief Удаляет указанный элемент из списка.
   *
   * @param pos Итератор, указывающий на удаляемый элемент.
   * @return Итератор, указывающий на следующий элемент после удаления.
   */
  void unique() {
    if (size() > 1) {
      Node* first = head_->next_;
      Node* second = first;
      while (second != tail_) {
        second = first->next_;
        while (first->data_ == second->data_ && second != tail_) {
          erase(second);
          second = first->next_;
        }
        first = first->next_;
      }
    }
  }

  /**
   * @brief Вставляет все элементы из другого списка в указанную позицию.
   *
   * @param pos Итератор, указывающий на позицию вставки.
   * @param other Другой список.
   */
  void splice(const_iterator pos, list& other) {
    if (!other.empty() && begin() != other.begin()) {
      Node* temp_second = other.head_;
      Node* temp_first = pos.c_ptr_.ptr_;
      while (other.list_size_) {
        temp_second = other.head_->next_;
        other.head_->next_->next_->prev_ = other.head_;
        other.head_->next_ = other.head_->next_->next_;
        temp_second->next_ = temp_first;
        temp_second->prev_ = temp_first->prev_;
        temp_second->prev_->next_ = temp_second;
        temp_first->prev_ = temp_second;
        --other.list_size_;
        ++list_size_;
      }
    }
  }

  /**
   * @brief Сортирует элементы в списке в порядке возрастания.
   */
  void sort() {
    if (size() > 1) {
      Node* element_fisrt = head_->next_;
      Node* element_second = head_->next_->next_;
      while (element_fisrt != tail_->prev_) {
        Node* dummy = element_fisrt;
        Node* min = element_fisrt;
        while (element_second != tail_) {
          if (dummy->data_ > element_second->data_) {
            min = element_second;
          }
          element_second = element_second->next_;
        }
        if (dummy != min) {
          if (dummy->next_ == min) {
            min->prev_ = min->prev_->prev_;
            dummy->next_ = dummy->next_->next_;
            dummy->prev_ = min;
            min->next_ = dummy;
          } else {
            Node* temp_next = dummy->next_;
            dummy->next_ = min->next_;
            min->next_ = temp_next;

            Node* temp_prev = dummy->prev_;
            dummy->prev_ = min->prev_;
            min->prev_ = temp_prev;

            min->next_->prev_ = min;
            dummy->prev_->next_ = dummy;
          }
          min->prev_->next_ = min;
          dummy->next_->prev_ = dummy;
          element_fisrt = min;
        } else {
          element_fisrt = element_fisrt->next_;
        }
        element_second = element_fisrt->next_;
      }
    }
  }

  /**
   * @brief Объединяет текущий список с другим списком.
   *
   * @param other Другой список.
   */
  void merge(list& other) {
    if (this != &other && !other.empty()) {
      if (empty()) {
        *this = std::move(other);
      } else {
        Node* temp_first = head_->next_;
        while (other.head_->next_ != other.tail_) {
          if ((temp_first->data_ <= other.head_->next_->data_ ||
               other.head_->next_ == other.tail_) &&
              temp_first != tail_) {
            temp_first = temp_first->next_;
          } else if (temp_first->data_ > other.head_->next_->data_ ||
                     temp_first == tail_) {
            Node* temp_second = other.head_->next_;
            other.head_->next_->next_->prev_ = other.head_;
            other.head_->next_ = other.head_->next_->next_;
            temp_second->next_ = temp_first;
            temp_second->prev_ = temp_first->prev_;
            temp_second->prev_->next_ = temp_second;
            temp_first->prev_ = temp_second;
            --other.list_size_;
            ++list_size_;
          }
        }
      }
    }
  }

  /**
   * @brief Удаляет указанный элемент из списка.
   *
   * @param pos Итератор, указывающий на удаляемый элемент.
   */

  void erase(iterator pos) {
    if (pos == --begin() || pos == end() || size() == 0) {
      throw std::out_of_range(
          "Invalid pointer: cannot be erased or dereferenced.");
    }
    Node* element = pos.ptr_;
    element->next_->prev_ = element->prev_;
    element->prev_->next_ = element->next_;
    delete element;
    pos.ptr_ = nullptr;
    --list_size_;
  }

  /**
   * @brief Удаляет все элементы из списка.
   */
  void clear() {
    Node* element = head_->next_;
    while (element != tail_) {
      pop_front();
      element = head_->next_;
    }
  }

  /**
   * @brief Вставляет несколько элементов в указанную позицию.
   *
   * @tparam Args Типы значений для вставки.
   * @param pos Итератор, указывающий на позицию вставки.
   * @param args Значения для вставки.
   * @return Итератор, указывающий на последний вставленный элемент.
   */
  template <typename... Args>
  typename list<T>::iterator insert_many(const_iterator pos, Args&&... args) {
    std::initializer_list<T> elements = {std::forward<Args>(args)...};
    auto iter = pos.c_ptr_;

    for (auto it = std::rbegin(elements); it != std::rend(elements); ++it) {
      iter = insert(iterator(iter), *it);
    }
    return iterator(iter);
  }

  /**
   * @brief Вставляет несколько элементов в конец списка.
   *
   * @tparam Args Типы значений для вставки.
   * @param args Значения для вставки.
   */
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    insert_many(end(), std::forward<Args>(args)...);
  }

  /**
   * @brief Вставляет несколько элементов в начало списка.
   *
   * @tparam Args Типы значений для вставки.
   * @param args Значения для вставки.
   */
  template <typename... Args>
  void insert_many_front(Args&&... args) {
    insert_many(begin(), std::forward<Args>(args)...);
  }

  //
 private:
  struct Node {
    value_type data_;
    Node* prev_ = nullptr;
    Node* next_ = nullptr;
  };

  Node* head_;
  Node* tail_;
  size_type list_size_ = 0;
};
}  // namespace s21

#endif  // SRC_S21_LIST_H_