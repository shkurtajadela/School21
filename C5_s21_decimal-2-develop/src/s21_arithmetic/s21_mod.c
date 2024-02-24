#include "../helpers/s21_helpfunc.h"
#include "../s21_decimal.h"
#include "s21_arithmetic.h"

void s21_bit_mod(s21_decimal delim, s21_decimal delit, s21_decimal *ostatok) {
  memcheck(ostatok);
  if (is_greater_M(delit, delim)) {
    *ostatok = delim;
  } else {
    s21_decimal buf = {0};
    s21_bit_division(delim, delit, &buf);
    multiplication(delit, buf, &buf);
    Light_sub(delim, buf, ostatok);
  }
}