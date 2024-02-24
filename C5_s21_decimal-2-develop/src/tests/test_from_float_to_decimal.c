#include "s21_tests.h"

START_TEST(float_to_decimal_float_max) {
  s21_decimal dec;
  int error = s21_from_float_to_decimal(FLT_MAX, &dec);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(float_to_decimal_float_min) {
  s21_decimal dec;
  int error = s21_from_float_to_decimal(FLT_MIN, &dec);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(roundtrip_dec_like_a_max) {
  s21_decimal dec;
  int error = s21_from_float_to_decimal(DEC_MAX, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(float_to_decimal_null_pointer) {
  int error = s21_from_float_to_decimal(FLT_MIN, NULL);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(roundtrip_minus_numb_one) {
  s21_decimal dec;
  float value = -123.3456789;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_minus_numb_two) {
  s21_decimal dec;
  float value = -0.123456789;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_minus_numb_three) {
  s21_decimal dec;
  float value = -123456789.0;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_minus_numb_four) {
  s21_decimal dec;
  float value = -123456789.123456789;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_one) {
  s21_decimal dec;
  float value = 431.658879;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_two) {
  s21_decimal dec;
  float value = 0.1234658879;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_three) {
  s21_decimal dec;
  float value = 123465887900000000000.0000023455;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_five) {
  s21_decimal dec;
  float value = 1234658879000045400000056560.0;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_six) {
  s21_decimal dec;
  float value = 0.00000000000001;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_seven) {
  s21_decimal dec;
  float value = 0.0000000000000198756453;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_eight) {
  s21_decimal dec;
  float value = 0.0000000000000198756553;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_nine) {
  s21_decimal dec;
  float value = 123;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_ten) {
  s21_decimal dec;
  float value = 123.213;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_eleven) {
  s21_decimal dec;
  float value = 1e-28;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(0, error);
}
END_TEST

START_TEST(roundtrip_numb_twelve) {
  s21_decimal dec;
  float value = 1e-29;
  int error = s21_from_float_to_decimal(value, &dec);
  ck_assert_int_eq(1, error);
}
END_TEST

Suite *test_21_from_float_to_decimal(void) {
  Suite *suite = suite_create("\033[45m-=S21_FROM_FLOAT_TO_DECIMAL=-\033[0m");

  TCase *tcase_core = tcase_create("CORE TESTS");

  tcase_add_test(tcase_core, float_to_decimal_float_max);
  tcase_add_test(tcase_core, float_to_decimal_float_min);
  tcase_add_test(tcase_core, roundtrip_dec_like_a_max);
  tcase_add_test(tcase_core, roundtrip_minus_numb_one);
  tcase_add_test(tcase_core, roundtrip_minus_numb_two);
  tcase_add_test(tcase_core, roundtrip_minus_numb_three);
  tcase_add_test(tcase_core, roundtrip_minus_numb_four);
  tcase_add_test(tcase_core, roundtrip_numb_one);
  tcase_add_test(tcase_core, roundtrip_numb_two);
  tcase_add_test(tcase_core, roundtrip_numb_three);
  tcase_add_test(tcase_core, roundtrip_numb_five);
  tcase_add_test(tcase_core, roundtrip_numb_six);
  tcase_add_test(tcase_core, roundtrip_numb_seven);
  tcase_add_test(tcase_core, roundtrip_numb_eight);
  tcase_add_test(tcase_core, roundtrip_numb_nine);
  tcase_add_test(tcase_core, roundtrip_numb_ten);
  tcase_add_test(tcase_core, roundtrip_numb_eleven);
  tcase_add_test(tcase_core, roundtrip_numb_twelve);
  tcase_add_test(tcase_core, float_to_decimal_null_pointer);

  suite_add_tcase(suite, tcase_core);

  return suite;
}
