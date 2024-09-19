#include "s21_deposit.h"

namespace s21 {

/* Методы для установки значений пользовательских переменных. Проверка границ
 * значений не проводится. */

/* Устанавливает сумму депозита. */
void Deposit::setDeposit(double value) noexcept { deposit_ = value; }

/* Устанавливает срок депозита в днях. */
void Deposit::setTerm(int days) noexcept { term_ = days; }

/* Устанавливает тип срока (например, дни, месяцы, годы). */
void Deposit::setTermType(TermType value) noexcept { term_type_ = value; }

/* Устанавливает текущую дату как дату начала депозита. */
bool Deposit::setStartDate() {
  Date current;
  start_date_ = current;
  return true;
}

/* Устанавливает дату начала депозита, если дата валидна. */
bool Deposit::setStartDate(int day, int month, int year) {
  if (Date::isDateValid(day, month, year) == false) return false;
  start_date_.setDate(day, month, year);
  return true;
}

/* Устанавливает дату начала депозита на основе переданного объекта Date. */
bool Deposit::setStartDate(Date& date) noexcept {
  start_date_ = date;
  return true;
}

/* Устанавливает процентную ставку по депозиту. */
void Deposit::setInterest(double value) noexcept { interest_ = value; }

/* Устанавливает налоговую ставку. */
void Deposit::setTax(double value) noexcept { tax_ = value; }

/* Устанавливает, будет ли применяться капитализация процентов. */
void Deposit::setCapitalization(bool set) noexcept { capital_ = set; }

/* Устанавливает периодичность выплат процентов. */
void Deposit::setPeriodicity(PayPeriod value) noexcept { periodicity_ = value; }

/* Устанавливает минимальный остаток, который должен оставаться на счете. */
void Deposit::setRemainderLimit(double value) noexcept {
  remainder_limit_ = value;
}

/* Добавляет операцию пополнения депозита. */
void Deposit::addReplenish(OperPeriod freq, Date date, double value) {
  replenish_list_.push_back(Operation(freq, date, value));
}

/* Добавляет операцию снятия средств с депозита. */
void Deposit::addWithdrawal(OperPeriod freq, Date date, double value) {
  withdrawal_list_.push_back(Operation(freq, date, value));
}

/* Удаляет операцию пополнения по указанному индексу. */
void Deposit::removeReplenish(size_t index) noexcept {
  replenish_list_.erase(replenish_list_.begin() + index);
}

/* Удаляет операцию снятия по указанному индексу. */
void Deposit::removeWithdrawal(size_t index) noexcept {
  withdrawal_list_.erase(withdrawal_list_.begin() + index);
}

/* Удаляет последнюю операцию пополнения. */
void Deposit::popBackReplenish() noexcept {
  if (getReplenishListSize() > 0) replenish_list_.pop_back();
}

/* Удаляет последнюю операцию снятия. */
void Deposit::popBackWithdrawal() noexcept {
  if (getWithdrawalListSize() > 0) withdrawal_list_.pop_back();
}

/* Очищает список операций пополнения. */
void Deposit::clearReplenish() noexcept { replenish_list_.clear(); }

/* Очищает список операций снятия. */
void Deposit::clearWithdrawal() noexcept { withdrawal_list_.clear(); }

/* Методы для получения значений пользовательских переменных. Проверка границ
 * значений не проводится. */

/* Возвращает, включена ли капитализация процентов. */
bool Deposit::isCapitalization() const noexcept { return capital_; }

/* Возвращает сумму депозита. */
double Deposit::getDeposit() const noexcept { return deposit_; }

/* Возвращает минимальный остаток на счете. */
double Deposit::getRemainderLimit() const noexcept { return remainder_limit_; }

/* Возвращает количество операций пополнения. */
size_t Deposit::getReplenishListSize() const noexcept {
  return replenish_list_.size();
}

/* Возвращает количество операций снятия. */
size_t Deposit::getWithdrawalListSize() const noexcept {
  return withdrawal_list_.size();
}

/* Возвращает итератор на элемент списка операций пополнения по индексу. */
std::vector<Deposit::Operation>::const_iterator
Deposit::getReplenishListElement(size_t index) const noexcept {
  return replenish_list_.cbegin() + index;
}

/* Возвращает итератор на элемент списка операций снятия по индексу. */
std::vector<Deposit::Operation>::const_iterator
Deposit::getWithdrawalListElement(size_t index) const noexcept {
  return withdrawal_list_.cbegin() + index;
}

/* Методы для получения результатов расчетов. */

/* Возвращает количество событий (операций) в списке. */
size_t Deposit::getEventListSize() const noexcept { return event_list_.size(); }

/* Возвращает итератор на элемент списка событий по индексу. */
std::vector<Deposit::Event>::const_iterator Deposit::getEventListElement(
    size_t index) const noexcept {
  return event_list_.cbegin() + index;
}

/* Возвращает количество записей по налоговым отчислениям. */
size_t Deposit::getTaxListSize() const noexcept { return tax_list_.size(); }

/* Возвращает итератор на элемент списка налогов по индексу. */
std::vector<Deposit::Tax>::const_iterator Deposit::getTaxListElement(
    size_t index) const noexcept {
  return tax_list_.cbegin() + index;
}

/* Возвращает текущий баланс депозита. */
double Deposit::getBalance() const noexcept { return balance_; }

/* Возвращает общую сумму начисленных процентов. */
double Deposit::getInterestTotal() const noexcept { return interest_total_; }

/* Возвращает общую сумму налога на проценты. */
double Deposit::getTaxTotal() const noexcept { return tax_total_; }

/* Возвращает общую сумму пополнений. */
double Deposit::getReplenishTotal() const noexcept { return replenish_total_; }

/* Возвращает общую сумму снятий. */
double Deposit::getWithdrawalTotal() const noexcept {
  return withdrawal_total_;
}

/* Основной метод для расчета депозита. Проводит проверку данных. */
/* Возвращает false, если параметры депозита некорректны.
   Слабое место: функция строго зависит от порядка событий после сортировки -
   некоторые реализации std::sort не гарантируют, что равные элементы не
   поменяются местами, что может привести к некорректному порядку данных и
   ошибкам в расчетах. */
bool Deposit::calculate() {
  if (validateSettings() == false) return false;
  setDefaultValues();
  calculateEndDate();
  insertDeposit();
  insertReplenishList();
  insertWithdrawalList();
  insertPaydays();
  insertNewYears();
  insertLastPayday();

  std::sort(event_list_.begin(), event_list_.end(), dateComparator);

  /* Объединяет пополнения и снятия, происходящие в один и тот же день.
   * Установите 'false', если требуется полное представление. */
  fixEventList(true);

  calculateValues();  // Выполняет расчеты по каждому событию.
  return true;
}

/* Вспомогательные методы */

/* Сбрасывает все значения переменных и очищает списки событий и налогов. */
void Deposit::setDefaultValues() noexcept {
  event_list_.clear();
  tax_list_.clear();
  balance_ = 0.0L;
  year_income_ = 0.0L;
  interest_total_ = 0.0L;
  tax_total_ = 0.0L;
  withdrawal_total_ = 0.0L;
  replenish_total_ = 0.0L;
}

/* Рассчитывает дату окончания срока депозита в зависимости от типа срока. */
void Deposit::calculateEndDate() {
  end_date_ = start_date_;
  if (term_type_ == T_MONTH) {
    end_date_.addMonths(term_);
  } else if (term_type_ == T_YEAR) {
    end_date_ = nextMonthDate(end_date_, term_ * 12);
  } else {
    end_date_ += term_;
  }
}

/* Выполняет расчеты по каждому событию из списка событий. */
void Deposit::calculateValues() {
  countDayValue(start_date_.getYear());
  for (std::vector<Event>::iterator i = event_list_.begin();
       i != event_list_.end(); ++i) {
    switch (i->event_) {
      case E_REPLENISH:
        countReplenish(i);
        break;
      case E_WITHDRAWAL:
        countWithdrawal(i);
        break;
      case E_NEWYEAR:
        countNewyear(i);
        break;
      case E_PAYDAY:
        countPayday(i);
        break;

      default:
        break;
    }
  }
}

/* Рассчитывает изменения после пополнения депозита. */
void Deposit::countReplenish(std::vector<Event>::iterator i) noexcept {
  countGain(i);
  countBalance(i);
  if (i != event_list_.begin()) replenish_total_ += i->balance_change_;
}

/* Рассчитывает изменения после снятия средств с депозита. */
void Deposit::countWithdrawal(std::vector<Event>::iterator i) noexcept {
  countGain(i);
  if (balance_ + i->balance_change_ >= remainder_limit_) {
    countBalance(i);
    withdrawal_total_ -= i->balance_change_;
  } else {
    i->balance_ = balance_;
    i->event_ = E_DECLINE;
  }
}

/* Рассчитывает изменения при наступлении нового года. */
void Deposit::countNewyear(std::vector<Event>::iterator i) {
  countGain(i);
  countBalance(i);
  countDayValue(i->date_.getYear() + 1);
  if (i->date_ != start_date_) countTax(i);
}

/* Рассчитывает изменения при выплате процентов. */
void Deposit::countPayday(std::vector<Event>::iterator i) {
  countGain(i);
  sumPreviousGains(i);
  if (capital_ == true)
    i->balance_change_ = i->gain_;
  else
    i->payment_ = i->gain_;
  countBalance(i);
  interest_total_ += i->gain_;
  year_income_ += i->gain_;
  if (i->date_ == end_date_) {
    countTax(i);
  }
}

/* Рассчитывает текущий баланс депозита на основе изменения баланса в текущем
 * событии. */
void Deposit::countBalance(std::vector<Event>::iterator i) noexcept {
  balance_ += i->balance_change_;
  i->balance_ = balance_;  // Обновляет значение баланса в текущем событии.
}

/* Рассчитывает прирост депозита. Внимание: обращается к предыдущему элементу
 * списка событий. */
void Deposit::countGain(std::vector<Event>::iterator i) noexcept {
  if (i > event_list_.begin())
    i->gain_ = day_value_ * (i->date_ | (i - 1)->date_) * balance_;
}

/* Суммирует приросты за предыдущие события до последнего дня выплаты и
 * сбрасывает их значения. */
void Deposit::sumPreviousGains(std::vector<Event>::iterator i) noexcept {
  for (std::vector<Event>::iterator j = i - 1;
       j->event_ != E_PAYDAY && j != event_list_.begin(); --j) {
    i->gain_ += j->gain_;
    j->gain_ =
        0.0L;  // Обнуляет прирост в предыдущем событии после суммирования.
  }
}

/* Рассчитывает налог на прирост по депозиту и добавляет его в список налогов.
 */
void Deposit::countTax(std::vector<Event>::iterator i) {
  long double gain = year_income_ * tax_;
  tax_total_ += gain;  // Обновляет общую сумму налога.
  tax_list_.push_back(Tax(i->date_.getYear(), year_income_,
                          gain));  // Добавляет налог в список.
  year_income_ = 0.0L;  // Сбрасывает годовой доход после расчета налога.
}

/* Рассчитывает значение прироста в день для заданного года. */
void Deposit::countDayValue(int year) noexcept {
  day_value_ = calculateDayValue(year, interest_);
}

/* Объединяет пополнения и снятия, произведенные в один и тот же день.
   Переставляет события "выплата" и "Новый год", если они происходят в один
   день, чтобы событие "Новый год" следовало за "выплатой". */
void Deposit::fixEventList(bool splice_on) noexcept {
  for (size_t i = 1; i < event_list_.size() - 1; ++i) {
    if (splice_on == true) {
      if (event_list_[i].date_ == event_list_[i + 1].date_ &&
          (event_list_[i].event_ == E_REPLENISH ||
           event_list_[i].event_ == E_WITHDRAWAL) &&
          (event_list_[i + 1].event_ == E_REPLENISH ||
           event_list_[i + 1].event_ == E_WITHDRAWAL)) {
        spliceOperations(i, i + 1);
        --i;  // Возвращаемся на один шаг назад после объединения.
      }
    }
  }
}

/* Объединяет два события (пополнение или снятие) в одно, если они происходят в
 * один день. */
void Deposit::spliceOperations(size_t first, size_t second) noexcept {
  event_list_[first].balance_change_ += event_list_[second].balance_change_;
  if (event_list_[first].balance_change_ < 0.0L)
    event_list_[first].event_ =
        E_WITHDRAWAL;  // Устанавливаем тип события как снятие, если сумма
                       // отрицательная.
  else
    event_list_[first].event_ =
        E_REPLENISH;  // Иначе устанавливаем как пополнение.
  event_list_.erase(event_list_.begin() + second);  // Удаляем второе событие.
}

/* Вставляет начальное пополнение депозита. */
void Deposit::insertDeposit() { pushEvent(E_REPLENISH, start_date_, deposit_); }

/* Вставляет события "Новый год" в список событий для каждого года действия
 * депозита. */
void Deposit::insertNewYears() {
  for (int i = 0; i < end_date_.getYear() - start_date_.getYear(); i++) {
    pushEvent(E_NEWYEAR, Date(31, 12, start_date_.getYear() + i));
  }
}

/* Вставляет в список событий все пополнения из списка пополнений. */
void Deposit::insertReplenishList() {
  for (size_t i = 0; i < replenish_list_.size(); ++i) {
    insertOperation(replenish_list_.cbegin() + i, E_REPLENISH);
  }
}

/* Вставляет в список событий все снятия из списка снятий. */
void Deposit::insertWithdrawalList() {
  for (size_t i = 0; i < withdrawal_list_.size(); ++i) {
    insertOperation(withdrawal_list_.cbegin() + i, E_WITHDRAWAL);
  }
}

/* Вставляет в список событий дни выплаты процентов в зависимости от
 * периодичности выплат. */
void Deposit::insertPaydays() {
  switch (periodicity_) {
    case P_DAILY:
      pushPaydaysSkipDays(1);  // Ежедневная выплата.
      break;
    case P_WEEKLY:
      pushPaydaysSkipDays(7);  // Еженедельная выплата.
      break;
    case P_MONTHLY:
      pushPaydaysSkipMonths(1);  // Ежемесячная выплата.
      break;
    case P_QUARTERLY:
      pushPaydaysSkipMonths(3);  // Ежеквартальная выплата.
      break;
    case P_BIANNUALLY:
      pushPaydaysSkipMonths(6);  // Полугодовая выплата.
      break;
    case P_ANNUALLY:
      pushPaydaysSkipMonths(12);  // Годовая выплата.
      break;

    default:
      break;
  }
}

/* Вставляет последнее событие выплаты процентов перед завершением депозита. */
void Deposit::insertLastPayday() { pushEvent(E_PAYDAY, end_date_); }

/* Вставляет операцию в список событий в зависимости от периодичности операции.
   Метод учитывает особенности работы с датами, такими как 29-31 числа месяца.
 */
void Deposit::insertOperation(std::vector<Operation>::const_iterator element,
                              EventType event) {
  Date date = element->date_;
  switch (element->period_) {
    case O_ONCE:
      if (date > start_date_ && date <= end_date_)
        pushEvent(event, date, element->value_);  // Однократная операция.
      break;
    case O_MONTHLY:
      pushOperationsShiftMonths(event, date, element->value_,
                                1);  // Ежемесячная операция.
      break;
    case O_BIMONTHLY:
      pushOperationsShiftMonths(event, date, element->value_,
                                2);  // Операция раз в два месяца.
      break;
    case O_QUARTERLY:
      pushOperationsShiftMonths(event, date, element->value_,
                                3);  // Операция раз в квартал.
      break;
    case O_BIANNUALLY:
      pushOperationsShiftMonths(event, date, element->value_,
                                6);  // Операция раз в полгода.
      break;
    case O_ANNUALLY:
      pushOperationsShiftMonthsWithOvercap(
          event, date, element->value_,
          12);  // Годовая операция с возможным переносом дат.
      break;

    default:
      break;
  }
}

/* Генерирует даты операций относительно стартовой даты с учетом корректировки
   дней. Например, 31.01.2024 + 1 месяц = 29.02.2024, 31.03.2024, 30.04.2024 и
   т.д. */
void Deposit::pushOperationsShiftMonths(EventType event, Date date,
                                        long double value, size_t step) {
  Date start = date;
  for (size_t j = step; date <= end_date_; j += step) {
    if (date > start_date_) pushEvent(event, date, value);
    date = start.shiftMonths(j);  // Сдвиг даты на j месяцев вперед.
  }
}

/* Генерирует даты операций относительно текущей даты с возможностью
   корректировки на 1-3 дня. Текущая дата всегда пересчитывается. */
void Deposit::pushOperationsShiftMonthsWithOvercap(EventType event, Date date,
                                                   long double value,
                                                   size_t step) {
  while (date <= end_date_) {
    if (date > start_date_) pushEvent(event, date, value);
    date = nextMonthDate(date, step);  // Сдвиг даты на step месяцев вперед с
                                       // учетом возможной корректировки.
  }
}

/* Вставляет дни выплаты процентов с пропуском месяцев на заданное количество
 * шагов. */
void Deposit::pushPaydaysSkipMonths(int step) {
  Date current = nextMonthDate(start_date_, step);
  for (; current < end_date_; current = nextMonthDate(current, step)) {
    pushEvent(E_PAYDAY, current);
  }
}

/* Вставляет дни выплаты процентов с пропуском дней на заданное количество
 * шагов. */
void Deposit::pushPaydaysSkipDays(int step) {
  Date current = start_date_ + step;
  for (; current < end_date_; current += step) {
    pushEvent(E_PAYDAY, current);
  }
}

/* Вставляет событие (операцию или выплату) в список событий. */
void Deposit::pushEvent(EventType event, Date date, long double change) {
  if (event == E_WITHDRAWAL)
    change = -change;  // Отрицательное значение для снятия средств.
  event_list_.push_back(Event(event, date, 0.0L, change, 0.0L,
                              0.0L));  // Добавление события в список.
}

/* Проверяет настройки депозита на корректность. */
bool Deposit::validateSettings() const noexcept {
  return checkReplenishes() && checkWithdrawals() &&
         checkPositiveDouble(deposit_) && checkPositiveDouble(interest_) &&
         checkPositiveDouble(tax_) && checkPositiveDouble(remainder_limit_) &&
         deposit_ <= MAX_DEPOSIT_VALUE && interest_ <= MAX_RATE &&
         tax_ <= MAX_TAX && checkDates();
}

/* Проверяет корректность списка пополнений депозита. */
bool Deposit::checkReplenishes() const noexcept {
  for (size_t i = 0; i < replenish_list_.size(); ++i) {
    if (replenish_list_[i].date_.getYear() > MAX_START_YEAR ||
        replenish_list_[i].value_ > MAX_DEPOSIT_VALUE ||
        !checkPositiveDouble(replenish_list_[i].value_))
      return false;
  }
  return true;
}

/* Проверяет корректность списка снятий с депозита. */
bool Deposit::checkWithdrawals() const noexcept {
  for (size_t i = 0; i < withdrawal_list_.size(); ++i) {
    if (withdrawal_list_[i].date_.getYear() > MAX_START_YEAR ||
        withdrawal_list_[i].value_ > MAX_DEPOSIT_VALUE ||
        !checkPositiveDouble(withdrawal_list_[i].value_))
      return false;
  }
  return true;
}

/* Проверяет, является ли значение положительным числом с плавающей точкой. */
bool Deposit::checkPositiveDouble(double value) const noexcept {
  return value >= 0.0 && !std::isnan(value) && !std::isinf(value) &&
         value < MAX_DOUBLE_VALUE;
}

/* Проверяет корректность дат и срока действия депозита. */
bool Deposit::checkDates() const noexcept {
  return term_ > 0 &&
         ((term_type_ == T_YEAR && term_ <= MAX_TERM_Y) ||
          (term_type_ == T_MONTH && term_ <= MAX_TERM_M) ||
          (term_type_ == T_DAY && term_ <= MAX_TERM_D)) &&
         start_date_.getYear() <= MAX_START_YEAR;
}

/* Возвращает дату, сдвинутую на n месяцев вперед, с учетом корректировки дней.
 */
Date Deposit::nextMonthDate(const Date& date, int n) {
  Date ret = date;
  int days = date.getDay();
  if (date.getDay() >= 29) {
    ret.addMonths(n);
    if (!Date::isDateValid(date.getDay(), ret.getMonth(), ret.getYear())) {
      ret.setDate(1, ret.getMonth(), ret.getYear());
      ret += days - 1;
      return ret;
    } else {
      ret.setDate(date.getDay(), ret.getMonth(), ret.getYear());
      return ret;
    }
  } else { /* if (date.getDay() < 29) */
    ret.addMonths(n);
    return ret;
  }
}

/* Рассчитывает значение прироста за день в зависимости от года (високосный или
 * нет). */
long double Deposit::calculateDayValue(int year, long double rate) noexcept {
  if (isLeapYear(year) == false) {
    return rate / 365.0L;
  } else {
    return rate / 366.0L;
  }
}

/* Проверяет, является ли год високосным. */
bool Deposit::isLeapYear(int year) noexcept {
  if (year % 400 == 0) return true;
  if (year % 100 == 0) return false;
  if (year % 4 == 0) return true;
  return false;
}

/* Компаратор для сортировки событий по дате, а также по типу события,
   если события происходят в один и тот же день. */
bool Deposit::dateComparator(const Event& first, const Event& second) noexcept {
  if (first.date_ == second.date_) {
    return first.event_ < second.event_;
  }
  return first.date_ < second.date_;
}

}  // namespace s21
