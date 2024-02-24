#include "s21_tests.h"

START_TEST(test1) {
  s21_decimal value_1 = {0};
  int a = -5;
  s21_decimal test = {{5}};
  s21_from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(value_1.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test2) {
  s21_decimal value_1 = {0};
  s21_decimal test = {0};
  int a = 0;
  s21_from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  ck_assert_int_eq(value_1.bits[3] >> 31, 0);
}
END_TEST

START_TEST(test3) {
  s21_decimal value_1 = {0};
  s21_decimal test = {0};
  int a = 123456;
  test.bits[0] = 123456;
  s21_from_int_to_decimal(a, &value_1);
  ck_assert_int_eq(value_1.bits[0], test.bits[0]);
  //   set_sign(&value_1);
}
END_TEST

START_TEST(from_int_to_decimal_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_long_1) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  long int tmp = 987654321234;
  int n = (int)tmp;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, n);
}
END_TEST

Suite *suite_from_int_to_decimal(void) {
  Suite *s = suite_create("\033[45m-=S21_FROM_INT_TO_DECIMAL=-\033[0m");
  TCase *tc = tcase_create("from_int_to_decimal_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);

  tcase_add_test(tc, from_int_to_decimal_0);
  tcase_add_test(tc, from_int_to_decimal_1);
  tcase_add_test(tc, from_int_to_decimal_long_1);

  suite_add_tcase(s, tc);
  return s;
}
