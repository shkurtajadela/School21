#include "s21_tests.h"

START_TEST(int_pos_sub) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_float_to_decimal(5, &value_1);
  s21_from_int_to_decimal(2, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(5 - 2, result_fl);
}
END_TEST

START_TEST(int_neg_sub) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_float_to_decimal(5, &value_1);
  s21_from_int_to_decimal(-2, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(5 + 2, result_fl);
}
END_TEST

START_TEST(float_pos_sub) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_float_to_decimal(123.23, &value_1);
  s21_from_float_to_decimal(23.1, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(123.23 - 23.1, result_fl);
}
END_TEST

START_TEST(float_neg_sub) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_float_to_decimal(123.23, &value_1);
  s21_from_float_to_decimal(-23.1, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(123.23 + 23.1, result_fl);
}
END_TEST

START_TEST(mixed_pos_sub) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(214748, &value_1);
  s21_from_float_to_decimal(0.5, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(214748 - 0.5, result_float);
}
END_TEST

START_TEST(mixed_neg_sub) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(214748, &value_1);
  s21_from_float_to_decimal(-0.5, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(214748 + 0.5, result_float);
}
END_TEST

START_TEST(loan_of_a_discharge) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(123801.012, &value_1);
  s21_from_float_to_decimal(987.4, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(123801.012 - 987.4, result_float);
}
END_TEST

START_TEST(simple_negative_positive) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(-53150.901, &value_1);
  s21_from_float_to_decimal(23.0931, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(-53150.901 - 23.0931, result_float);
}
END_TEST

START_TEST(simple_positive_negative) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(82642.032, &value_1);
  s21_from_float_to_decimal(-19330, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(82642.032 + 19330, result_float);
}
END_TEST

START_TEST(simple_positive_positive_1) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(35664.0251, &value_1);
  s21_from_float_to_decimal(893.1, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(35664.0251 - 893.1, result_float);
}
END_TEST

START_TEST(simple_positive_positive_2) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(893.1, &value_1);
  s21_from_float_to_decimal(35664.3251, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(893.1 - 35664.3251, result_float);
}
END_TEST

START_TEST(simple_negative_negative_1) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(-99991.0, &value_1);
  s21_from_float_to_decimal(-1133132.0, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(-99991.0 + 1133132.0, result_float);
}
END_TEST

START_TEST(simple_negative_negative_2) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(-1133132.0, &value_1);
  s21_from_float_to_decimal(-99991.0, &value_2);
  s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(-1133132.0 + 99991.0, result_float);
}
END_TEST

START_TEST(overflow_of_the_mantissa) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_decimal_set_zero(&value_1);
  value_1.bits[0] = 2701131776;
  value_1.bits[1] = 466537709;
  value_1.bits[2] = 54210;
  s21_from_float_to_decimal(0.1111111, &value_2);
  int error = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_float_eq_tol(1e+24, result_float, 1e17);
}
END_TEST

Suite *test_21_sub(void) {
  Suite *suite = suite_create("\033[45m-=S21_SUB=-\033[0m");

  TCase *tcase_core = tcase_create("S21_SUB TESTS");

  tcase_add_test(tcase_core, int_pos_sub);
  tcase_add_test(tcase_core, int_neg_sub);
  tcase_add_test(tcase_core, float_pos_sub);
  tcase_add_test(tcase_core, float_neg_sub);
  tcase_add_test(tcase_core, mixed_pos_sub);
  tcase_add_test(tcase_core, mixed_neg_sub);
  tcase_add_test(tcase_core, loan_of_a_discharge);
  tcase_add_test(tcase_core, simple_negative_positive);
  tcase_add_test(tcase_core, simple_positive_negative);
  tcase_add_test(tcase_core, simple_positive_positive_1);
  tcase_add_test(tcase_core, simple_positive_positive_2);
  tcase_add_test(tcase_core, simple_negative_negative_1);
  tcase_add_test(tcase_core, simple_negative_negative_2);
  tcase_add_test(tcase_core, overflow_of_the_mantissa);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
