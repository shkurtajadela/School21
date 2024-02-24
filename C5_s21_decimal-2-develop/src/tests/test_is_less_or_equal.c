#include "s21_tests.h"

START_TEST(is_less_eq_1) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(5, &val2);

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_less_eq_2) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(2, &val1);
  s21_from_int_to_decimal(5, &val2);

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_less_eq_3) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(2, &val2);

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 0);
}
END_TEST

START_TEST(is_less_eq_4) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-5, &val1);
  s21_from_int_to_decimal(-5, &val2);

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_less_eq_5) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-2, &val1);
  s21_from_int_to_decimal(-5, &val2);

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 0);
}
END_TEST

START_TEST(is_less_eq_6) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-5, &val1);
  s21_from_int_to_decimal(-2, &val2);

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_9) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_10) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_11) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_less_or_equal(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_12) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_or_equal_13) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_less_or_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

Suite *suite_is_less_or_equal(void) {
  Suite *s = suite_create("\033[45m-=S21_IS_LESS_OR_EQUAL=-\033[0m");
  TCase *tc = tcase_create("is_less_or_equal_tc");

  tcase_add_test(tc, is_less_eq_1);
  tcase_add_test(tc, is_less_eq_2);
  tcase_add_test(tc, is_less_eq_3);
  tcase_add_test(tc, is_less_eq_4);
  tcase_add_test(tc, is_less_eq_5);
  tcase_add_test(tc, is_less_eq_6);

  // ref tests
  tcase_add_test(tc, is_less_or_equal_1);
  tcase_add_test(tc, is_less_or_equal_2);
  tcase_add_test(tc, is_less_or_equal_3);
  tcase_add_test(tc, is_less_or_equal_4);
  tcase_add_test(tc, is_less_or_equal_5);
  tcase_add_test(tc, is_less_or_equal_6);
  tcase_add_test(tc, is_less_or_equal_7);
  tcase_add_test(tc, is_less_or_equal_8);
  tcase_add_test(tc, is_less_or_equal_9);
  tcase_add_test(tc, is_less_or_equal_10);
  tcase_add_test(tc, is_less_or_equal_11);
  tcase_add_test(tc, is_less_or_equal_12);
  tcase_add_test(tc, is_less_or_equal_13);

  suite_add_tcase(s, tc);
  return s;
}
