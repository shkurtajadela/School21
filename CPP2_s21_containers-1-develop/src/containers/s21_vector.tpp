#include "s21_vector.h"

namespace s21 {

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : data_(new value_type[n]), size_(n), capacity_(n) {
  std::fill_n(data_, n, value_type());
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : data_(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
vector<T>::vector(const vector &v)
    : data_(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <typename T>
vector<T>::vector(vector &&v) noexcept
    : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
  v.data_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &v) {
  if (data_) delete[] data_;
  data_ = new value_type[v.capacity_];
  capacity_ = v.capacity_;
  size_ = v.size_;
  std::copy(v.data_, v.data_ + v.size_, data_);
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) noexcept {
  if (data_) delete[] data_;
  size_ = v.size_;
  capacity_ = v.capacity_;
  data_ = v.data_;
  v.data_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of vector range");
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return this->at(pos);
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  if (pos >= size_) throw std::out_of_range("Index out of vector range");
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (!size_) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (!size_) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[size_ - 1];
}

template <typename T>
T *vector<T>::data() noexcept {
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return data_ + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
  return data_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const {
  return data_ + size_;
}

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_t>::max() / sizeof(value_type);
}

template <typename T>
void vector<T>::reserve(size_type new_capacity) {
  if (new_capacity <= capacity_) {
    return;
  }

  if (new_capacity > max_size()) {
    throw std::out_of_range("Too large size");
  }

  T *temp = new value_type[new_capacity];
  std::copy(data_, data_ + size_, temp);
  delete[] data_;
  data_ = temp;
  capacity_ = new_capacity;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ != capacity_) {
    T *temp = new value_type[size_];
    std::copy(data_, data_ + size_, temp);
    delete[] data_;
    data_ = temp;
    capacity_ = size_;
  }
}

template <typename T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) reserve(capacity_ ? capacity_ * 2 : 1);
  data_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type idx = pos - begin();
  if (idx > size_) {
    throw std::out_of_range("Index out of vector range");
  }
  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }
  iterator new_pos = begin() + idx;
  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }
  *new_pos = value;
  ++size_;

  return new_pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type position = pos - begin();
  if (position > size_) {
    throw std::out_of_range("Index out of vector range");
  }
  for (iterator it = pos; it != end() - 1; ++it) {
    *it = *(it + 1);
  }
  --size_;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> tmp{args...};
  iterator cur_pos = begin() + (pos - cbegin());
  for (size_t i = 0; i < tmp.size(); ++i) {
    cur_pos = insert(cur_pos, tmp[i]);
    ++cur_pos;
  }

  return cur_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}

}  // namespace s21
