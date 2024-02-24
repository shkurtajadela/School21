#include "s21_tests.h"

START_TEST(is_eq_1) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(5, &val2);

  ck_assert_int_eq(s21_is_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_eq_2) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(2, &val1);
  s21_from_int_to_decimal(5, &val2);

  ck_assert_int_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(is_eq_3) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(2, &val2);

  ck_assert_int_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(is_eq_4) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-5, &val1);
  s21_from_int_to_decimal(-5, &val2);

  ck_assert_int_eq(s21_is_equal(val1, val2), 1);
}
END_TEST

START_TEST(is_eq_5) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-2, &val1);
  s21_from_int_to_decimal(-5, &val2);

  ck_assert_int_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(is_eq_6) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-5, &val1);
  s21_from_int_to_decimal(-2, &val2);

  ck_assert_int_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{1747, 0, 1, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_8) {
  s21_decimal x = {{0, 0, 0, NEGATIVE}};
  s21_decimal y = {{1, 0, 0, 0}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_9) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, NEGATIVE}};

  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_10) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, NEGATIVE}};

  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_11) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_12) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_13) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_14) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_equal(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_15) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_equal(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_equal_16) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, -2147483648}};
  int flag = s21_is_equal(num1, num2);

  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_equal_17) {
  // Arrange
  s21_decimal num1 = {{0, 0, 0, -2147483648}};
  s21_decimal num2 = {{0, 0, 0, -2147483648}};
  // Act
  int flag = s21_is_equal(num1, num2);
  // Accert
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_equal_18) {
  s21_decimal num1 = {{3345, 2656, 1242, 0}};
  s21_decimal num2 = {{3345, 2656, 1242, 0}};
  int flag = s21_is_equal(num1, num2);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(is_equal_19) {
  s21_decimal num1 = {{467, 2, 1, 0}};
  s21_decimal num2 = {{3, 234653, 1, 0}};
  int flag = s21_is_equal(num1, num2);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(is_equal_20) {
  s21_decimal num1 = {{4, 2, 1, 589824}};
  s21_decimal num2 = {{4, 2, 1, 0}};
  int flag1 = s21_is_equal(num1, num2);
  int flag2 = s21_is_equal(num2, num1);
  ck_assert_int_eq(flag1, 0);
  ck_assert_int_eq(flag2, 0);
}
END_TEST

START_TEST(is_equal_21) {
  s21_decimal num1 = {{4, 2, 1, 65536}};
  s21_decimal num2 = {{4, 3, 1, 0}};
  int flag1 = s21_is_equal(num1, num2);
  int flag2 = s21_is_equal(num2, num1);
  ck_assert_int_eq(flag1, 0);
  ck_assert_int_eq(flag2, 0);
}
END_TEST

START_TEST(is_equal_22) {
  s21_decimal num1 = {{454, 3269, 16887, 786432}};
  s21_decimal num2 = {{454, 3269, 16887, 786432}};
  int flag1 = s21_is_equal(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_eq_7) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  float f_val1 = 1234.567993;
  float f_val2 = 1234.567993;
  s21_from_float_to_decimal(f_val1, &val1);
  s21_from_float_to_decimal(f_val2, &val2);

  ck_assert_float_eq(s21_is_equal(val1, val2), 1);
}
END_TEST

Suite *suite_is_equal(void) {
  Suite *s = suite_create("\033[45m-=S21_IS_EQUAL=-\033[0m");
  TCase *tc = tcase_create("is_equal_tc");

  tcase_add_test(tc, is_eq_1);
  tcase_add_test(tc, is_eq_2);
  tcase_add_test(tc, is_eq_3);
  tcase_add_test(tc, is_eq_4);
  tcase_add_test(tc, is_eq_5);
  tcase_add_test(tc, is_eq_6);
  tcase_add_test(tc, is_eq_7);

  // ref tests
  tcase_add_test(tc, is_equal_1);
  tcase_add_test(tc, is_equal_2);
  tcase_add_test(tc, is_equal_3);
  tcase_add_test(tc, is_equal_4);
  tcase_add_test(tc, is_equal_5);
  tcase_add_test(tc, is_equal_6);
  tcase_add_test(tc, is_equal_7);
  tcase_add_test(tc, is_equal_8);
  tcase_add_test(tc, is_equal_9);
  tcase_add_test(tc, is_equal_10);
  tcase_add_test(tc, is_equal_11);
  tcase_add_test(tc, is_equal_12);
  tcase_add_test(tc, is_equal_13);
  tcase_add_test(tc, is_equal_14);
  tcase_add_test(tc, is_equal_15);
  tcase_add_test(tc, is_equal_16);
  tcase_add_test(tc, is_equal_17);
  tcase_add_test(tc, is_equal_18);
  tcase_add_test(tc, is_equal_19);
  tcase_add_test(tc, is_equal_20);

  tcase_add_test(tc, is_equal_21);
  tcase_add_test(tc, is_equal_22);

  suite_add_tcase(s, tc);
  return s;
}
