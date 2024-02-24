#ifndef SRC_UTILS_S21_UTILS_H_
#define SRC_UTILS_S21_UTILS_H_

#include "s21_decimal.h"

// decimal

void s21_decimal_set_bit(s21_decimal *dst, int index, int bit);
void s21_decimal_set_zero(s21_decimal *dst);
void s21_decimal_set_sign(s21_decimal *dst, int sign);
void s21_decimal_set_scale(s21_decimal *dst, int exp);

int s21_decimal_get_bit(s21_decimal dst, int index);
int s21_decimal_get_scale(s21_decimal src);
int s21_decimal_get_sign(s21_decimal vl);
bool s21_decimal_get_sign_bool(s21_decimal dec);

int s21_convert_to_same_scale(s21_decimal *vl_1, s21_decimal *vl_2, int round);
int s21_scale_shifter(s21_decimal *vl, int shift, int round);

void s21_decimal_invert_sign(s21_decimal *dst);
int s21_decimal_is_zero(s21_decimal dec);
void s21_decimal_rescale(s21_decimal *value_1, s21_decimal *value_2);

// dbl_decimal

int s21_sub_dbl_decimal(s21_dbl_decimal dbl_dec_value_1,
                        s21_dbl_decimal dbl_dec_value_2,
                        s21_dbl_decimal *dbl_dec_result);
int s21_add_dbl_decimal(s21_dbl_decimal dbl_dec_value_1,
                        s21_dbl_decimal dbl_dec_value_2,
                        s21_dbl_decimal *dbl_dec_result);
int s21_mul_dbl_decimal(s21_dbl_decimal dbl_dec_value_1,
                        s21_dbl_decimal dbl_dec_value_2,
                        s21_dbl_decimal *dbl_dec_result);
int s21_div_dbl_decimal(s21_dbl_decimal dbl_dec_value_1,
                        s21_dbl_decimal dbl_dec_value_2,
                        s21_dbl_decimal *dbl_dec_result);
int s21_mod_dbl_decimal(s21_dbl_decimal dbl_dec_value_1,
                        s21_dbl_decimal dbl_dec_value_2,
                        s21_dbl_decimal *dbl_dec_result);

void s21_dbl_decimal_right_shift(s21_dbl_decimal *dbl_dec);
void s21_dbl_decimal_left_shift(s21_dbl_decimal *dbl_dec);

void s21_dbl_decimal_set_zero(s21_dbl_decimal *dbl_dec);

s21_dbl_decimal s21_decimal_to_dbl_decimal(s21_decimal dec);
s21_decimal s21_dbl_decimal_to_decimal(s21_dbl_decimal dbl_dec);

void s21_decimal_rescale_dbl_dec(s21_dbl_decimal *dbl_dec_value_1,
                                 s21_dbl_decimal *dbl_dec_value_2);
void s21_dbl_decimal_rescale_bank_rounding(s21_dbl_decimal *dbl_dec_value_1,
                                           s21_dbl_decimal *dbl_dec_value_2);

int s21_dbl_decimal_mod_by_ten(s21_dbl_decimal *dbl_dec);

bool s21_dbl_decimal_compare_bits(s21_dbl_decimal dbl_dec1,
                                  s21_dbl_decimal dbl_dec2);
bool s21_dbl_decimal_is_zero(s21_dbl_decimal dbl_dec);
int s21_dbl_decimal_highest_bit(s21_dbl_decimal dbl_dec);

void s21_dbl_decimal_bank_rounding(s21_dbl_decimal *dbl_dec, int mod);

void s21_dbl_decimal_align(s21_dbl_decimal *dbl_dec1,
                           s21_dbl_decimal *dbl_dec2);

void s21_dbl_decimal_rescale_to_zero(s21_dbl_decimal *dbl_dec_value_1,
                                     s21_dbl_decimal *dbl_dec_value_2);

s21_dbl_decimal s21_dbl_decimal_simple_div(s21_dbl_decimal dbl_dec_value_1,
                                           s21_dbl_decimal dbl_dec_value_2,
                                           s21_dbl_decimal *dbl_dec_result);

void s21_dbl_decimal_truncate(s21_dbl_decimal *dbl_dec_value);

// int

bool s21_int_get_bit(unsigned int num, int pos);

#endif  // SRC_UTILS_S21_UTILS_H_
