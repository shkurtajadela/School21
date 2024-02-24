#include "../s21_decimal.h"

// decimal --> float
// 0 - successful
// 1 - error

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int ans = 0;
  if (dst != NULL) {
    (*dst) = 0;
    int bin_exp = 95;
    for (int j = 2; j >= 0; j--) {
      for (int i = 31; i >= 0; i--) {
        int bin = (src.bits[j] >> i) & 1;
        float scale = pow(2, bin_exp);
        bin_exp--;
        (*dst) += bin * scale;
      }
    }
    int exp = src.bits[3];
    if (exp & (1 << 31U)) {
      (*dst) *= -1;
      exp &= ~(1u << 31);
    }
    exp >>= 16u;
    (*dst) = ((*dst) / pow(10, exp));
  } else {
    ans = 1;
  }
  return ans;
}
