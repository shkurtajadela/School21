#ifndef SRC_S21_ANOTHER_S21_ANOTHER_H_
#define SRC_S21_ANOTHER_S21_ANOTHER_H_

#include "../helpers/s21_helpfunc.h"
#include "../s21_arithmetic/s21_arithmetic.h"
#include "../s21_convertors/s21_convertors.h"
#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result);

int s21_floor(s21_decimal value, s21_decimal *result);

// another function helper

void protectedTruncate(s21_decimal value, s21_decimal *result);

void protectedRound(s21_decimal value, s21_decimal *result);

long double decimalToDouble(s21_decimal src, long double dst);

#endif  // SRC_S21_ANOTHER_S21_ANOTHER_H_
