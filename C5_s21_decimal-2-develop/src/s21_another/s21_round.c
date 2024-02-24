#include "../s21_decimal.h"

// 0 - successful
// 1- error

int s21_round(s21_decimal value, s21_decimal *result) {
  int ret_val = 0;
  if (result == NULL) {
    ret_val = 1;
  } else {
    int scale = s21_decimal_get_scale(value);
    if ((scale >= 0) && (scale <= 28)) {
      *result = value;
      if (scale > 0) {
        s21_scale_shifter(result, -scale, 2);
      }
    } else {
      ret_val = 1;
    }
  }
  return ret_val;
}
