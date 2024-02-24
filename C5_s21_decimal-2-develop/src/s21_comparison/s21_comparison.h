#ifndef SRC_S21_COMPARISON_S21_COMPARISON_H_
#define SRC_S21_COMPARISON_S21_COMPARISON_H_

#include "../s21_arithmetic/s21_arithmetic.h"
#include "../s21_convertors/s21_convertors.h"
#include "../s21_decimal.h"

// comparations
////
int s21_is_less(s21_decimal, s21_decimal);

int s21_is_less_or_equal(s21_decimal, s21_decimal);

int s21_is_greater(s21_decimal, s21_decimal);

int s21_is_greater_or_equal(s21_decimal, s21_decimal);

int s21_is_equal(s21_decimal, s21_decimal);

int s21_is_not_equal(s21_decimal, s21_decimal);

// comparation helpers
int isInf(const s21_decimal *el);

int isNan(const s21_decimal *el);

int decCmp(s21_decimal el1, s21_decimal el2);

///
int decCmp_M(s21_decimal el1, s21_decimal el2);
int is_less_M(s21_decimal, s21_decimal);

int is_less_or_equal_M(s21_decimal, s21_decimal);

int is_greater_M(s21_decimal, s21_decimal);

int is_greater_or_equal_M(s21_decimal, s21_decimal);

int is_equal_M(s21_decimal, s21_decimal);

int is_not_equal_M(s21_decimal, s21_decimal);

#endif  // SRC_S21_COMPARISON_S21_COMPARISON_H_