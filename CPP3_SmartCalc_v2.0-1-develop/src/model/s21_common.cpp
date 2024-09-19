#include "s21_common.h"

namespace s21 {

/* Регулярное банковское округление числа типа double до целого значения. */
double bankRound(double number) noexcept {
  // Проверяем, если дробная часть числа равна 0.5 (с точностью до 1e-10),
  // тогда округляем в зависимости от чётности предшествующего числа.
  if (number >= 0.0 &&
      std::fabs(std::fabs(number - std::floor(number)) - 0.5) < 1e-10) {
    // Если предшествующее число чётное, округляем вниз (к ближайшему чётному).
    if (std::fabs(std::fmod(std::fmod(std::floor(number), 10.0), 2.0)) < 1e-10)
      number = std::floor(number);
    else
      // Если предшествующее число нечётное, округляем вверх.
      number = std::ceil(number);
  } else if (number < 0.0 &&
             std::fabs(std::fabs(number - std::floor(number)) - 0.5) < 1e-10) {
    // Аналогичная проверка для отрицательных чисел.
    if (std::fabs(std::fmod(std::fmod(std::ceil(number), 10.0), 2.0)) < 1e-10)
      number = std::ceil(number);
    else
      number = std::floor(number);
  } else {
    // Если дробная часть не равна 0.5, используем обычное округление.
    number = std::round(number);
  }
  return number;
}

/* Банковское округление числа до значения с двумя знаками после запятой. */
double bankRoundTwoDecimal(double number) noexcept {
  return bankRound(number * 100.0) / 100.0;
}

/* Регулярное банковское округление числа типа long double до целого значения.
 */
long double bankRoundLong(long double number) noexcept {
  return bankRound(number);
}

/* Банковское округление числа типа long double до значения с двумя знаками
 * после запятой. */
long double bankRoundLongTwoDecimal(long double number) noexcept {
  return bankRoundLong(number * 100.0L) / 100.0L;
}

/* Конструктор класса Date, инициализирующий объект текущей датой. */
Date::Date() {
  time_t t = std::time(NULL);
  if (std::localtime(&t) == NULL)
    throw std::runtime_error(
        "Can't read local time format or it doesn't exist.");  // Ошибка при
                                                               // невозможности
                                                               // получения
                                                               // локального
                                                               // времени.
  current_ = *std::localtime(&t);  // Устанавливаем текущую дату.
  current_.tm_sec = 0;
  current_.tm_min = 0;
  current_.tm_hour = 12;
  // Устанавливаем базовую дату для расчётов (например, 01.01.1970).
  base_.tm_sec = 0;
  base_.tm_min = 0;
  base_.tm_hour = 12;
  base_.tm_mday = BASE_DAY;
  base_.tm_mon = BASE_MONTH - 1;
  base_.tm_year = BASE_YEAR - 1900;
}

/* Конструктор класса Date, инициализирующий объект заданной датой. */
Date::Date(int day, int month, int year) {
  if (isDateValid(day, month, year) == false)
    throw std::invalid_argument("Invalid date.");  // Ошибка при неверной дате.
  current_.tm_sec = 0;
  current_.tm_min = 0;
  current_.tm_hour = 12;
  current_.tm_mday = day;
  current_.tm_mon = month - 1;
  current_.tm_year = year - 1900;
  // Устанавливаем базовую дату для расчётов.
  base_.tm_sec = 0;
  base_.tm_min = 0;
  base_.tm_hour = 12;
  base_.tm_mday = BASE_DAY;
  base_.tm_mon = BASE_MONTH - 1;
  base_.tm_year = BASE_YEAR - 1900;
}

/* Устанавливает новую дату для объекта. */
void Date::setDate(int day, int month, int year) {
  if (isDateValid(day, month, year) == false)
    throw std::invalid_argument("Invalid date.");  // Ошибка при неверной дате.
  current_.tm_mday = day;
  current_.tm_mon = month - 1;
  current_.tm_year = year - 1900;
}

/* Возвращает текущий день. */
int Date::getDay() const noexcept { return current_.tm_mday; }

/* Возвращает текущий месяц. */
int Date::getMonth() const noexcept { return current_.tm_mon + 1; }

/* Возвращает текущий год. */
int Date::getYear() const noexcept { return current_.tm_year + 1900; }

/* Вычисляет разницу в днях между текущей датой и переданной. */
int Date::subtract(const Date& sub) const {
  return getDiff(current_, sub.current_);
}

/* Перегрузка оператора | для вычисления разницы в днях. */
int Date::operator|(const Date& sub) const { return subtract(sub); }

/* Перегрузка оператора + для добавления дней к дате. */
Date operator+(int days, const Date& date) {
  Date date_new(date);
  date_new.addDays(days);
  return date_new;
}

/* Перегрузка оператора + для добавления дней к текущей дате. */
Date Date::operator+(int days) const {
  Date date_new(*this);
  date_new.addDays(days);
  return date_new;
}

/* Перегрузка оператора - для вычитания дней из текущей даты. */
Date Date::operator-(int days) const {
  Date date_new(*this);
  date_new.addDays(-days);
  return date_new;
}

/* Перегрузка оператора += для добавления дней к текущей дате. */
Date Date::operator+=(int days) {
  addDays(days);
  return *this;
}

/* Перегрузка оператора -= для вычитания дней из текущей даты. */
Date Date::operator-=(int days) {
  addDays(-days);
  return *this;
}

/* Перегрузка постфиксного оператора ++ для увеличения текущей даты на один
 * день. */
Date Date::operator++(int) {
  addDays(1);
  return *this;
}

/* Перегрузка постфиксного оператора -- для уменьшения текущей даты на один
 * день. */
Date Date::operator--(int) {
  addDays(-1);
  return *this;
}

/* Перегрузка префиксного оператора ++ для увеличения текущей даты на один день.
 */
Date Date::operator++() {
  addDays(1);
  return *this;
}

/* Перегрузка префиксного оператора -- для уменьшения текущей даты на один день.
 */
Date Date::operator--() {
  addDays(-1);
  return *this;
}

/* Перегрузка оператора == для проверки равенства дат. */
bool Date::operator==(const Date& date) const {
  return getDaysSinceBase() == date.getDaysSinceBase();
}

/* Перегрузка оператора != для проверки неравенства дат. */
bool Date::operator!=(const Date& date) const {
  return getDaysSinceBase() != date.getDaysSinceBase();
}

/* Перегрузка оператора >= для проверки, что текущая дата больше или равна
 * другой дате. */
bool Date::operator>=(const Date& date) const {
  return getDaysSinceBase() >= date.getDaysSinceBase();
}

/* Перегрузка оператора <= для проверки, что текущая дата меньше или равна
 * другой дате. */
bool Date::operator<=(const Date& date) const {
  return getDaysSinceBase() <= date.getDaysSinceBase();
}

/* Перегрузка оператора > для проверки, что текущая дата больше другой даты. */
bool Date::operator>(const Date& date) const {
  return getDaysSinceBase() > date.getDaysSinceBase();
}

/* Перегрузка оператора < для проверки, что текущая дата меньше другой даты. */
bool Date::operator<(const Date& date) const {
  return getDaysSinceBase() < date.getDaysSinceBase();
}

/* Добавляет указанное количество дней к текущей дате. */
void Date::addDays(int days) {
  std::tm new_date = current_;
  time_t tmp = std::mktime(&new_date);
  tmp += static_cast<time_t>(days) *
         (60 * 60 * 24);  // Пересчитываем количество дней в секунды.
  new_date = *std::localtime(&tmp);
  current_ = new_date;  // Устанавливаем новую дату.
}

/* Добавляет указанное количество месяцев к текущей дате. */
void Date::addMonths(int months) {
  int new_day = getDay(), new_month = 0, new_year = 0;
  // Вычисляем новый месяц и год с учётом возможного перехода через год.
  if (getMonth() + months <= 0) {
    new_month = 12 - std::abs(getMonth() + months) % 12;
    new_year = getYear() - 1 - std::abs(getMonth() + months) / 12;
  } else {
    new_month = (getMonth() + months - 1) % 12 + 1;
    new_year = getYear() + (getMonth() + months - 1) / 12;
  }

  // Если новая дата невалидна (например, 31 февраля), уменьшаем день до
  // валидного значения.
  while (!isDateValid(new_day, new_month, new_year)) {
    new_day--;
  }
  setDate(new_day, new_month, new_year);  // Устанавливаем новую дату.
}

/* Добавляет указанное количество лет к текущей дате. */
void Date::addYears(int years) {
  int new_year = getYear() + years;
  // Проверяем валидность новой даты и корректируем день, если необходимо.
  if (!isDateValid(getDay(), getMonth(), new_year))
    setDate(getDay() - 1, getMonth(), new_year);
  else
    setDate(getDay(), getMonth(), new_year);
}

/* Возвращает новую дату, сдвинутую на указанное количество месяцев. */
Date Date::shiftMonths(int months) const {
  Date ret = *this;
  ret.addMonths(months);
  return ret;
}

/* Возвращает количество дней, прошедших с базовой даты. */
int Date::getDaysSinceBase() const { return getDiff(current_, base_); }

/* Вычисляет разницу в днях между двумя датами. */
int Date::getDiff(const struct std::tm& end,
                  const struct std::tm& start) const {
  struct std::tm end_new = {}, start_new = {};
  end_new.tm_sec = end.tm_sec;
  end_new.tm_min = end.tm_min;
  end_new.tm_hour = end.tm_hour;
  end_new.tm_mday = end.tm_mday;
  end_new.tm_mon = end.tm_mon;
  end_new.tm_year = end.tm_year;
  start_new.tm_sec = start.tm_sec;
  start_new.tm_min = start.tm_min;
  start_new.tm_hour = start.tm_hour;
  start_new.tm_mday = start.tm_mday;
  start_new.tm_mon = start.tm_mon;
  start_new.tm_year = start.tm_year;
  // Рассчитываем разницу в днях между двумя датами.
  double difference =
      std::round(std::difftime(std::mktime(&end_new), std::mktime(&start_new)) /
                 (60.0 * 60.0 * 24.0));
  return static_cast<int>(difference);
}

/* Проверяет, является ли дата корректной. */
bool Date::isDateValid(int d, int m, int y) noexcept {
  if (y < BASE_YEAR) return false;  // Год не может быть меньше базового.
  if (m < 1 || m > 12)
    return false;  // Месяц должен быть в диапазоне от 1 до 12.
  if (d < 1 || d > 31)
    return false;  // День должен быть в диапазоне от 1 до 31.
  // Проверка на корректность дней в месяцах с разным количеством дней.
  if (d == 31 && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11))
    return false;
  if (d == 30 && m == 2) return false;
  // Проверка на високосный год.
  if (m == 2 && d == 29 && y % 4 != 0) return false;
  if (m == 2 && d == 29 && y % 400 == 0) return true;
  if (m == 2 && d == 29 && y % 100 == 0) return false;
  if (m == 2 && d == 29 && y % 4 == 0) return true;
  return true;
}

}  // namespace s21
