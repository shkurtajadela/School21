#include "tests/s21_tests.h"

int main(void) {
  int failed = 0;

  Suite *s21_decimal_test[] = {suite_from_int_to_decimal(),
                               test_s21_from_decimal_to_int(),
                               suite_from_decimal_to_float(),
                               test_21_from_float_to_decimal(),
                               test_s21_is_greater(),
                               suite_is_greater_or_equal(),
                               suite_is_equal(),
                               suite_is_not_equal(),
                               suite_is_less(),
                               suite_is_less_or_equal(),
                               test_S21_negate(),
                               suite_truncate(),
                               test_s21_round(),
                               suite_floor(),
                               suite_add(),
                               suite_mul(),
                               test_21_sub(),
                               suite_div(),
                               test_21_mod(),
                               s21_NULL};

  for (int i = 0; s21_decimal_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *runner = srunner_create(s21_decimal_test[i]);

    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);

    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
