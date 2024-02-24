#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s21_NULL ((void *)0)
#define DEC_MIN -1 * DEC_MAX
#define s21_MAX_UINT 4294967295
#define DEC_MAX powl(2.0, 96)

typedef struct {
  uint32_t bits[4];
} s21_decimal;

typedef struct {
  uint32_t bits[8];
} s21_big_decimal;

typedef struct {
  int plus_inf;
  int minus_inf;
  int nan;
} s21_error_type;

typedef struct s21_dbl_decimal {
  bool bits[192];
  bool sign;
  int scale;
} s21_dbl_decimal;

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison operators

int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// Converters

int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Other

int s21_round(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#include "s21_auxiliary.h"

#endif  //  SRC_S21_DECIMAL_H_
