#include "../helpers/s21_helpfunc.h"
#include "../s21_decimal.h"
#include "s21_arithmetic.h"

void InfDivCase(s21_error_type *error, s21_decimal *result);
void denomZero(s21_decimal value_1, s21_decimal value_2, s21_error_type *error);
s21_decimal Light_mod(s21_decimal delim, s21_decimal delit, s21_decimal chast);
void protectedDiv(s21_decimal *value_1, s21_decimal *value_2,
                  s21_decimal *result, s21_error_type *error);

int check_one(s21_decimal decimal) {
  int res = 0;
  res = 1;
  for (int i = 0; i < 96; ++i) {
    if (getBit(decimal, i) == 0) {
      res = 0;
      break;
    }
  }
  return res;
}

s21_decimal Light_mod(s21_decimal delim, s21_decimal delit, s21_decimal chast) {
  s21_decimal res = {0};
  if (is_greater_M(delit, delim)) {
    res = delim;
  } else {
    multiplication(delit, chast, &chast);
    Light_sub(delim, chast, &res);
  }
  return res;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memcheck(result);
  s21_error_type error = {0};
  if (checkErrorDiv(value_1, value_2, &error)) {
    if (check_zero(value_2)) {
      error.nan = 1;
    } else {
      s21_powNormilize(&value_1, &value_2);
      if (check_zero(value_2)) {
        denomZero(value_1, value_2, &error);
        error.nan = 1;
      } else {
        protectedDiv(&value_1, &value_2, result, &error);
      }
    }

  } else if ((error.minus_inf || error.plus_inf) && (!isInf(&value_1))) {
    InfDivCase(&error, result);
  }
  makeResult(error, result);
  return error.plus_inf ? 1 : error.minus_inf ? 2 : error.nan ? 3 : 0;
}

void protectedDiv(s21_decimal *value_1, s21_decimal *value_2,
                  s21_decimal *result, s21_error_type *error) {
  int flag = 0;
  if ((getSign(*value_1) == (-1)) ^ (getSign(*value_2) == (-1))) {
    flag = 1;
  }
  setSign(value_1, 1);
  setSign(value_2, 1);
  int power = 0;
  s21_decimal ost = {0};
  s21_decimal buf = {0};
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal five = {{5, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  power = 0;
  s21_bit_division(*value_1, *value_2, result);
  ost = Light_mod(*value_1, *value_2, *result);
  buf = *result;
  int a = 0;
  while (!check_zero(ost) && ((power) != 28) && !checkForOverflow(buf, ten)) {
    multiplication(buf, ten, &buf);
    multiplication(ost, ten, &ost);
    power++;
    s21_bit_division(ost, *value_2, result);
    addition(buf, *result, &buf, &a);
    ost = Light_mod(ost, *value_2, *result);
  }
  if (!check_zero(ost)) {
    multiplication(ost, ten, &ost);
    s21_bit_division(ost, *value_2, result);
    if (is_greater_or_equal_M(*result, five)) {
      s21_add(one, buf, &buf);
    }
  }
  *result = buf;
  setPower(result, power);
  if (flag) {
    setSign(result, -1);
  }
  if (check_zero(*result) && power >= 28) {
    error->minus_inf = 1;
  }
}

void denomZero(s21_decimal value_1, s21_decimal value_2,
               s21_error_type *error) {
  if ((getSign(value_1) == (-1)) ^ (getSign(value_2) == (-1))) {
    error->minus_inf = 1;
  } else {
    error->plus_inf = 1;
  }
}
void InfDivCase(s21_error_type *error, s21_decimal *result) {
  if (error->minus_inf) {
    setSign(result, -1);
  }
  error->minus_inf = 0;
  error->plus_inf = 0;
}
// целочисленное деление без учета нормализации и учета краевых случаев
int s21_bit_division(s21_decimal delim, s21_decimal delit, s21_decimal *chast) {
  memcheck(chast);
  int flag = 0;
  if ((getSign(delim) == (-1)) ^ (getSign(delit) == (-1))) {
    flag = 1;
  }
  setSign(&delim, 1);
  setSign(&delit, 1);
  if (is_equal_M(delim, delit)) {  // если числа равны
    chast->bits[0] = 1;
  } else if (!check_zero(delim) && is_greater_M(delim, delit)) {
    s21_decimal delitBuf = {0};
    delitBuf = delit;
    div_first_decrement(delim, delit, &delitBuf,
                        chast);  // первый этап декремента
  }
  if (flag) {
    setSign(chast, -1);
  }
  return 0;
}

void div_first_decrement(s21_decimal delim, s21_decimal delit,
                         s21_decimal *delitBuf, s21_decimal *chast) {
  int count1 = 0;
  while (is_greater_or_equal_M(delim, leftshift(*delitBuf)) &&
         !getBit(leftshift(*delitBuf), 96)) {
    *delitBuf = leftshift(*delitBuf);
    count1++;
  }
  if (count1) {
    degree_of_two(chast, count1);  // запись ответа
    s21_decimal razn = {0};
    Light_sub(delim, *delitBuf, &razn);
    while (is_greater_or_equal_M(razn, delit)) {
      div_second_decrement(delit, delitBuf, chast, &razn);
    }
  } else {
    chast->bits[0] = 1;
  }
}
void div_second_decrement(s21_decimal delit, s21_decimal *delitBuf,
                          s21_decimal *chast, s21_decimal *razn) {
  int count2 = 0;
  *delitBuf = delit;  // вернули буфер к исходнику
  while (is_greater_or_equal_M(*razn, leftshift(*delitBuf)) &&
         !getBit(leftshift(*delitBuf), 96)) {
    *delitBuf = leftshift(*delitBuf);
    count2++;
  }
  Light_sub(*razn, *delitBuf, razn);
  memset(delitBuf, 0, sizeof(s21_decimal));
  degree_of_two(delitBuf, count2);
  int a = 0;
  addition(*chast, *delitBuf, chast, &a);
}
