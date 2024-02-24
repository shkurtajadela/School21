#include "../s21_decimal.h"

// 0 - successful
// 1 - too large or equal to infinity
// 2 - too little or equal to negative infinity

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  s21_decimal_rescale(&value_1, &value_2);
  s21_dbl_decimal dbl_dec_value_1 = s21_decimal_to_dbl_decimal(value_1);
  s21_dbl_decimal dbl_dec_value_2 = s21_decimal_to_dbl_decimal(value_2);
  s21_dbl_decimal dbl_dec_result;
  s21_dbl_decimal_set_zero(&dbl_dec_result);
  if (dbl_dec_value_1.sign == dbl_dec_value_2.sign) {
    return_code =
        s21_add_dbl_decimal(dbl_dec_value_1, dbl_dec_value_2, &dbl_dec_result);
  } else {
    if (dbl_dec_value_1.sign) {
      dbl_dec_value_1.sign = 0;
      value_1 = s21_dbl_decimal_to_decimal(dbl_dec_value_1);
      return_code = s21_sub(value_2, value_1, result);
      dbl_dec_result = s21_decimal_to_dbl_decimal(*result);
    } else {
      dbl_dec_value_2.sign = 0;
      value_2 = s21_dbl_decimal_to_decimal(dbl_dec_value_2);
      return_code = s21_sub(value_1, value_2, result);
      dbl_dec_result = s21_decimal_to_dbl_decimal(*result);
    }
  }
  *result = s21_dbl_decimal_to_decimal(dbl_dec_result);
  return return_code;
}
