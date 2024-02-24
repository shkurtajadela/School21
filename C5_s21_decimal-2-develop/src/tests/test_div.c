#include "s21_tests.h"

START_TEST(div1) {
  s21_decimal var1 = {{200, 0, 0, 2147483648}};
  s21_decimal var2 = {{50, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_div(var1, var2, &result);
  s21_decimal answer = {{4, 0, 0, 2147483648}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(getPower(answer),
                   getPower(result));  // the fraction is different
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(div2) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 196608}};
  s21_decimal var2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_div(var1, var2, &result);
  s21_decimal answer = {{858993459, 858993459, 858993459, 196608}};
  ck_assert_int_eq(getPower(answer),
                   getPower(result));  // the fraction is different
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(div3) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 196608}};
  s21_decimal var2 = {{4294967295, 4294967295, 4294967295, 196608}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_div(var1, var2, &result);
  s21_decimal answer = {{1, 0, 0, 0}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(div4) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal var2 = {{1, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_div(var1, var2, &result);
  ck_assert_int_eq(1, returned_var);
}
END_TEST

START_TEST(div6) {
  s21_decimal x = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal y = {{2, 0, 0, 28 << 16}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(div7) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(div8) {
  s21_decimal x = {{52525252, 0, 0, 2147483648}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);

  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(div9) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;

  err = s21_div(x, y, &z);

  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(div10) {
  s21_decimal x = {{52525252, 0, 0, 8845}};
  s21_decimal y = {{0, 0, 0, 10}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(div11) {
  s21_decimal x = {{52525252, 0, 0, 65465}};
  s21_decimal y = {{0, 0, 0, 9598595}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(div12) {
  s21_decimal x = {{0xffffffff, 0xffffffff, 0xffffffff, NEGATIVE}};
  s21_decimal y = {{2, 0, 0, 28 << 16}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 2);
}
END_TEST

START_TEST(div13) {
  s21_decimal x = {{5, 0, 50, NEGATIVE}};
  s21_decimal y = {{5, 0, 0, NEGATIVE}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_div(x, y, &z);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(div14) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(div15) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, 983040}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "100000 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(div16) {
  s21_decimal x = {{1, 1, 1, 10 << 16}};
  s21_decimal y = {{1, 10, 1, NEGATIVE + (15 << 16)}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1019311944 458670364 542101085 2148990976";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(div17) {
  s21_decimal x = {{1, 1, 1, 983040}};
  s21_decimal y = {{1, 1, 1, -2146500608}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(div_1_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_2_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{4, 0, 0, -2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 25);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq((int)res.bits[3], -2147418112);
}
END_TEST

START_TEST(div_3_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 894784853);
  ck_assert_int_eq((int)res.bits[1], -819591186);
  ck_assert_int_eq(res.bits[2], 1807003620);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_4_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{22, 0, 0, 65536}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 48806447);
  ck_assert_int_eq((int)res.bits[1], -1898527489);
  ck_assert_int_eq((int)res.bits[2], -1830871450);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_5_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, 393216}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 10000000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_7_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{658067456, 1164, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 786432);
}
END_TEST

START_TEST(div_9_test) {
  s21_decimal num1 = {{-1, -1, -1, 0}};
  s21_decimal num2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq((int)res.bits[2], -2147483648);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_10_test) {
  s21_decimal num1 = {{-1, -1, -1, 0}};
  s21_decimal num2 = {{4, 0, 0, -2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1073741824);
  ck_assert_int_eq((int)res.bits[3], -2147483648);
}
END_TEST

START_TEST(div_11_test) {
  s21_decimal num1 = {{-1, -1, -1, 0}};
  s21_decimal num2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1431655765);
  ck_assert_int_eq(res.bits[1], 1431655765);
  ck_assert_int_eq(res.bits[2], 1431655765);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_13_test) {
  s21_decimal num1 = {{-1, -1, -1, 0}};
  s21_decimal num2 = {{658067456, 1164, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 858993459);
  ck_assert_int_eq(res.bits[1], 858993459);
  ck_assert_int_eq(res.bits[2], 858993459);
  ck_assert_int_eq(res.bits[3], 786432);
}
END_TEST

START_TEST(div_18_test) {
  s21_decimal num1 = {{1, 1, 1, 1835008}};
  s21_decimal num2 = {{0, 0, 0, -2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 3);
}
END_TEST

START_TEST(div_19_test) {
  s21_decimal num1 = {{-1, -1, -1, 0}};
  s21_decimal num2 = {{1, 0, 0, 393216}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(div_20_test) {
  s21_decimal num1 = {{1, 0, 0, 1835008}};
  s21_decimal num2 = {{4, 0, 0, -2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(div_big_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result_our = {{0, 0, 0, 0}};

  src1.bits[0] = 0b11111111111111111111111111111110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000111000000000000000000;
  int val = s21_div(src1, src2, &result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

START_TEST(div_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result;
  int val = s21_div(src1, src2, &result);
  ck_assert_int_eq(val, 3);
}
END_TEST

Suite *suite_div(void) {
  Suite *s = suite_create("\033[45m-=S21_DIV=-\033[0m");
  TCase *tc = tcase_create("div_tc");
  tcase_add_test(tc, div1);
  tcase_add_test(tc, div2);
  tcase_add_test(tc, div3);
  tcase_add_test(tc, div4);
  // tcase_add_test(tc, div5);
  tcase_add_test(tc, div6);
  tcase_add_test(tc, div7);
  tcase_add_test(tc, div8);
  tcase_add_test(tc, div9);
  tcase_add_test(tc, div10);
  tcase_add_test(tc, div11);
  tcase_add_test(tc, div12);
  tcase_add_test(tc, div13);
  tcase_add_test(tc, div14);
  tcase_add_test(tc, div15);
  tcase_add_test(tc, div16);
  tcase_add_test(tc, div17);
  tcase_add_test(tc, div_1_test);
  tcase_add_test(tc, div_2_test);
  tcase_add_test(tc, div_3_test);
  tcase_add_test(tc, div_4_test);
  tcase_add_test(tc, div_5_test);
  tcase_add_test(tc, div_7_test);
  tcase_add_test(tc, div_9_test);
  tcase_add_test(tc, div_10_test);
  tcase_add_test(tc, div_11_test);
  tcase_add_test(tc, div_13_test);
  tcase_add_test(tc, div_18_test);
  tcase_add_test(tc, div_19_test);
  tcase_add_test(tc, div_20_test);
  tcase_add_test(tc, div_big_error);
  tcase_add_test(tc, div_error);

  suite_add_tcase(s, tc);
  return s;
}
