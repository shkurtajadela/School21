#include "s21_tests.h"

START_TEST(s21_floor_positive_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 7;
  s21_decimal test = {{7}};
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(getSign(result), 1);
  ck_assert_int_eq(s21_result, 0);
}
END_TEST

START_TEST(s21_floor_null) {
  s21_decimal *result = NULL;
  s21_decimal value = {0};
  int s21_result = s21_floor(value, result);
  ck_assert_int_eq(s21_result, 1);
}
END_TEST

START_TEST(s21_floor_negative_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 12;
  s21_decimal test = {{12}};
  setBit(&value, 127, 1);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(getSign(result), -1);
  ck_assert_int_eq(s21_result, 0);
}
END_TEST

START_TEST(s21_floor_positive_non_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 2463;
  s21_decimal test = {{2}};
  setPower(&value, 3);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(getSign(result), 1);
  ck_assert_int_eq(s21_result, 0);
}
END_TEST

START_TEST(s21_floor_negative_non_integer) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  value.bits[0] = 2463;
  s21_decimal test = {{3}};
  setSign(&value, -1);
  setPower(&value, 3);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(getSign(result), -1);
  ck_assert_int_eq(s21_result, 0);
}
END_TEST

START_TEST(s21_floor_inf) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  s21_decimal test = {0};
  makeInf(&value);
  makeInf(&test);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(value, result), 1);
  ck_assert_int_eq(getSign(result), 1);
  ck_assert_int_eq(s21_result, 0);
}
END_TEST

START_TEST(s21_floor_negative_inf) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  s21_decimal test = {0};
  makeInf(&value);
  makeInf(&test);
  setSign(&value, -1);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(value, result), 1);
  ck_assert_int_eq(getSign(result), -1);
  ck_assert_int_eq(s21_result, 0);
}
END_TEST

START_TEST(s21_floor_nan) {
  s21_decimal result = {0};
  s21_decimal value = {0};
  s21_decimal test = {0};
  makeNan(&value);
  makeNan(&test);
  int s21_result = s21_floor(value, &result);
  ck_assert_int_eq(s21_is_equal(value, result), 1);
  ck_assert_int_eq(getSign(result), 1);
  ck_assert_int_eq(s21_result, 1);
}
END_TEST

Suite *suite_floor(void) {
  Suite *s = suite_create("\033[45m-=S21_FLOOR=-\033[0m");
  TCase *tc = tcase_create("floor_tc");

  tcase_add_test(tc, s21_floor_positive_integer);
  tcase_add_test(tc, s21_floor_null);
  tcase_add_test(tc, s21_floor_negative_integer);
  tcase_add_test(tc, s21_floor_positive_non_integer);
  tcase_add_test(tc, s21_floor_negative_non_integer);

  tcase_add_test(tc, s21_floor_inf);

  tcase_add_test(tc, s21_floor_negative_inf);
  tcase_add_test(tc, s21_floor_nan);

  suite_add_tcase(s, tc);
  return s;
}
