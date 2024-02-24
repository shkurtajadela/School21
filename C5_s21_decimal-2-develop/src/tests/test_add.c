#include "s21_tests.h"

START_TEST(add_sign_1) {
  s21_decimal var1 = {{5, 0, 0, 0}};
  s21_decimal var2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{7, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_2) {
  s21_decimal var1 = {{5, 0, 0, 2147483648}};
  s21_decimal var2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{3, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_3) {
  s21_decimal var1 = {{5, 0, 0, 0}};
  s21_decimal var2 = {{2, 0, 0, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{3, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_4) {
  s21_decimal var1 = {{5, 0, 0, 2147483648}};
  s21_decimal var2 = {{2, 0, 0, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{7, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_5) {
  s21_decimal var1 = {{1, 0, 0, 2147483648}};
  s21_decimal var2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{1, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_6) {
  s21_decimal var1 = {{1, 0, 0, 2147483648}};
  s21_decimal var2 = {{2, 0, 0, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{3, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_7) {
  s21_decimal var1 = {{1, 0, 0, 0}};
  s21_decimal var2 = {{2, 0, 0, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{1, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_8) {
  s21_decimal var1 = {{0, 0, 0, 0}};
  s21_decimal var2 = {{1, 0, 0, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{1, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_9) {
  s21_decimal var1 = {{1, 0, 0, 2147483648}};
  s21_decimal var2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{1, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add_sign_10) {
  s21_decimal var1 = {{1, 0, 0, 2147483648}};
  s21_decimal var2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

// START_TEST(add_neg_inf) {
//   s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
//   s21_decimal var2 = {{1, 0, 0, 2147483648}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_decimal answer = {{0, 0, 0, 2164195328}};
//   ck_assert_int_eq(2, s21_add(var1, var2, &result));
//   ck_assert_int_eq(1, s21_is_equal(answer, result));
// }
// END_TEST

START_TEST(add_plus_inf) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal var2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0, 0, 0, 2164195328}};
  ck_assert_int_eq(1, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add1) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 196608}};
  s21_decimal var2 = {{1, 0, 0, 196608}};
  s21_decimal result = {{0, 0, 0, 0}};
  // int returned_var = s21_add(var1, var2, &result);

  s21_decimal answer = {{2576980378, 2576980377, 429496729, 131072}};
  ck_assert_int_eq(0, s21_add(var1, var2, &result));
  ck_assert_int_eq(1, is_equal_M(answer, result));
}
END_TEST

START_TEST(add2) {
  s21_decimal var1 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal var2 = {{1, 0, 0, 1835008}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_add(var1, var2, &result);
  s21_decimal answer = {{4294967294, 4294967295, 4294967295, 0}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, is_equal_M(answer, result));
}
END_TEST

START_TEST(add3) {
  s21_decimal var1 = {{456789, 0, 0, 0}};
  s21_decimal var2 = {{123456, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_add(var1, var2, &result);
  s21_decimal answer = {{580245, 0, 0, 0}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add4) {
  s21_decimal var1 = {{3210, 0, 0, NEGATIVE}};
  s21_decimal var2 = {{1234, 0, 0, NEGATIVE}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_add(var1, var2, &result);
  s21_decimal answer = {{4444, 0, 0, NEGATIVE}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add5) {
  s21_decimal var1 = {{3210, 0, 0, NEGATIVE}};
  s21_decimal var2 = {{1234, 0, 0, NEGATIVE}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_add(var1, var2, &result);
  s21_decimal answer = {{4444, 0, 0, NEGATIVE}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add6) {
  s21_decimal var1 = {{4294967294, 4294967295, 0, 0}};
  s21_decimal var2 = {{1, 4294967295, 4294967294, 0}};
  s21_decimal result = {{0, 0, 0, 0}};

  int returned_var = s21_add(var1, var2, &result);
  s21_decimal answer = {{4294967295, 4294967294, 4294967295, 0}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add7) {
  s21_decimal var1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal var2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_add(var1, var2, &result);
  ck_assert_int_eq(1, returned_var);
}
END_TEST

START_TEST(add8) {
  s21_decimal var1 = {{613478421, 0, 0, 196608}};
  s21_decimal var2 = {{2056771366, 613, 0, 393216}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_add(var1, var2, &result);
  s21_decimal answer = {{1354869038, 756, 0, 393216}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add9) {
  s21_decimal var1 = {{613478421, 0, 0, 196608}};
  s21_decimal var2 = {{0, 0, 0, 393216}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_add(var1, var2, &result);
  s21_decimal answer = {{613478421, 0, 0, 196608}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add10) {
  s21_decimal var1 = {{23784103, 0, 0, 0}};
  s21_decimal var2 = {{721398, 0, 0, NEGATIVE}};
  s21_decimal result = {{0, 0, 0, 0}};
  int returned_var = s21_add(var1, var2, &result);
  s21_decimal answer = {{23062705, 0, 0, 0}};
  ck_assert_int_eq(0, returned_var);
  ck_assert_int_eq(1, s21_is_equal(answer, result));
}
END_TEST

START_TEST(add11) {
  s21_decimal x = {{4294967295, 4294967295, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 1 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add12) {
  s21_decimal x = {{20, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967295 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add13) {
  s21_decimal x = {{20, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "41 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add14) {
  s21_decimal x = {{20, 1, 0, 0}};
  s21_decimal y = {{21, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967295 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add15) {
  s21_decimal x = {{20, 0, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add16) {
  s21_decimal x = {{25, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add17) {
  s21_decimal x = {{100, 0, 0, 2147483648}};
  s21_decimal y = {{100, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add18) {
  s21_decimal x = {{99, 0, 0, 0}};
  s21_decimal y = {{100, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add19) {
  s21_decimal test = {{15, 0, 0, 65536}};
  s21_round(test, &test);
  s21_decimal value_1 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{15, 0, 0, 65536}};
  s21_decimal result = {{0}};
  s21_decimal answer = {0};
  makeInf(&answer);
  ck_assert_int_eq(1, s21_add(value_1, value_2, &result));
  ck_assert_int_eq(1, s21_is_equal(result, answer));
}
END_TEST

START_TEST(add20) {
  s21_decimal x = {{0, 0, 3000000000, 0}};
  s21_decimal y = {{0, 0, 3000000000, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = s21_add(x, y, &z);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(add22) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, 65536}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);

  char ourRes[1000], expect[1000] = "2 2 2 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add23) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1000000001 1000000001 1000000001 655360";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add24) {
  s21_decimal x = {{24, 1, 1, -2147418112}};
  s21_decimal y = {{1, 15, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "2525163519 999999990 999999999 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add25) {
  s21_decimal x = {{1, 1, 1, 655360}};       // 10 степень
  s21_decimal y = {{1, 1, 1, -2147418112}};  // знак минус, степень 1
  // при нормализации второй децимал переполняется но вроде корректно
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "999999999 999999999 999999999 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(add_check) {
  s21_decimal src1, src2, true_result, result, dec_null, dec_max = {0};

  int val = 0;

  memset(&dec_null, 0, sizeof(s21_decimal));
  memset(&true_result, 0, sizeof(s21_decimal));
  // s21_set_zero(&dec_null);
  // s21_set_zero(&true_result);
  dec_max.bits[0] = dec_max.bits[1] = dec_max.bits[2] = 0xffffffff;
  dec_max.bits[3] = 0;
  // 1+3=4
  src1 = dec_null;
  src1.bits[0] = 1;
  src2 = dec_null;
  src2.bits[0] = 3;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, 0);

  // -1+3=2
  src1.bits[0] = 1;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2 = dec_null;
  src2.bits[0] = 3;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, 0);

  // -1+(-3)=-4
  src1.bits[0] = 1;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 3;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, 0);

  // 1+(-3)=-2
  src1 = dec_null;
  src1.bits[0] = 1;
  src2.bits[0] = 3;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, 0);

  // 3+1=4
  src1 = dec_null;
  src1.bits[0] = 3;
  src2 = dec_null;
  src2.bits[0] = 1;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, 0);

  // -3+1=-2
  src1.bits[0] = 3;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2 = dec_null;
  src2.bits[0] = 1;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, 0);

  // 3+(-1)=2
  src1 = dec_null;
  src1.bits[0] = 3;
  src2.bits[0] = 1;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, 0);

  // -3+(-1)=-4
  src1.bits[0] = 3;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0x80000000;
  src2.bits[0] = 1;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, 0);
  // 2-16=-14
  src1 = dec_null;
  src1.bits[0] = 2;
  src2.bits[0] = 16;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 14);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, 0);

  // 79228162514264337593543950335+(-6)=79228162514264337593543950329
  src1 = dec_max;
  src2.bits[0] = 6;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 0x80000000;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xffffffff - 6);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, 0);

  // 79228162514264337593543950335+0.4=79228162514264337593543950335
  src1 = dec_max;
  src2.bits[0] = 4;
  src2.bits[1] = 0;
  src2.bits[2] = 0;
  src2.bits[3] = 65536;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, 0);

  // 99+1=100
  src1 = dec_null;
  src1.bits[0] = 99;
  src2 = dec_null;
  src2.bits[0] = 1;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, 0);
  // 79228162514264337593543950335-79228162514264337593543950335=0
  src1 = dec_max;
  src2 = dec_max;
  src2.bits[3] = 0x80000000;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(val, 0);

  // 79228162514264337593543950335+79228162514264337593543950335=1
  src1 = dec_max;
  src2 = dec_max;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(val, 1);
  // 18446744073709551615 - 79228162514264337593543950335 =
  // -79228162495817593519834398720 src1.bits[0] = 0xffffffff;
  src1.bits[1] = 0xffffffff;
  src1.bits[2] = 0;
  src1.bits[3] = 0;
  src2 = dec_max;
  src2.bits[3] = 0x80000000;
  val = s21_add(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq((unsigned)result.bits[2], 0xffffffff);
  ck_assert_int_eq((unsigned)result.bits[3], 0x80000000);
  ck_assert_int_eq(val, 0);
}
END_TEST

Suite *suite_add(void) {
  Suite *s = suite_create("\033[45m-=S21_ADD=-\033[0m");
  TCase *tc = tcase_create("add_tc");

  tcase_add_test(tc, add_sign_1);
  tcase_add_test(tc, add_sign_2);
  tcase_add_test(tc, add_sign_3);
  tcase_add_test(tc, add_sign_4);
  tcase_add_test(tc, add_sign_5);
  tcase_add_test(tc, add_sign_6);
  tcase_add_test(tc, add_sign_7);
  tcase_add_test(tc, add_sign_8);
  tcase_add_test(tc, add_sign_9);
  tcase_add_test(tc, add_sign_10);

  tcase_add_test(tc, add_plus_inf);
  // tcase_add_test(tc, add_neg_inf);

  tcase_add_test(tc, add1);
  tcase_add_test(tc, add2);
  tcase_add_test(tc, add3);
  tcase_add_test(tc, add4);
  tcase_add_test(tc, add5);
  tcase_add_test(tc, add6);
  tcase_add_test(tc, add7);
  tcase_add_test(tc, add8);
  tcase_add_test(tc, add9);
  tcase_add_test(tc, add10);
  tcase_add_test(tc, add11);
  tcase_add_test(tc, add12);
  tcase_add_test(tc, add13);
  tcase_add_test(tc, add14);
  tcase_add_test(tc, add15);
  tcase_add_test(tc, add16);
  tcase_add_test(tc, add17);
  tcase_add_test(tc, add18);
  tcase_add_test(tc, add19);
  tcase_add_test(tc, add20);
  tcase_add_test(tc, add22);
  tcase_add_test(tc, add23);
  tcase_add_test(tc, add24);
  tcase_add_test(tc, add25);
  tcase_add_test(tc, add_check);

  suite_add_tcase(s, tc);
  return s;
}
