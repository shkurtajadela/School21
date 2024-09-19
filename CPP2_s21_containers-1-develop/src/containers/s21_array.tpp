#include "s21_array.h"

namespace s21 {
template <typename T, size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  std::copy(items.begin(), items.end(), elems_);
}

template <typename T, size_t N>
array<T, N>::array(const array &a) {
  std::copy(a.elems_, a.elems_ + N, elems_);
}

template <typename T, size_t N>
array<T, N>::array(array &&a) noexcept {
  std::move(a.elems_, a.elems_ + N, elems_);
}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(const array &a) {
  std::copy(a.elems_, a.elems_ + N, elems_);
  return *this;
}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(array &&a) noexcept {
  for (size_t i = 0; i < N; ++i) {
    elems_[i] = std::move(a.elems_[i]);
  }
  return *this;
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  return (*this)[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  return (*this)[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of array range");
  }
  return elems_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of array range");
  }
  return elems_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return elems_[0];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return elems_[N - 1];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return elems_;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return elems_;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return elems_ + size_;
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const {
  return elems_;
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const {
  return elems_ + size_;
}

template <typename T, size_t N>
bool array<T, N>::empty() {
  return size_ == 0;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return size_;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return size_;
}

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  std::swap_ranges(elems_, elems_ + N, other.elems_);
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(elems_, elems_ + N, value);
}

}  // namespace s21
