#include "s21_tests.h"

START_TEST(test_negate_operation_null) {
  s21_decimal tmp_1;
  ck_assert_float_eq(s21_negate(tmp_1, NULL), 1);
}
END_TEST

START_TEST(test_negate_operation_overflow) {
  s21_decimal tmp_1;
  s21_decimal_set_scale(&tmp_1, 29);
  ck_assert_float_eq(s21_negate(tmp_1, &tmp_1), 1);
}
END_TEST

Suite *test_S21_negate(void) {
  Suite *suite = suite_create("\033[45m-=S21_NEGATE=-\033[0m");

  TCase *tcase_core = tcase_create("S21_NEGATE TESTS");
  tcase_add_test(tcase_core, test_negate_operation_null);
  tcase_add_test(tcase_core, test_negate_operation_overflow);
  suite_add_tcase(suite, tcase_core);

  return suite;
}
