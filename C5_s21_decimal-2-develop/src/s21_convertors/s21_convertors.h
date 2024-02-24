#ifndef SRC_S21_CONVERTORS_S21_CONVERTORS_H_
#define SRC_S21_CONVERTORS_S21_CONVERTORS_H_

#include "../helpers/s21_helpfunc.h"
#include "../s21_decimal.h"

// convertors
////
int s21_from_int_to_decimal(int src, s21_decimal *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);

int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_from_float_to_decimal(float src, s21_decimal *dst);
////

#endif  // SRC_S21_CONVERTORS_S21_CONVERTORS_H_