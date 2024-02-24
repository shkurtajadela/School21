#include "../helpers/s21_helpfunc.h"
#include "../s21_decimal.h"
#include "s21_comparison.h"

int is_greater_M(s21_decimal el1, s21_decimal el2) {
  int res = decCmp_M(el1, el2);
  return res > 0 ? 1 : 0;
}
int is_greater_or_equal_M(s21_decimal el1, s21_decimal el2) {
  int res = decCmp_M(el1, el2);
  return (res >= 0) ? 1 : 0;
}

int is_equal_M(s21_decimal el1, s21_decimal el2) {
  int res = decCmp_M(el1, el2);
  return res == 0 ? 1 : 0;
}

int decCmp_M(s21_decimal el1, s21_decimal el2) {
  int res = 0;

  if (check_zero(el1)) {
    setSign(&el1, 1);
  }
  if (check_zero(el2)) {
    setSign(&el2, 1);
  }
  int sign1 = getSign(el1), sign2 = getSign(el2);
  if ((isInf(&el1) == 1 && isInf(&el2) == 0) ||
      (isInf(&el1) == 0 && isInf(&el2) == -1) ||
      (sign1 > sign2)) {  //  первый точно больше
    res = 1;
  } else if ((isInf(&el1) == 0 && isInf(&el2) == 1) ||
             (isInf(&el1) == -1 && isInf(&el2) == 0) ||
             (sign1 < sign2)) {  //  второй точно больше
    res = -1;
  } else {
    res = 0;
    for (int i = 95; i >= 0 && res == 0;
         --i) {  //  сравниваем мантисы побитово, пока равны
      int cur_bit1 = getBit(el1, i), cur_bit2 = getBit(el2, i);
      if (cur_bit1 != cur_bit2) {
        res = cur_bit1 - cur_bit2;
      }
    }
    if (sign1 == -1) {  //  инвертируем, если оба отрицательные
      res = -res;
    }
  }
  return res;
}