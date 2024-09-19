/**
 * @brief Класс реализующий стэк на основе контейнера.
 *
 * @tparam T Тип элементов стэка.
 * @tparam Container Тип контейнера, по умолчанию s21::list<T>.
 * @author sejuanif
 *
 */

#ifndef CPP2_S21_CONTAINERS_S21_STACK_H
#define CPP2_S21_CONTAINERS_S21_STACK_H
#include "../s21_containers.h"

namespace s21 {
template <class T, class Container = s21::list<T> >
class Stack {
 public:
  /**
   * @brief Тип элементов стэка.
   */
  using value_type = T;

  /**
   * @brief Ссылка на элемент стэка.
   */
  using reference = T &;

  /**
   * @brief Константная ссылка на элемент стэка.
   */
  using const_reference = const T &;

  /**
   * @brief Тип размера стэка.
   */
  using size_type = std::size_t;

  /**
   * @brief Конструктор по умолчанию.
   */
  Stack();

  /**
   * @brief Конструктор с инициализационным списком.
   *
   * @param items Инициализационный список.
   */
  Stack(std::initializer_list<value_type> const &items);

  /**
   * @brief Копирующий конструктор.
   *
   * @param s Другой стэк.
   */
  Stack(const Stack &s);

  /**
   * @brief Перемещающий конструктор.
   *
   * @param s Другой стэк.
   */
  Stack(Stack &&s) noexcept;

  /**
   * @brief Деструктор.
   */
  ~Stack();

  /**
   * @brief Перемещающий оператор присваивания.
   *
   * @param s Другой стэк.
   * @return Ссылка на текущий стэк.
   */
  Stack &operator=(Stack &&s) noexcept;

  /**
   * @brief Возвращает константную ссылку на верхний элемент стэка.
   *
   * @return Константная ссылка на верхний элемент стэка.
   */
  const_reference top();

  /**
   * @brief Проверяет, пуст ли стэк.
   *
   * @return True, если стэк пуст, false в противном случае.
   */
  bool empty() const;

  /**
   * @brief Возвращает размер стэка.
   *
   * @return Размер стэка.
   */
  size_type size();

  /**
   * @brief Добавляет элемент в начало стэка.
   *
   * @param value Добавляемый элемент.
   */
  void push(const_reference value);

  /**
   * @brief Удаляет элемент из начала стэка.
   */
  void pop();

  /**
   * @brief Меняет местами текущий стэк и другой стэк.
   *
   * @param other Другой стэк.
   */
  void swap(Stack &other);

  /**
   * @brief Добавляет несколько элементов в начало стэка.
   *
   * @tparam Args Типы добавляемых элементов.
   * @param args Добавляемые элементы.
   */
  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  /**
   * @brief Контейнер, реализующий стэк.
   */
  Container list_;
};

template <class value_type, class Container>
Stack<value_type, Container>::Stack() : list_() {}

template <class value_type, class Container>
Stack<value_type, Container>::Stack(
    std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push(*i);
  }
}

template <class value_type, class Container>
Stack<value_type, Container>::Stack(const Stack &s) : list_(s.list_) {}

template <class value_type, class Container>
Stack<value_type, Container>::Stack(Stack &&s) noexcept
    : list_(std::move(s.list_)) {}

template <class value_type, class Container>
Stack<value_type, Container>::~Stack() = default;

template <class value_type, class Container>
Stack<value_type, Container> &Stack<value_type, Container>::operator=(
    Stack &&s) noexcept {
  if (this != &s) {
    list_ = std::move(s.list_);
  }
  return *this;
}

template <class value_type, class Container>
typename Stack<value_type, Container>::const_reference
Stack<value_type, Container>::top() {
  return list_.front();
}

template <class value_type, class Container>
bool Stack<value_type, Container>::empty() const {
  return list_.empty();
}

template <class value_type, class Container>
typename Stack<value_type, Container>::size_type
Stack<value_type, Container>::size() {
  return list_.size();
}

template <class value_type, class Container>
void Stack<value_type, Container>::push(const_reference value) {
  list_.push_front(value);
}

template <class value_type, class Container>
void Stack<value_type, Container>::pop() {
  return list_.pop_front();
}

template <class value_type, class Container>
void Stack<value_type, Container>::swap(Stack &other) {
  std::swap(list_, other.list_);
}

template <class value_type, class Container>
template <class... Args>
void Stack<value_type, Container>::insert_many_front(Args &&...args) {
  for (const auto &item : {args...}) {
    push(item);
  }
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_STACK_H_