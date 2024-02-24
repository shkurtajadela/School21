#include "s21_tests.h"

START_TEST(int_fpos_mod) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_int_to_decimal(72, &value_1);
  s21_from_int_to_decimal(3, &value_2);
  s21_bit_mod(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(72 % 3, result_fl);
}
END_TEST

START_TEST(int_pos_mod) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_float_to_decimal(5, &value_1);
  s21_from_float_to_decimal(5, &value_2);
  s21_bit_mod(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(5 % 5, result_fl);
}
END_TEST

START_TEST(int_neg_mod) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_float_to_decimal(6, &value_1);
  s21_from_float_to_decimal(-2, &value_2);
  s21_bit_mod(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(6 % -2, result_fl);
}
END_TEST

START_TEST(float_pos_mod) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_float_to_decimal(12323, &value_1);
  s21_from_float_to_decimal(231, &value_2);
  s21_bit_mod(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(12323 % 231, result_fl);
}
END_TEST

START_TEST(float_neg_mod) {
  s21_decimal value_1, value_2, result;
  float result_fl;
  s21_from_float_to_decimal(12554, &value_1);
  s21_from_float_to_decimal(-231, &value_2);
  s21_bit_mod(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_fl);
  ck_assert_float_eq(12554 % -231, result_fl);
}
END_TEST

START_TEST(mixed_pos_mod) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_int_to_decimal(214748, &value_1);
  s21_from_float_to_decimal(5, &value_2);
  s21_bit_mod(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(214748 % 5, result_float);
}
END_TEST

START_TEST(too_big_mod) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_float_to_decimal(21474, &value_1);
  s21_from_float_to_decimal(1231, &value_2);
  s21_bit_mod(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_float_eq_tol(21474 % 1231, result_float, 1e-5);
}
END_TEST

START_TEST(too_small_mod) {
  s21_decimal value_1, value_2, result;
  float result_float;
  s21_from_float_to_decimal(123124, &value_1);
  s21_from_float_to_decimal(125151, &value_2);
  s21_bit_mod(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_float_eq_tol(123124 % 125151, result_float, 1e-5);
}
END_TEST

Suite *test_21_mod(void) {
  Suite *suite = suite_create("\033[45m-=S21_MOD=-\033[0m");
  TCase *tcase_core = tcase_create("CORE TESTS");

  tcase_add_test(tcase_core, int_fpos_mod);
  tcase_add_test(tcase_core, int_pos_mod);
  tcase_add_test(tcase_core, int_neg_mod);
  tcase_add_test(tcase_core, float_pos_mod);
  tcase_add_test(tcase_core, float_neg_mod);
  tcase_add_test(tcase_core, mixed_pos_mod);
  tcase_add_test(tcase_core, too_big_mod);
  tcase_add_test(tcase_core, too_small_mod);

  suite_add_tcase(suite, tcase_core);

  return suite;
}