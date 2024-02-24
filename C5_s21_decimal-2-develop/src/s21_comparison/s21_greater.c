#include "../s21_decimal.h"

// 0 - value_1 <= value_2
// 1 - value_1 > value_2

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int ret_val = 0;
  int sign_1 = s21_decimal_get_sign(value_1);
  int sign_2 = s21_decimal_get_sign(value_2);

  if (s21_decimal_is_zero(value_1) && s21_decimal_is_zero(value_2)) {
    ret_val = 0;
  } else if (s21_decimal_is_zero(value_1) &&
             (s21_decimal_is_zero(value_2) == 0 &&
              s21_decimal_get_sign(value_2) == 0)) {
    ret_val = 0;
  } else if (s21_decimal_is_zero(value_1) &&
             (s21_decimal_is_zero(value_2) == 0 &&
              s21_decimal_get_sign(value_2) == 1)) {
    ret_val = 1;
  } else if (s21_decimal_is_zero(value_2) &&
             (s21_decimal_is_zero(value_1) == 0 &&
              s21_decimal_get_sign(value_1) == 0)) {
    ret_val = 1;
  } else if (s21_decimal_is_zero(value_2) &&
             (s21_decimal_is_zero(value_1) == 0 &&
              s21_decimal_get_sign(value_1) == 1)) {
    ret_val = 0;
  } else if (sign_1 == sign_2) {
    int end_flag = 0;
    s21_convert_to_same_scale(&value_1, &value_2, 0);
    for (int i = 2; i >= 0 && end_flag == 0; i--) {
      for (int j = 31; j >= 0 && end_flag == 0; j--) {
        if (((value_1.bits[i] >> j) > (value_2.bits[i] >> j) && sign_1 == 0) ||
            ((value_1.bits[i] >> j) < (value_2.bits[i] >> j) && sign_1 == 1)) {
          ret_val = 1;
          end_flag = 1;
        } else if (((value_1.bits[i] >> j) < (value_2.bits[i] >> j) &&
                    sign_1 == 0) ||
                   ((value_1.bits[i] >> j) > (value_2.bits[i] >> j) &&
                    sign_1 == 1)) {
          ret_val = 0;
          end_flag = 1;
        }
      }
    }
  } else if (sign_1 == 0 && sign_2 == 1) {
    ret_val = 1;
  }
  return ret_val;
}
