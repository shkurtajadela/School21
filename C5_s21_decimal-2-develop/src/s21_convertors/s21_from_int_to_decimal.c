#include "../s21_decimal.h"

// int --> decimal
// 0 - successful
// 1 - error
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int ans = 0;
  if (dst != NULL) {
    s21_decimal_set_zero(dst);
    if (src < 0) {
      s21_decimal_set_sign(dst, 1);
    }
    dst->bits[0] = abs(src);
  } else {
    ans = 1;
  }
  return ans;
}
