#include "s21_tests.h"

START_TEST(is_neq_1) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(5, &val2);

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 0);
}
END_TEST

START_TEST(is_neq_2) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(2, &val1);
  s21_from_int_to_decimal(5, &val2);

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_neq_3) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(2, &val2);

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_neq_4) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-5, &val1);
  s21_from_int_to_decimal(-5, &val2);

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 0);
}
END_TEST

START_TEST(is_neq_5) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-2, &val1);
  s21_from_int_to_decimal(-5, &val2);

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_neq_6) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-5, &val1);
  s21_from_int_to_decimal(-2, &val2);

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

// ref tests
START_TEST(is_not_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_8) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_9) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_10) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_11) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_12) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_not_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_not_equal_13) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, -2147483648}};
  int flag = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(is_not_equal_14) {
  s21_decimal num1 = {{1, 0, 0, -2147483648}};
  s21_decimal num2 = {{1, 0, 0, 0}};
  int flag = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_not_equal_15) {
  s21_decimal num1 = {{3, 2, 1, 0}};
  s21_decimal num2 = {{3, 2, 1, 0}};
  int flag = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(is_not_equal_16) {
  s21_decimal num1 = {{4, 2, 1, 0}};
  s21_decimal num2 = {{3, 2, 1, 0}};
  int flag = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_not_equal_17) {
  s21_decimal num1 = {{4, 2, 1, 65536}};
  s21_decimal num2 = {{4, 2, 1, 0}};
  int flag1 = s21_is_not_equal(num1, num2);
  int flag2 = s21_is_not_equal(num2, num1);
  ck_assert_int_eq(flag1, 1);
  ck_assert_int_eq(flag2, 1);
}
END_TEST

START_TEST(is_not_equal_18) {
  s21_decimal num1 = {{4, 2, 1, 65536}};
  s21_decimal num2 = {{4, 3, 1, 0}};
  int flag1 = s21_is_not_equal(num1, num2);
  int flag2 = s21_is_not_equal(num2, num1);
  ck_assert_int_eq(flag1, 1);
  ck_assert_int_eq(flag2, 1);
}
END_TEST

START_TEST(is_not_equal_19) {
  s21_decimal num1 = {{44, 369, 1687, 65536}};
  s21_decimal num2 = {{44, 369, 1687, 65536}};
  int flag1 = s21_is_not_equal(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

Suite *suite_is_not_equal(void) {
  Suite *s = suite_create("\033[45m-=S21_IS_NOT_EQUAL=-\033[0m");
  TCase *tc = tcase_create("is_not_equal_tc");

  tcase_add_test(tc, is_neq_1);
  tcase_add_test(tc, is_neq_2);
  tcase_add_test(tc, is_neq_3);
  tcase_add_test(tc, is_neq_4);
  tcase_add_test(tc, is_neq_5);
  tcase_add_test(tc, is_neq_6);

  // ref tests
  tcase_add_test(tc, is_not_equal_1);
  tcase_add_test(tc, is_not_equal_2);
  tcase_add_test(tc, is_not_equal_3);
  tcase_add_test(tc, is_not_equal_4);
  tcase_add_test(tc, is_not_equal_5);
  tcase_add_test(tc, is_not_equal_6);
  tcase_add_test(tc, is_not_equal_7);
  tcase_add_test(tc, is_not_equal_8);
  tcase_add_test(tc, is_not_equal_9);
  tcase_add_test(tc, is_not_equal_10);
  tcase_add_test(tc, is_not_equal_11);
  tcase_add_test(tc, is_not_equal_12);
  tcase_add_test(tc, is_not_equal_13);
  tcase_add_test(tc, is_not_equal_14);
  tcase_add_test(tc, is_not_equal_15);
  tcase_add_test(tc, is_not_equal_16);
  tcase_add_test(tc, is_not_equal_17);
  tcase_add_test(tc, is_not_equal_18);
  tcase_add_test(tc, is_not_equal_19);

  suite_add_tcase(s, tc);
  return s;
}
