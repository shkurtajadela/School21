#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <typename T, size_t N>
class array {
 private:
  T elems_[N] = {};
  size_t size_ = N;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array() = default;

  array &operator=(const array &a);
  array &operator=(array &&a) noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data();

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty();
  size_type size();
  size_type max_size();

  void swap(array &other);
  void fill(const_reference value);
};

}  // namespace s21

#include "s21_array.tpp"

#endif  // S21_ARRAY_H
