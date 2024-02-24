#ifndef SRC_S21_ARITHMETIC_S21_ARITHMETIC_H_
#define SRC_S21_ARITHMETIC_S21_ARITHMETIC_H_

#include "../helpers/s21_helpfunc.h"
#include "../s21_another/s21_another.h"
#include "../s21_comparison/s21_comparison.h"
#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// arithmetic helpers
int makeNegInf(s21_decimal *el);

int makeNan(s21_decimal *el);

int makeInf(s21_decimal *el);
void makeResult(s21_error_type error, s21_decimal *result);
//// casscurs

int find_one(s21_decimal bit, int *pos);

s21_decimal leftshift(s21_decimal bit);

s21_decimal bank_round(s21_decimal bit);

int is_uneven(s21_decimal bit);

int check_zero(s21_decimal decimal);

void degree_of_two(s21_decimal *num, int degree);

// sub
int s21_bit_sub(s21_decimal bit1, s21_decimal bit2, s21_decimal *res);

void one_zero_pattern(int *mindone, s21_decimal *res, int j);

void and_pattern(int *mindone, s21_decimal *res, int j);

void zero_one_pattern(int *mindone, s21_decimal *res, int j);

void positive_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                  int power);
void Light_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// div
int s21_bit_division(s21_decimal delim, s21_decimal delit, s21_decimal *chast);

void div_first_decrement(s21_decimal delim, s21_decimal delit,
                         s21_decimal *delitBuf, s21_decimal *chast);

void div_second_decrement(s21_decimal delit, s21_decimal *delitBuf,
                          s21_decimal *chast, s21_decimal *razn);

// mod
void s21_bit_mod(s21_decimal delim, s21_decimal delit, s21_decimal *ostatok);

//// aquaman

int s21_add_for_mul(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);

void subIn_s21_add(s21_decimal *value_1, s21_decimal *value_2,
                   s21_decimal *result, int power_value1);

void addition_for_mul(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result);

void setMaxDecimal(s21_decimal *result);
void positive_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                  int power);

int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             int *power);
void multiplication(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);

int checkErrorAdd(const s21_decimal value_1, const s21_decimal value_2,
                  s21_error_type *error);

int checkErrorMul(const s21_decimal value_1, const s21_decimal value_2,
                  s21_error_type *error);

int checkErrorDiv(const s21_decimal value_1, const s21_decimal value_2,
                  s21_error_type *error);

//
int v1_greater_v2(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                  int power);
int v2_greater_v1(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                  int power);
int s21_bit_sub(s21_decimal bit1, s21_decimal bit2, s21_decimal *res);

void one_zero_pattern(int *mindone, s21_decimal *res, int j);

void and_pattern(int *mindone, s21_decimal *res, int j);

void zero_one_pattern(int *mindone, s21_decimal *res, int j);
int s21_bit_sub(s21_decimal bit1, s21_decimal bit2, s21_decimal *res);

int checkForOverflow(s21_decimal value_1, s21_decimal value_2);

void setSignIn_s21_add(s21_decimal *value_1, s21_decimal *value_2,
                       s21_decimal *result);

void setSign(s21_decimal *decimal, int sign);

void setPowerIn_s21_add(int power_value1, s21_decimal *result,
                        int overflow_status);

int getAroundOverflow_s21_add(s21_decimal *value_1, s21_decimal *value_2,
                              s21_decimal *result, int index, int cases,
                              int *power);

int makePower(s21_decimal value_1, s21_decimal value_2);

// ниже функции для бигдецимал - все они сами в s21_mul
void additionBigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);
int find_oneBigDecimal(s21_big_decimal bit, int *pos);
s21_big_decimal leftshiftBigDecimal(s21_big_decimal bit);
int setBitBigDecimal(s21_big_decimal *decimal, int index, int value);
int getBitBigDecimal(s21_big_decimal decimal, int index);
void nullBigDecimal(s21_big_decimal *value);
int bigDecimalToDecimal(s21_big_decimal value, s21_decimal *result,
                        int power_result);
s21_big_decimal decimalToBigDecimal(s21_decimal value);
int multiplicationBigDecimal(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2, s21_decimal *result,
                             int power_result);
// ОТКРЫВАЙТЕ ФОРТОЧКУ
void zero_one_patternBigDecimal(int *mindone, s21_big_decimal *res, int j);
void and_patternBigDecimal(int *mindone, s21_big_decimal *res, int j);
void one_zero_patternBigDecimal(int *mindone, s21_big_decimal *res, int j);
int s21_bit_subBigDecimal(s21_big_decimal bit1, s21_big_decimal bit2,
                          s21_big_decimal *res);
int decCmp_MBigDecimal(s21_big_decimal el1, s21_big_decimal el2);
int is_equal_MBigDecimal(s21_big_decimal el1, s21_big_decimal el2);
int is_greater_MBigDecimal(s21_big_decimal el1, s21_big_decimal el2);
int is_greater_or_equal_MBigDecimal(s21_big_decimal el1, s21_big_decimal el2);

void Light_subBigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);
void degree_of_twoBigDeicmal(s21_big_decimal *num, int degree);
void div_second_decrementBigDeicmal(s21_big_decimal delit,
                                    s21_big_decimal *delitBuf,
                                    s21_big_decimal *chast,
                                    s21_big_decimal *razn);

void div_first_decrementBigDeicmal(s21_big_decimal delim, s21_big_decimal delit,
                                   s21_big_decimal *delitBuf,
                                   s21_big_decimal *chast);
int check_zeroBigDecimal(s21_big_decimal decimal);
int s21_bit_divisionBigDeicmal(s21_big_decimal delim, s21_big_decimal delit,
                               s21_big_decimal *chast);
int is_unevenBigDeicmal(s21_big_decimal bit);
void s21_bit_modBigDeicmal(s21_big_decimal delim, s21_big_decimal delit,
                           s21_big_decimal *ostatok);
s21_big_decimal bank_roundBigDeicmal(s21_big_decimal bit);
s21_big_decimal simpleMultiplicationBigDecimal(s21_big_decimal big_value_1,
                                               s21_big_decimal big_value_2);
void positive_subBigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result, int power);
int v1_greater_v2BigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result, int power);
int v2_greater_v1BigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result, int power);
int setPowerBigDecimal(s21_big_decimal *dec, int power);
void clearPowerBigDecimal(s21_big_decimal *dec);
int getSignBigDecimal(s21_big_decimal decimal);
void setSignBigDecimal(s21_big_decimal *decimal, int sign);
int getPowerBigDecimal(s21_big_decimal dec);
int isInfBigDecimal(const s21_big_decimal *el);

#endif  // SRC_S21_ARITHMETIC_S21_ARITHMETIC_H_
