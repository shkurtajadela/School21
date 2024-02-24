#include "../s21_decimal.h"

// 0 - successful
// 1- error

int s21_negate(s21_decimal value, s21_decimal *result) {
  int ret_val = 0;
  if (result == NULL) {
    ret_val = 1;
  } else {
    int scale = s21_decimal_get_scale(value);
    if ((scale >= 0) && (scale <= 28)) {
      result->bits[0] = value.bits[0];
      result->bits[1] = value.bits[1];
      result->bits[2] = value.bits[2];
      result->bits[3] = value.bits[3] ^ (1 << 31);  //  xor
    } else {
      ret_val = 1;
    }
  }
  return ret_val;
}
