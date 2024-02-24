#include "s21_tests.h"

START_TEST(d_to_f_1) {
  s21_decimal value = {{8}};
  float a = 0;
  float b = 8.0;
  s21_from_decimal_to_float(value, &a);
  ck_assert_int_eq(getBit(value, 95), 0);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(d_to_f_2) {
  s21_decimal value = {0};
  float a = 0.0;
  float b = 0.0;
  s21_from_decimal_to_float(value, &a);
  ck_assert_int_eq(getBit(value, 95), 0);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(d_to_f_3) {
  s21_decimal value = {{8}};
  float a = 0.0;
  float b = -0.8;
  setPower(&value, 1);
  setBit(&value, 127, 1);  // negative
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(d_to_f_4) {
  s21_decimal value = {{8}};
  float a = 0.0;
  float b = -0.0000000000000000000000000008;
  setPower(&value, 28);
  setBit(&value, 127, 1);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(d_to_f_5) {
  s21_decimal value = {0};
  value.bits[0] = 147484107;
  float a = 0.0;
  float b = -1.47484107;
  setPower(&value, 8);
  setBit(&value, 127, 1);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(d_to_f_6) {
  s21_decimal value = {0};
  value.bits[0] = 214748;

  float a = 0.0;
  float b = -0.00000214748;
  setPower(&value, 11);
  setBit(&value, 127, 1);
  s21_from_decimal_to_float(value, &a);
  ck_assert_float_eq_tol(a, b, 1e-6);
}
END_TEST

START_TEST(from_decimal_to_float_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  setPower(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  setBit(&val, 127, 1);
  setPower(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(decimal_to_float_2) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = -3.14;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 314;
  number.bits[1] = 0;
  number.bits[2] = 0;
  number.bits[3] |= SIGN;
  setPower(&number, 2);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.7f", float_result);
  sprintf(s21_result, "%.7f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_3) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = -5792277640.493418938682;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 314;
  number.bits[1] = 314;
  number.bits[2] = 314;
  number.bits[3] |= SIGN;
  setPower(&number, 12);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_4) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = 5792277640.493418938682;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 314;
  number.bits[1] = 314;
  number.bits[2] = 314;
  setPower(&number, 12);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_5) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = 1980704062.8566084398385987584;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 0;
  number.bits[1] = 0;
  number.bits[2] = 1073741824;
  setPower(&number, 19);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_6) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = -1980704062.8566084398385987584;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 0;
  number.bits[1] = 0;
  number.bits[2] = 1073741824;
  number.bits[3] |= SIGN;
  setPower(&number, 19);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

START_TEST(decimal_to_float_7) {
  char s21_result[BUF];
  char result[BUF];
  memset(result, '\0', BUF);
  memset(s21_result, '\0', BUF);
  float float_result = -1980704063.3177770417887117312;
  float s21_float_result = 0;
  s21_decimal number = {0};
  number.bits[0] = 1073741824;
  number.bits[1] = 1073741824;
  number.bits[2] = 1073741824;
  number.bits[3] |= SIGN;
  setPower(&number, 19);
  s21_from_decimal_to_float(number, &s21_float_result);
  sprintf(result, "%.28f", float_result);
  sprintf(s21_result, "%.28f", s21_float_result);
  ck_assert_str_eq(result, s21_result);
}
END_TEST

Suite *suite_from_decimal_to_float(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_DECIMAL_TO_FLOAT=-\033[0m");
  TCase *tc = tcase_create("from_decimal_to_float_tc");

  tcase_add_test(tc, d_to_f_1);
  tcase_add_test(tc, d_to_f_2);
  tcase_add_test(tc, d_to_f_3);
  tcase_add_test(tc, d_to_f_4);
  tcase_add_test(tc, d_to_f_5);
  tcase_add_test(tc, d_to_f_6);

  tcase_add_test(tc, from_decimal_to_float_0);
  tcase_add_test(tc, from_decimal_to_float_1);
  tcase_add_test(tc, decimal_to_float_2);
  tcase_add_test(tc, decimal_to_float_3);
  tcase_add_test(tc, decimal_to_float_4);
  tcase_add_test(tc, decimal_to_float_5);
  tcase_add_test(tc, decimal_to_float_6);
  tcase_add_test(tc, decimal_to_float_7);

  suite_add_tcase(s, tc);
  return s;
}
