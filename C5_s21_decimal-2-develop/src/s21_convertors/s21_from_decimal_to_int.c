#include "../s21_decimal.h"

// decimal --> int
// 0 - successful
// 1- error

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int ans = 0;
  if (dst == NULL || src.bits[1] || src.bits[2]) {
    ans = 1;
  } else {
    if (s21_decimal_is_zero(src)) {
      (*dst) = 0;
    } else {
      int num = src.bits[0];
      int exp = src.bits[3];
      if (s21_decimal_get_sign(src)) {
        num *= -1;
        exp &= ~(1u << 31);
      }
      exp >>= 16u;
      (*dst) = (num / pow(10, exp));
    }
  }
  return ans;
}
