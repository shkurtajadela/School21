#include "s21_tests.h"

START_TEST(roundtrip_int_max) {
  s21_decimal tmp;
  int value = 0;
  int error = s21_from_int_to_decimal(INT_MAX, &tmp);
  ck_assert_int_eq(0, error);
  error = s21_from_decimal_to_int(tmp, &value);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(INT_MAX, value);
}
END_TEST

START_TEST(roundtrip_int_min) {
  s21_decimal tmp;
  int value = 0;
  int error = s21_from_int_to_decimal(INT_MIN, &tmp);
  ck_assert_int_eq(0, error);
  error = s21_from_decimal_to_int(tmp, &value);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(INT_MIN, value);
}
END_TEST

START_TEST(roundtrip_int_zero) {
  s21_decimal tmp;
  int value = 0;
  int error = s21_from_int_to_decimal(0, &tmp);
  ck_assert_int_eq(0, error);
  error = s21_from_decimal_to_int(tmp, &value);
  ck_assert_int_eq(0, value);
}
END_TEST

START_TEST(int_to_dec_max) {
  s21_decimal tmp;
  int error = s21_from_int_to_decimal(INT_MAX, &tmp);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(INT_MAX, tmp.bits[0]);
  ck_assert_int_eq(0, tmp.bits[1]);
  ck_assert_int_eq(0, tmp.bits[2]);
  ck_assert_int_eq(0, tmp.bits[3]);
}
END_TEST

START_TEST(int_to_dec_min) {
  s21_decimal tmp;
  int a = 0;
  int error = s21_from_int_to_decimal(INT_MIN, &tmp);
  ck_assert_int_eq(0, error);
  error = s21_from_decimal_to_int(tmp, &a);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(INT_MIN, a);
  ck_assert_int_eq(2147483648, tmp.bits[0]);
  ck_assert_int_eq(0, tmp.bits[1]);
  ck_assert_int_eq(0, tmp.bits[2]);
  ck_assert_int_eq(2147483648, tmp.bits[3]);
}
END_TEST

START_TEST(dec_to_int_big_num_one) {
  s21_decimal dec;
  dec.bits[0] = 12234;
  dec.bits[1] = 653453;
  int a = 0;
  int error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(dec_to_int_big_num_two) {
  s21_decimal dec;
  dec.bits[0] = 12234;
  dec.bits[1] = 653453;
  dec.bits[2] = 653453;
  int a = 0;
  int error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(dec_to_int_big_num_three) {
  s21_decimal dec;
  dec.bits[1] = 653453;
  dec.bits[2] = 653453;
  int a = 0;
  int error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(dec_to_int_big_num_four) {
  s21_decimal dec;
  dec.bits[2] = 653453;
  int a = 0;
  int error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(dec_to_int_big_num_five) {
  s21_decimal dec;
  dec.bits[0] = 653453;
  dec.bits[1] = 653453;
  dec.bits[2] = 653453;
  int a = 0;
  int error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(roundtrip_one) {
  s21_decimal dec;
  int a = 5463654;
  int error = s21_from_int_to_decimal(a, &dec);
  ck_assert_int_eq(0, error);
  error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(5463654, a);
}
END_TEST

START_TEST(roundtrip_two) {
  s21_decimal dec;
  int a = -5463654;
  int error = s21_from_int_to_decimal(a, &dec);
  ck_assert_int_eq(0, error);
  error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(-5463654, a);
}
END_TEST

START_TEST(roundtrip_three) {
  s21_decimal dec;
  int a = 1;
  int error = s21_from_int_to_decimal(a, &dec);
  ck_assert_int_eq(0, error);
  error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, a);
}
END_TEST

START_TEST(roundtrip_five) {
  s21_decimal dec;
  int a = -34;
  int error = s21_from_int_to_decimal(a, &dec);
  ck_assert_int_eq(0, error);
  error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(-34, a);
}
END_TEST

START_TEST(overflow_of_the_mantissa_1) {
  s21_decimal dec;
  s21_decimal_set_zero(&dec);
  dec.bits[1] = 132;
  int a;
  int error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(overflow_of_the_mantissa_2) {
  s21_decimal dec;
  s21_decimal_set_zero(&dec);
  dec.bits[2] = 132;
  int a;
  int error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(overflow_of_the_mantissa_3) {
  s21_decimal dec;
  s21_decimal_set_zero(&dec);
  dec.bits[1] = 132;
  dec.bits[2] = 132;
  int a;
  int error = s21_from_decimal_to_int(dec, &a);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(null_dst) {
  s21_decimal dec;
  s21_decimal_set_zero(&dec);
  dec.bits[1] = 132;
  dec.bits[2] = 132;
  int error = s21_from_decimal_to_int(dec, NULL);
  ck_assert_int_eq(1, error);
}
END_TEST

Suite *test_s21_from_decimal_to_int(void) {
  Suite *suite = suite_create("\033[45m-=S21_FROM_DECIMAL_TO_INT=-\033[0m");

  TCase *tcase_core = tcase_create("S21_FROM_DECIMAL_TO_INT TESTS");

  tcase_add_test(tcase_core, roundtrip_int_max);
  tcase_add_test(tcase_core, roundtrip_int_min);
  tcase_add_test(tcase_core, roundtrip_int_zero);
  tcase_add_test(tcase_core, int_to_dec_max);
  tcase_add_test(tcase_core, int_to_dec_min);
  tcase_add_test(tcase_core, dec_to_int_big_num_one);
  tcase_add_test(tcase_core, dec_to_int_big_num_two);
  tcase_add_test(tcase_core, dec_to_int_big_num_three);
  tcase_add_test(tcase_core, dec_to_int_big_num_four);
  tcase_add_test(tcase_core, dec_to_int_big_num_five);
  tcase_add_test(tcase_core, roundtrip_one);
  tcase_add_test(tcase_core, roundtrip_two);
  tcase_add_test(tcase_core, roundtrip_three);
  tcase_add_test(tcase_core, roundtrip_five);
  tcase_add_test(tcase_core, overflow_of_the_mantissa_1);
  tcase_add_test(tcase_core, overflow_of_the_mantissa_2);
  tcase_add_test(tcase_core, overflow_of_the_mantissa_3);
  tcase_add_test(tcase_core, null_dst);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
