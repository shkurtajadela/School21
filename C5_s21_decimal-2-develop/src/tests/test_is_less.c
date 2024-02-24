#include "s21_tests.h"

START_TEST(is_less_01) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(5, &val2);

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(is_less_02) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(2, &val1);
  s21_from_int_to_decimal(5, &val2);

  ck_assert_int_eq(s21_is_less(val1, val2), 1);
}
END_TEST

START_TEST(is_less_03) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(2, &val2);

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(is_less_04) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-5, &val1);
  s21_from_int_to_decimal(-5, &val2);

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(is_less_05) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-2, &val1);
  s21_from_int_to_decimal(-5, &val2);

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(is_less_06) {
  s21_decimal val1 = {{8}};
  s21_decimal val2 = {{8}};

  s21_from_int_to_decimal(-5, &val1);
  s21_from_int_to_decimal(-2, &val2);

  ck_assert_int_eq(s21_is_less(val1, val2), 1);
}
END_TEST

START_TEST(is_less_1) {
  s21_decimal x = {{4294967295, 0, 0, 0}};
  s21_decimal y = {{0, 1, 0, 0}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 2, NEGATIVE}};

  int ourRes = s21_is_less(y, x);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_less(y, x);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal x = {{0, 0, 1, NEGATIVE}};
  s21_decimal y = {{0, 0, 1, 0}};

  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, NEGATIVE}};

  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_9) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_10) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_11) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_12) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int ourRes = s21_is_less(x, y);
  int expect = 1;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_13) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int ourRes = s21_is_less(x, y);
  int expect = 0;
  ck_assert_int_eq(ourRes, expect);
}
END_TEST

START_TEST(is_less_14) {
  s21_decimal num1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_less_15) {
  s21_decimal num1 = {{1, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, -2147483648}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_less_16) {
  s21_decimal num1 = {{10, 0, 0, -2147483648}};
  s21_decimal num2 = {{9, 0, 0, -2147483648}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_less_17) {
  s21_decimal num1 = {{9, 0, 0, -2147483648}};
  s21_decimal num2 = {{10, 0, 0, -2147483648}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_less_18) {
  s21_decimal num1 = {{10, 11, 12, 0}};
  s21_decimal num2 = {{9, 8, 13, 0}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_less_19) {
  s21_decimal num1 = {{500, 1, 3, -2146041856}};
  s21_decimal num2 = {{5, 4, 8, -2146238464}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 0);
}
END_TEST

START_TEST(is_less_20) {
  s21_decimal num1 = {{5, 4, 8, -2146238464}};
  s21_decimal num2 = {{500, 1, 3, -2146041856}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST
START_TEST(is_less_21) {
  s21_decimal num1 = {{10, 11, 12, 65536}};
  s21_decimal num2 = {{9, 8, 13, 65536}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

START_TEST(is_less_22) {
  s21_decimal num1 = {{6, 0, 0, 589824}};
  s21_decimal num2 = {{0, 0, 10, 0}};
  int flag1 = s21_is_less(num1, num2);
  ck_assert_int_eq(flag1, 1);
}
END_TEST

Suite *suite_is_less(void) {
  Suite *s = suite_create("\033[45m-=S21_IS_LESS=-\033[0m");
  TCase *tc = tcase_create("is_less_tc");

  tcase_add_test(tc, is_less_01);
  tcase_add_test(tc, is_less_02);
  tcase_add_test(tc, is_less_03);
  tcase_add_test(tc, is_less_04);
  tcase_add_test(tc, is_less_05);
  tcase_add_test(tc, is_less_06);

  // ref tests
  tcase_add_test(tc, is_less_22);
  tcase_add_test(tc, is_less_1);
  tcase_add_test(tc, is_less_2);
  tcase_add_test(tc, is_less_3);
  tcase_add_test(tc, is_less_4);
  tcase_add_test(tc, is_less_5);
  tcase_add_test(tc, is_less_6);
  tcase_add_test(tc, is_less_7);
  tcase_add_test(tc, is_less_8);
  tcase_add_test(tc, is_less_9);
  tcase_add_test(tc, is_less_10);
  tcase_add_test(tc, is_less_11);
  tcase_add_test(tc, is_less_12);
  tcase_add_test(tc, is_less_13);
  tcase_add_test(tc, is_less_14);
  tcase_add_test(tc, is_less_15);
  tcase_add_test(tc, is_less_16);
  tcase_add_test(tc, is_less_17);
  tcase_add_test(tc, is_less_18);
  tcase_add_test(tc, is_less_19);
  tcase_add_test(tc, is_less_20);
  tcase_add_test(tc, is_less_21);
  tcase_add_test(tc, is_less_22);

  suite_add_tcase(s, tc);
  return s;
}
