#include "../s21_decimal.h"

// compares decimal1 == decimal2
// vl_1 == vl_2 = 1
// vl_1 != vl_2 = 0
int s21_is_equal(s21_decimal vl_1, s21_decimal vl_2) {
  int rt_vl = 0;
  s21_convert_to_same_scale(&vl_1, &vl_2, 0);
  if (vl_1.bits[0] == vl_2.bits[0] && vl_1.bits[1] == vl_2.bits[1] &&
      vl_1.bits[2] == vl_2.bits[2] && vl_1.bits[3] == vl_2.bits[3]) {
    rt_vl = 1;
  } else if (s21_decimal_is_zero(vl_1) && s21_decimal_is_zero(vl_2)) {
    rt_vl = 1;
  }
  return rt_vl;
}
