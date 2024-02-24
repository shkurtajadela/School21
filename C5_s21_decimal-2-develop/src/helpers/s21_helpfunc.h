#ifndef SRC_HELPERS_S21_HELPFUNC_H_
#define SRC_HELPERS_S21_HELPFUNC_H_

#include "../s21_arithmetic/s21_arithmetic.h"
#include "../s21_comparison/s21_comparison.h"
#include "../s21_decimal.h"

//  bit opertions helpers
////
void memcheck(s21_decimal *result);

int getPower(s21_decimal dec);

void clearPower(s21_decimal *dec);

int getSign(s21_decimal decimal);

int setPower(s21_decimal *dec, int power);

int getBit(s21_decimal decimal, int index);

int subGetBit(uint32_t bits, int pos);

int setBit(s21_decimal *decimal, int index, int value);

//
void s21_powNormilize(s21_decimal *value1, s21_decimal *value2);

void powerValueTo28(s21_decimal *value, int power);

void powerValueToXUp(s21_decimal *value, int power, int *lesser_power);

void powerValueToXDown(s21_decimal *value, int *power_1, int power_2);

#endif  // SRC_HELPERS_S21_HELPFUNC_H_