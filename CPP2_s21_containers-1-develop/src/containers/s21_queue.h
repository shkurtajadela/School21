#include "s21_list.h"

namespace s21 {

/**
 * @brief Класс реализующий очередь с использованием двусвязного списка.
 * @tparam T Тип элементов очереди.
 * @author sejuanif
 */
template <typename T>
class queue {
 private:
  list<T> data;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  /**
   * @brief Конструктор по умолчанию. Создает пустую очередь.
   */
  queue() {}

  /**
   * @brief Конструктор инициализации с использованием списка инициализаторов.
   * @param items Список инициализаторов для инициализации очереди.
   */
  queue(std::initializer_list<value_type> const& items) : data(items) {}

  /**
   * @brief Конструктор копирования. Создает новую очередь как копию другой
   * очереди.
   * @param other Очередь для копирования.
   */
  queue(const queue<T>& other) : data(other.data) {}

  /**
   * @brief Конструктор перемещения. Создает новую очередь перемещением
   * элементов из другой очереди.
   * @param other Очередь для перемещения.
   */
  queue(queue<T>&& other) : data(std::move(other.data)) {}

  /**
   * @brief Оператор присваивания перемещения. Перемещает элементы из другой
   * очереди в эту очередь.
   * @param other Очередь для перемещения.
   * @return Ссылка на эту очередь.
   */
  queue& operator=(queue&& other) {
    data = std::move(other.data);
    return *this;
  }

  /**
   * @brief Деструктор. Очищает все элементы из очереди.
   */
  ~queue() { data.clear(); }

  /**
   * @brief Возвращает константную ссылку на первый элемент очереди.
   * @return Константная ссылка на первый элемент.
   */
  const_reference front() const { return data.front(); }

  /**
   * @brief Возвращает константную ссылку на последний элемент очереди.
   * @return Константная ссылка на последний элемент.
   */
  const_reference back() const { return data.back(); }

  /**
   * @brief Проверяет, пуста ли очередь.
   * @return true, если очередь пуста, иначе false.
   */
  bool empty() const { return data.empty(); }

  /**
   * @brief Возвращает количество элементов в очереди.
   * @return Количество элементов в очереди.
   */
  size_type size() const { return data.size(); }

  /**
   * @brief Добавляет элемент в конец очереди.
   * @param value Элемент для добавления.
   */
  void push(const_reference value) { data.push_back(value); }

  /**
   * @brief Удаляет первый элемент из очереди.
   */
  void pop() { data.pop_front(); }

  /**
   * @brief Меняет местами содержимое этой очереди с содержимым другой очереди.
   * @param other Очередь для обмена содержимым.
   */
  void swap(queue& other) { data.swap(other.data); }

  /**
   * @brief Вставляет несколько элементов в конец очереди.
   * @param args Переменное число аргументов, представляющих элементы для
   * вставки.
   */
  template <typename... Args>
  void insert_many_back(Args... args) {
    (data.push_back(args), ...);
  }
};
}  // namespace s21