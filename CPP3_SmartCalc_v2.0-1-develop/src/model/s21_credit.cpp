#include "s21_credit.h"

namespace s21 {

/* Устанавливает тип платежей как аннуитетный. */
void Credit::SetAnnuity() noexcept { payment_type_ = ANNUITY; }

/* Устанавливает тип платежей как дифференцированный. */
void Credit::SetDifferential() noexcept { payment_type_ = DIFFERENTIAL; }

/* Устанавливает срок кредита в месяцах. */
void Credit::SetTime(int months) noexcept { time_ = months; }

/* Устанавливает процентную ставку по кредиту. */
void Credit::SetRate(double rate) noexcept { rate_ = rate; }

/* Устанавливает сумму кредита. */
void Credit::SetCredit(double credit) noexcept { credit_ = credit; }

/* Устанавливает дату начала выплат (месяц и год). */
void Credit::SetStartDate(int month, int year) {
  start_month_ = month;
  start_year_ = year;
}

/* Устанавливает текущую дату как дату начала выплат. */
void Credit::SetStartDate() {
  time_t t = std::time(NULL);
  struct tm time_data = *std::localtime(&t);
  start_month_ = time_data.tm_mon + 1;
  start_year_ = time_data.tm_year + 1900;
}

/* Возвращает текущий тип платежей (аннуитетный или дифференцированный). */
Credit::Type Credit::GetType() const noexcept { return payment_type_; }

/* Возвращает срок кредита в месяцах. */
int Credit::GetTime() const noexcept { return time_; }

/* Возвращает процентную ставку по кредиту. */
double Credit::GetRate() const noexcept { return rate_; }

/* Возвращает сумму кредита. */
double Credit::GetCredit() const noexcept { return credit_; }

/* Возвращает месяц начала выплат. */
int Credit::GetStartMonth() const noexcept { return start_month_; }

/* Возвращает год начала выплат. */
int Credit::GetStartYear() const noexcept { return start_year_; }

/* Возвращает общую сумму, выплаченную по кредиту. */
double Credit::GetSummaryPaid() const noexcept { return sum_paid_; }

/* Возвращает общую сумму, выплаченную в счет основного долга. */
double Credit::GetSummaryMainPart() const noexcept { return sum_main_paid_; }

/* Возвращает общую сумму, выплаченную в счет процентов по кредиту. */
double Credit::GetSummaryRatePart() const noexcept { return sum_rate_paid_; }

/* Возвращает количество записей в массиве данных по платежам. */
size_t Credit::GetDataSize() const noexcept { return data_.size(); }

/* Возвращает итератор на начало массива данных по платежам. */
std::vector<Credit::CreditMonth>::const_iterator Credit::GetData()
    const noexcept {
  return data_.cbegin();
}

/* Перегрузка оператора [], возвращает данные по платежу за конкретный месяц. */
Credit::CreditMonth Credit::operator[](size_t pos) const noexcept {
  return data_[pos];
}

/* Главная функция для расчета кредита.
   Вызывается после установки всех значений.
   Если все данные корректны, она заполняет вектор данных и итоговые суммы,
   и возвращает true. Если данные некорректны, возвращает false. */
bool Credit::Calculate() {
  if (Validate() == true) {
    Reset();
    data_.resize(time_);
    data_.shrink_to_fit();  // Уменьшает размер вектора до количества элементов.
    if (payment_type_ == ANNUITY)
      CalculateAnnuity();  // Рассчитывает аннуитетные платежи.
    else
      CalculateDifferential();  // Рассчитывает дифференцированные платежи.
    return true;
  }
  return false;
}

/* Вспомогательные функции */

/* Сбрасывает все накопленные суммы и очищает данные по платежам. */
void Credit::Reset() noexcept {
  sum_paid_ = 0.0;
  sum_main_paid_ = 0.0;
  sum_rate_paid_ = 0.0;
  data_.clear();
}

/* Проверяет корректность всех данных для расчета кредита. */
bool Credit::Validate() const noexcept {
  return ValidateCredit() && ValidateRate() && ValidateTime() &&
         ValidateStartDate();
}

/* Проверяет корректность суммы кредита. */
bool Credit::ValidateCredit() const noexcept {
  return credit_ > 0.0 && credit_ <= MAX_CREDIT_ && !std::isnan(credit_) &&
         !std::isinf(credit_);
}

/* Проверяет корректность процентной ставки. */
bool Credit::ValidateRate() const noexcept {
  return rate_ > 0.0 && rate_ <= MAX_RATE_ && !std::isnan(rate_) &&
         !std::isinf(rate_);
}

/* Проверяет корректность срока кредита. */
bool Credit::ValidateTime() const noexcept {
  return time_ > 0 && time_ <= MAX_TIME_;
}

/* Проверяет корректность даты начала выплат. */
bool Credit::ValidateStartDate() const noexcept {
  return start_month_ > 0 && start_month_ <= 12 && start_year_ >= MIN_YEAR_ &&
         start_year_ <= MAX_YEAR_;
}

/* Рассчитывает аннуитетные платежи по кредиту. */
void Credit::CalculateAnnuity() noexcept {
  // Инициализация первого месяца выплат.
  data_[0].month_ = start_month_;
  data_[0].year_ = start_year_;
  data_[0].rate_fee_ = bankRoundTwoDecimal(credit_ * rate_ / 12.0);
  data_[0].payment_ = bankRoundTwoDecimal(
      credit_ * rate_ / 12.0 /
      (1.0 - std::pow(1.0 + rate_ / 12.0, -static_cast<double>(time_))));
  data_[0].main_fee_ =
      bankRoundTwoDecimal(data_[0].payment_ - data_[0].rate_fee_);
  data_[0].leftover_ = bankRoundTwoDecimal(credit_ - data_[0].main_fee_);

  // Рассчет для всех последующих месяцев.
  for (int i = 1; i < time_; ++i) {
    data_[i].month_ = data_[i - 1].month_ + 1;
    data_[i].year_ = data_[i - 1].year_;
    if (data_[i].month_ > 12) {
      data_[i].month_ = 1;
      data_[i].year_++;
    }
    data_[i].payment_ = data_[0].payment_;
    data_[i].rate_fee_ =
        bankRoundTwoDecimal(data_[i - 1].leftover_ * rate_ / 12.0);
    data_[i].main_fee_ =
        bankRoundTwoDecimal(data_[i].payment_ - data_[i].rate_fee_);
    data_[i].leftover_ =
        bankRoundTwoDecimal(data_[i - 1].leftover_ - data_[i].main_fee_);
  }
  CalculateSummary();  // Подсчитывает итоговые суммы по кредиту.
}

/* Рассчитывает дифференцированные платежи по кредиту. */
void Credit::CalculateDifferential() noexcept {
  // Инициализация первого месяца выплат.
  data_[0].month_ = start_month_;
  data_[0].year_ = start_year_;
  data_[0].main_fee_ = credit_ / time_;
  data_[0].payment_ = data_[0].main_fee_ + credit_ * rate_ / 12.0;
  data_[0].rate_fee_ = data_[0].payment_ - data_[0].main_fee_;
  data_[0].leftover_ = credit_ - data_[0].main_fee_;

  // Рассчет для всех последующих месяцев.
  for (int i = 1; i < time_; ++i) {
    data_[i].month_ = data_[i - 1].month_ + 1;
    data_[i].year_ = data_[i - 1].year_;
    if (data_[i].month_ > 12) {
      data_[i].month_ = 1;
      data_[i].year_++;
    }
    data_[i].main_fee_ = data_[0].main_fee_;
    data_[i].payment_ =
        data_[0].main_fee_ + (credit_ - data_[0].main_fee_ * i) * rate_ / 12.0;
    data_[i].rate_fee_ = data_[i].payment_ - data_[i].main_fee_;
    data_[i].leftover_ = data_[i - 1].leftover_ - data_[i].main_fee_;
  }
  CalculateSummary();  // Подсчитывает итоговые суммы по кредиту.
  RoundData();  // Округляет все значения до двух знаков после запятой.
}

/* Подсчитывает итоговые суммы по кредиту: общую сумму выплат,
   сумму, выплаченную в счет основного долга, и сумму, выплаченную в счет
   процентов. */
void Credit::CalculateSummary() noexcept {
  for (int i = 0; i < time_; ++i) {
    sum_paid_ += data_[i].payment_;
    sum_main_paid_ += data_[i].main_fee_;
    sum_rate_paid_ += data_[i].rate_fee_;
  }
}

/* Округляет все данные по платежам и итоговые суммы до двух знаков после
 * запятой. */
void Credit::RoundData() noexcept {
  for (int i = 0; i < time_; ++i) {
    data_[i].main_fee_ = bankRoundTwoDecimal(data_[i].main_fee_);
    data_[i].payment_ = bankRoundTwoDecimal(data_[i].payment_);
    data_[i].rate_fee_ = bankRoundTwoDecimal(data_[i].rate_fee_);
    data_[i].leftover_ = bankRoundTwoDecimal(data_[i].leftover_);
  }
  sum_paid_ = bankRoundTwoDecimal(sum_paid_);
  sum_main_paid_ = bankRoundTwoDecimal(sum_main_paid_);
  sum_rate_paid_ = bankRoundTwoDecimal(sum_rate_paid_);
}

}  // namespace s21
