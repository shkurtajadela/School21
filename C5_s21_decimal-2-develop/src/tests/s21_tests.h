#ifndef SRC_TESTS_S21_TESTS_H_
#define SRC_TESTS_S21_TESTS_H_

#define SIGN 0x80000000
#define BUF 1024
#define NEGATIVE 2147483648

#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../helpers/s21_helpfunc.h"
#include "../s21_arithmetic/s21_arithmetic.h"
#include "../s21_auxiliary.h"
#include "../s21_convertors/s21_convertors.h"
#include "../s21_decimal.h"

// convertors
Suite *suite_from_int_to_decimal(void);

Suite *test_s21_from_decimal_to_int(void);

Suite *suite_from_decimal_to_float(void);

Suite *test_21_from_float_to_decimal(void);
//

// comparations
Suite *test_s21_is_greater(void);

Suite *suite_is_greater_or_equal(void);

Suite *suite_is_equal(void);

Suite *suite_is_not_equal(void);

Suite *suite_is_less(void);

Suite *suite_is_less_or_equal(void);
//

// arithmetic
Suite *suite_add(void);

Suite *suite_mul(void);

Suite *test_21_sub(void);

Suite *suite_div(void);

// another functions
Suite *test_S21_negate(void);

Suite *suite_truncate(void);

Suite *test_s21_round(void);

Suite *suite_floor(void);

Suite *test_21_mod(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // SRC_TESTS_S21_TESTS_H_
