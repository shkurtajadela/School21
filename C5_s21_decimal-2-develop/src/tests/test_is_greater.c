#include "s21_tests.h"

START_TEST(test_greater_operation_neg_zero) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  s21_decimal_set_zero(&tmp_2);
  int err = s21_from_float_to_decimal(-124.51, &tmp_1);
  ck_assert_float_eq(err, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 0);
}
END_TEST

START_TEST(test_greater_operation_zero_zero) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  s21_decimal_set_zero(&tmp_2);
  int err = s21_from_float_to_decimal(0, &tmp_1);
  ck_assert_float_eq(err, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 0);
}
END_TEST

START_TEST(test_greater_operation_max_zero) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  s21_decimal_set_zero(&tmp_2);
  int err = s21_from_float_to_decimal(DEC_MAX, &tmp_1);
  ck_assert_float_eq(err, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 1);
}
END_TEST

START_TEST(test_greater_operation_zero_min) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  s21_decimal_set_zero(&tmp_1);
  int err = s21_from_float_to_decimal(DEC_MIN, &tmp_2);
  ck_assert_float_eq(err, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 1);
}
END_TEST

START_TEST(test_greater_operation_max_min) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  int err_1 = s21_from_float_to_decimal(DEC_MAX, &tmp_1);
  int err_2 = s21_from_float_to_decimal(DEC_MIN, &tmp_2);
  ck_assert_float_eq(err_1, 0);
  ck_assert_float_eq(err_2, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 1);
}
END_TEST

START_TEST(test_greater_operation_pos_pos) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  int err_1 = s21_from_float_to_decimal(123.456, &tmp_1);
  int err_2 = s21_from_float_to_decimal(123.45, &tmp_2);
  ck_assert_float_eq(err_1, 0);
  ck_assert_float_eq(err_2, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 1);
}
END_TEST

START_TEST(test_greater_operation_neg_neg) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  int err_1 = s21_from_float_to_decimal(-2178.95, &tmp_1);
  int err_2 = s21_from_float_to_decimal(-2178.954, &tmp_2);
  ck_assert_float_eq(err_1, 0);
  ck_assert_float_eq(err_2, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 1);
}
END_TEST

START_TEST(test_greater_operation_pos_neg) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  int err_1 = s21_from_float_to_decimal(589.068, &tmp_1);
  int err_2 = s21_from_float_to_decimal(-571.491, &tmp_2);
  ck_assert_float_eq(err_1, 0);
  ck_assert_float_eq(err_2, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 1);
}
END_TEST

START_TEST(test_greater_operation_zero_neg) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  int err_1 = s21_from_float_to_decimal(0, &tmp_1);
  int err_2 = s21_from_float_to_decimal(-589.19, &tmp_2);
  ck_assert_float_eq(err_1, 0);
  ck_assert_float_eq(err_2, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 1);
}
END_TEST

START_TEST(test_greater_operation_zero_pos) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  int err_1 = s21_from_float_to_decimal(0, &tmp_1);
  int err_2 = s21_from_float_to_decimal(589.19, &tmp_2);
  ck_assert_float_eq(err_1, 0);
  ck_assert_float_eq(err_2, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 0);
}
END_TEST

START_TEST(test_greater_operation_pos_zero) {
  s21_decimal tmp_1;
  s21_decimal tmp_2;
  int err_1 = s21_from_float_to_decimal(191.219, &tmp_1);
  int err_2 = s21_from_float_to_decimal(0, &tmp_2);
  ck_assert_float_eq(err_1, 0);
  ck_assert_float_eq(err_2, 0);
  ck_assert_float_eq(s21_is_greater(tmp_1, tmp_2), 1);
}
END_TEST

Suite *test_s21_is_greater(void) {
  Suite *suite = suite_create("\033[45m-=S21_IS_GREATER=-\033[0m");

  TCase *tcase_core = tcase_create("S21_IS_GREATER TESTS");
  tcase_add_test(tcase_core, test_greater_operation_neg_zero);
  tcase_add_test(tcase_core, test_greater_operation_zero_zero);
  tcase_add_test(tcase_core, test_greater_operation_max_zero);
  tcase_add_test(tcase_core, test_greater_operation_zero_min);
  tcase_add_test(tcase_core, test_greater_operation_max_min);
  tcase_add_test(tcase_core, test_greater_operation_pos_pos);
  tcase_add_test(tcase_core, test_greater_operation_neg_neg);
  tcase_add_test(tcase_core, test_greater_operation_pos_neg);
  tcase_add_test(tcase_core, test_greater_operation_zero_neg);
  tcase_add_test(tcase_core, test_greater_operation_zero_pos);
  tcase_add_test(tcase_core, test_greater_operation_pos_zero);
  suite_add_tcase(suite, tcase_core);

  return suite;
}
