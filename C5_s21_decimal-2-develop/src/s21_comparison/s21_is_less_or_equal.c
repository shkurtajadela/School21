#include "../s21_decimal.h"

// comapres decimal1 <= decimal2
// 1 - value_1 <= value_2
// 0 - value_1 > value_2
int s21_is_less_or_equal(s21_decimal value_1,
                         s21_decimal value_2) {  // 0 - FALSE, 1 - TRUE
  return (s21_is_equal(value_1, value_2) || s21_is_less(value_1, value_2)) ? 1
                                                                           : 0;
}
