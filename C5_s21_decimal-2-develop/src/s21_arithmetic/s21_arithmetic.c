#include "s21_arithmetic.h"

s21_decimal bank_round(s21_decimal bit) {
  s21_decimal ceil = {0};
  s21_decimal mod = {0};
  s21_decimal ten = {0};
  s21_decimal five = {0};
  s21_decimal res = {0};
  ten.bits[0] = 10;
  five.bits[0] = 5;
  s21_bit_division(bit, ten, &ceil);
  res = ceil;
  s21_bit_mod(bit, ten, &mod);
  if (is_uneven(ceil) && is_greater_or_equal_M(mod, five)) {
    s21_decimal one = {0};
    one.bits[0] = 1;
    int a = 0;
    addition(ceil, one, &res, &a);
  }
  return res;
}

int is_uneven(s21_decimal bit) { return (getBit(bit, 0)) ? 1 : 0; }

s21_decimal leftshift(s21_decimal bit) {
  s21_decimal res = {0};
  res = bit;
  for (int i = 95; find_one(bit, &i); --i) {
    setBit(&res, i, 0);
    setBit(&res, i + 1, 1);
  }
  return res;
}
int find_one(s21_decimal bit, int *pos) {
  int flag = 0;
  for (int i = *pos; i >= 0; --i) {
    if (getBit(bit, i) == 1) {
      *pos = i;
      flag = 1;
      break;
    }
  }
  return (flag);
}

int check_zero(s21_decimal decimal) {  // проверка на нулевой decimal
  int res = 0;
  res = 1;
  for (int i = 0; i < 96; ++i) {
    if (getBit(decimal, i) == 1) {
      res = 0;
      break;
    }
  }
  return res;
}
void degree_of_two(s21_decimal *num, int degree) {
  if (degree) {
    num->bits[0] = 1;
    for (int i = 0; i < degree; ++i) {
      *num = leftshift(*num);
    }
  } else {
    s21_decimal one = {0};
    one.bits[0] = 1;
    int a = 0;
    addition(*num, one, num, &a);
  }
}

int checkErrorMul(const s21_decimal value_1, const s21_decimal value_2,
                  s21_error_type *error) {
  int flag = 1;
  if (isNan(&value_1) || isNan(&value_2)) {
    flag = 0;
    error->nan = 1;
  } else if (isInf(&value_1) || isInf(&value_2)) {
    if (getSign(value_1) * getSign(value_2) == 1) {
      flag = 0;
      error->plus_inf = 1;
    } else {
      flag = 0;
      error->minus_inf = 1;
    }
  }
  return flag;
}

int checkErrorDiv(const s21_decimal value_1, const s21_decimal value_2,
                  s21_error_type *error) {
  int flag = 1;
  if (isNan(&value_1) || isNan(&value_2)) {
    flag = 0;
    error->nan = 1;
  } else if (isInf(&value_1)) {
    if (isInf(&value_2)) {
      flag = 0;
      error->nan = 1;
    } else {
      if (getSign(value_1) * getSign(value_2) == 1) {
        flag = 0;
        error->plus_inf = 1;
      } else {
        flag = 0;
        error->minus_inf = 1;
      }
    }
  } else if (isInf(&value_2)) {
    if (getSign(value_1) * getSign(value_2) == 1) {
      flag = 0;
      error->plus_inf = 1;
    } else {
      flag = 0;
      error->minus_inf = 1;
    }
  }
  return flag;
}

int makeInf(s21_decimal *el) {
  int res = 1;
  if (el != NULL) {
    memset(el, 0, sizeof(s21_decimal));
    setSign(el, 1);
    setPower(el, 255);
    el->bits[2] = 0;
    el->bits[1] = 0;
    el->bits[0] = 0;
  } else {
    res = 0;
  }
  return res;
}

int makeNegInf(s21_decimal *el) {
  int res = 1;
  if (el != NULL) {
    memset(el, 0, sizeof(s21_decimal));
    setSign(el, -1);
    setPower(el, 255);
    el->bits[2] = 0;
    el->bits[1] = 0;
    el->bits[0] = 0;
  } else {
    res = 0;
  }
  return res;
}

int makeNan(s21_decimal *el) {
  int res = 1;
  if (el != NULL) {
    memset(el, 0, sizeof(s21_decimal));
    setPower(el, 255);
    el->bits[2] = 2147483648;
    el->bits[1] = 0;
    el->bits[0] = 0;
  } else {
    res = 0;
  }
  return res;
}
void makeResult(s21_error_type error, s21_decimal *result) {
  if (error.plus_inf) {
    makeInf(result);
  } else if (error.minus_inf) {
    makeNegInf(result);
  } else if (error.nan) {
    makeNan(result);
  }
}

int getAroundOverflow_s21_add(s21_decimal *value_1, s21_decimal *value_2,
                              s21_decimal *result, int index, int cases,
                              int *power) {
  int overflow_status = 0;
  if (*power == 0) {
    overflow_status++;
    s21_big_decimal big_result = decimalToBigDecimal(*result);
    setBitBigDecimal(&big_result, index, cases - 2);
    setBitBigDecimal(&big_result, index + 1, 1);
    bigDecimalToDecimal(big_result, result, *power);
  } else {
    memset(result, 0, sizeof(s21_decimal));
    powerValueToXDown(value_1, power, (*power - 1));
    powerValueToXDown(value_2, power, (*power - 1));
    addition(*value_1, *value_2, result, power);
  }
  return overflow_status;
}

void Light_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memcheck(result);
  int a = 0;
  switch (getSign(value_1) * getSign(value_2)) {
    case 1:
      positive_sub(value_1, value_2, result, 0);
      break;
    case -1:
      if (getSign(value_1) == (-1)) {
        setSign(&value_1, 1);

        addition(value_1, value_2, result, &a);
        setSign(result, -1);
      }
      if (getSign(value_2) == (-1)) {
        setSign(&value_2, 1);
        addition(value_1, value_2, result, &a);
      }
      break;
  }
}

int v1_greater_v2(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                  int power) {
  int res = 0;
  if (is_greater_M(value_1, value_2)) {
    s21_bit_sub(value_1, value_2, result);
    setPower(result, power);
    res = 1;
  }
  return res;
}
int v2_greater_v1(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                  int power) {
  int res = 0;
  if (is_greater_M(value_2, value_1)) {
    s21_bit_sub(value_2, value_1, result);
    setPower(result, power);
    setSign(result, -1);
    res = 1;
  }
  return res;
}

int s21_bit_sub(s21_decimal bit1, s21_decimal bit2, s21_decimal *res) {
  int flag = 0;
  int mindone = 0;
  for (int j = 0; j < 96; ++j) {
    if (getBit(bit1, j) && getBit(bit2, j)) {
      and_pattern(&mindone, res, j);
    } else if (getBit(bit1, j) == 1 && getBit(bit2, j) == 0) {
      one_zero_pattern(&mindone, res, j);
    } else if (getBit(bit1, j) == 0 && getBit(bit2, j) == 1) {
      zero_one_pattern(&mindone, res, j);
    } else if (getBit(bit1, j) == 0 && getBit(bit2, j) == 0) {
      and_pattern(&mindone, res, j);
    }
  }
  return (flag);
}
void one_zero_pattern(int *mindone, s21_decimal *res, int j) {
  if (*mindone) {
    setBit(res, j, 0);
    *mindone = 0;
  } else {
    setBit(res, j, 1);
  }
}
void and_pattern(int *mindone, s21_decimal *res, int j) {
  if (*mindone) {
    setBit(res, j, 1);
  } else {
    setBit(res, j, 0);
  }
}
void zero_one_pattern(int *mindone, s21_decimal *res, int j) {
  if (*mindone) {
    setBit(res, j, 0);
  } else {
    *mindone = 1;
    setBit(res, j, 1);
  }
}

void positive_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                  int power) {
  if ((getSign(value_1) == (-1)) && (getSign(value_2) == (-1))) {
    setSign(&value_1, 1);
    setSign(&value_2, 1);
    if (v1_greater_v2(value_1, value_2, result, power)) {
      setSign(result, -1);
    }
    if (v2_greater_v1(value_1, value_2, result, power)) {
      setSign(result, 1);
    }
  } else {
    v1_greater_v2(value_1, value_2, result, power);
    v2_greater_v1(value_1, value_2, result, power);
  }
}

s21_big_decimal bank_roundBigDeicmal(s21_big_decimal bit) {
  s21_big_decimal ceil = {0};
  s21_big_decimal mod = {0};
  s21_big_decimal ten = {0};
  s21_big_decimal five = {0};
  s21_big_decimal res = {0};
  ten.bits[0] = 10;
  five.bits[0] = 5;
  s21_bit_divisionBigDeicmal(bit, ten, &ceil);
  res = ceil;
  s21_bit_modBigDeicmal(bit, ten, &mod);
  if (is_unevenBigDeicmal(ceil) && is_greater_or_equal_MBigDecimal(mod, five)) {
    s21_big_decimal one = {0};
    one.bits[0] = 1;
    additionBigDecimal(ceil, one, &res);
  }
  return res;
}

void s21_bit_modBigDeicmal(s21_big_decimal delim, s21_big_decimal delit,
                           s21_big_decimal *ostatok) {
  nullBigDecimal(ostatok);
  if (is_greater_MBigDecimal(delit, delim)) {
    *ostatok = delim;
  } else {
    s21_big_decimal buf = {0};
    s21_bit_divisionBigDeicmal(delim, delit, &buf);
    buf = simpleMultiplicationBigDecimal(delit, buf);
    Light_subBigDecimal(delim, buf, ostatok);
  }
}

s21_big_decimal simpleMultiplicationBigDecimal(s21_big_decimal big_value_1,
                                               s21_big_decimal big_value_2) {
  s21_big_decimal big_result = {0};
  s21_big_decimal value_2_copied = big_value_2;
  s21_big_decimal sum = {0};
  for (int index = 0; index < 224; index++) {
    value_2_copied = big_value_2;
    if (getBitBigDecimal(big_value_1, index) == 1) {
      for (int i = 0; i < index; i++) {
        value_2_copied = leftshiftBigDecimal(value_2_copied);
      }
      nullBigDecimal(&big_result);
      additionBigDecimal(sum, value_2_copied, &big_result);
      sum = big_result;
    }
  }
  return big_result;
}

int is_unevenBigDeicmal(s21_big_decimal bit) {
  return (getBitBigDecimal(bit, 0)) ? 1 : 0;
}

int s21_bit_divisionBigDeicmal(s21_big_decimal delim, s21_big_decimal delit,
                               s21_big_decimal *chast) {
  nullBigDecimal(chast);
  int flag = 0;
  if ((getSignBigDecimal(delim) == (-1)) ^ (getSignBigDecimal(delit) == (-1))) {
    flag = 1;
  }
  setSignBigDecimal(&delim, 1);
  setSignBigDecimal(&delit, 1);
  if (is_equal_MBigDecimal(delim, delit)) {  // если числа равны
    chast->bits[0] = 1;
  } else if (!check_zeroBigDecimal(delim) &&
             is_greater_MBigDecimal(delim, delit)) {
    s21_big_decimal delitBuf = {0};
    delitBuf = delit;
    div_first_decrementBigDeicmal(delim, delit, &delitBuf,
                                  chast);  // первый этап декремента
  }
  if (flag) {
    setSignBigDecimal(chast, -1);
  }
  return 0;
}

int check_zeroBigDecimal(
    s21_big_decimal decimal) {  // проверка на нулевой decimal
  int res = 0;
  res = 1;
  for (int i = 0; i < 224; ++i) {
    if (getBitBigDecimal(decimal, i) == 1) {
      res = 0;
      break;
    }
  }
  return res;
}

void div_first_decrementBigDeicmal(s21_big_decimal delim, s21_big_decimal delit,
                                   s21_big_decimal *delitBuf,
                                   s21_big_decimal *chast) {
  int count1 = 0;
  while (
      is_greater_or_equal_MBigDecimal(delim, leftshiftBigDecimal(*delitBuf))) {
    *delitBuf = leftshiftBigDecimal(*delitBuf);
    count1++;
  }
  if (count1) {
    degree_of_twoBigDeicmal(chast, count1);  // запись ответа
    s21_big_decimal razn = {0};
    Light_subBigDecimal(delim, *delitBuf, &razn);  // BIG DECIMAL !_!_!_!
    while (is_greater_or_equal_MBigDecimal(razn, delit)) {
      div_second_decrementBigDeicmal(
          delit, delitBuf, chast,
          &razn);  // разность по указателю и декремент внутри функции
    }
  } else {
    chast->bits[0] = 1;
  }
}

void div_second_decrementBigDeicmal(s21_big_decimal delit,
                                    s21_big_decimal *delitBuf,
                                    s21_big_decimal *chast,
                                    s21_big_decimal *razn) {
  int count2 = 0;
  *delitBuf = delit;
  while (
      is_greater_or_equal_MBigDecimal(*razn, leftshiftBigDecimal(*delitBuf))) {
    *delitBuf = leftshiftBigDecimal(*delitBuf);
    count2++;
  }
  Light_subBigDecimal(*razn, *delitBuf, razn);
  nullBigDecimal(delitBuf);
  degree_of_twoBigDeicmal(delitBuf, count2);
  additionBigDecimal(*chast, *delitBuf, chast);
}

void degree_of_twoBigDeicmal(s21_big_decimal *num, int degree) {
  if (degree) {
    num->bits[0] = 1;
    for (int i = 0; i < degree; ++i) {
      *num = leftshiftBigDecimal(*num);
    }
  } else {
    s21_big_decimal one = {0};
    one.bits[0] = 1;
    additionBigDecimal(*num, one, num);
  }
}

void Light_subBigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  nullBigDecimal(result);
  int a = 0;
  switch (getSignBigDecimal(value_1) * getSignBigDecimal(value_2)) {
    case 1:
      a = 0;
      positive_subBigDecimal(value_1, value_2, result, a);
      break;
    case -1:
      if (getSignBigDecimal(value_1) == (-1)) {
        setSignBigDecimal(&value_1, 1);

        additionBigDecimal(value_1, value_2, result);
        setSignBigDecimal(result, -1);
      }
      if (getSignBigDecimal(value_2) == (-1)) {
        setSignBigDecimal(&value_2, 1);
        additionBigDecimal(value_1, value_2, result);
      }
      break;
  }
}

int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             int *power) {
  memset(result, 0, sizeof(s21_decimal));
  int overflow_status = 0;
  for (int index = 0; index < 96; index++) {
    switch (getBit(value_1, index) + getBit(value_2, index) +
            getBit(*result, index)) {
      case 0:
        setBit(result, index, 0);
        break;
      case 1:
        setBit(result, index, 1);
        break;
      case 2:
        if (index != 95) {
          setBit(result, index, 0);
          setBit(result, index + 1, 1);
        } else {
          overflow_status = getAroundOverflow_s21_add(&value_1, &value_2,
                                                      result, index, 2, power);
        }
        break;
      case 3:
        if (index != 95) {
          setBit(result, index, 1);
          setBit(result, index + 1, 1);
        } else {
          overflow_status = getAroundOverflow_s21_add(&value_1, &value_2,
                                                      result, index, 3, power);
        }
        break;
    }
  }
  return overflow_status;
}

void positive_subBigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result, int power) {
  if ((getSignBigDecimal(value_1) == (-1)) &&
      (getSignBigDecimal(value_2) == (-1))) {
    setSignBigDecimal(&value_1, 1);
    setSignBigDecimal(&value_2, 1);
    if (v1_greater_v2BigDecimal(value_1, value_2, result, power)) {
      setSignBigDecimal(result, -1);
    }
    if (v2_greater_v1BigDecimal(value_1, value_2, result, power)) {
      setSignBigDecimal(result, 1);
    }
  } else {
    v1_greater_v2BigDecimal(value_1, value_2, result, power);
    v2_greater_v1BigDecimal(value_1, value_2, result, power);
  }
}

int v1_greater_v2BigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result, int power) {
  int res = 0;
  if (is_greater_MBigDecimal(value_1, value_2)) {
    s21_bit_subBigDecimal(value_1, value_2, result);
    setPowerBigDecimal(result, power);
    res = 1;
  }
  return res;
}
int v2_greater_v1BigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                            s21_big_decimal *result, int power) {
  int res = 0;
  if (is_greater_MBigDecimal(value_2, value_1)) {
    s21_bit_subBigDecimal(value_2, value_1, result);
    setPowerBigDecimal(result, power);
    setSignBigDecimal(result, -1);
    res = 1;
  }
  return res;
}

int setPowerBigDecimal(s21_big_decimal *dec, int power) {
  int is_error = 0;
  if (power < 0) {
    is_error = 1;
  } else {
    clearPowerBigDecimal(dec);
    dec->bits[7] |= power << 16;  // set new power
  }
  return is_error;
}

void clearPowerBigDecimal(s21_big_decimal *dec) {
  int sign = 0;
  if (getSignBigDecimal(*dec) == -1) {
    sign = 1;
  }
  dec->bits[7] = 0;
  if (sign) {
    dec->bits[7] |= 1u << 31;
  }
}

int getSignBigDecimal(s21_big_decimal decimal) {
  return ((decimal.bits[7] >> 31) & 1u) ? -1 : 1;
}

void setSignBigDecimal(s21_big_decimal *decimal, int sign) {
  if (sign == 1) {
    setBitBigDecimal(decimal, 255, 0);
  } else if (sign == -1) {
    setBitBigDecimal(decimal, 255, 1);
  }
}

int is_greater_or_equal_MBigDecimal(s21_big_decimal el1, s21_big_decimal el2) {
  int res = decCmp_MBigDecimal(el1, el2);
  return (res >= 0) ? 1 : 0;
}

int is_greater_MBigDecimal(s21_big_decimal el1, s21_big_decimal el2) {
  int res = decCmp_MBigDecimal(el1, el2);
  return res > 0 ? 1 : 0;
}

int is_equal_MBigDecimal(s21_big_decimal el1, s21_big_decimal el2) {
  int res = decCmp_MBigDecimal(el1, el2);
  return res == 0 ? 1 : 0;
}

int decCmp_MBigDecimal(s21_big_decimal el1, s21_big_decimal el2) {
  int res = 0;
  if (check_zeroBigDecimal(el1)) {
    setSignBigDecimal(&el1, 1);
  }
  if (check_zeroBigDecimal(el2)) {
    setSignBigDecimal(&el2, 1);
  }
  int sign1 = getSignBigDecimal(el1), sign2 = getSignBigDecimal(el2);
  if ((isInfBigDecimal(&el1) == 1 && isInfBigDecimal(&el2) == 0) ||
      (isInfBigDecimal(&el1) == 0 && isInfBigDecimal(&el2) == -1) ||
      (sign1 > sign2)) {  //  первый точно больше
    res = 1;
  } else if ((isInfBigDecimal(&el1) == 0 && isInfBigDecimal(&el2) == 1) ||
             (isInfBigDecimal(&el1) == -1 && isInfBigDecimal(&el2) == 0) ||
             (sign1 < sign2)) {  //  второй точно больше
    res = -1;
  } else {
    res = 0;
    for (int i = 223; i >= 0 && res == 0;
         --i) {  //  сравниваем мантисы побитово, пока равны
      int cur_bit1 = getBitBigDecimal(el1, i),
          cur_bit2 = getBitBigDecimal(el2, i);
      if (cur_bit1 != cur_bit2) {
        res = cur_bit1 - cur_bit2;
      }
    }
    if (sign1 == -1) {  //  инвертируем, если оба отрицательные
      res = -res;
    }
  }
  return res;
}

int isInfBigDecimal(const s21_big_decimal *el) {
  int res = 0;
  if (el != NULL) {
    if (getPowerBigDecimal(*el) == 255 && (el->bits[2] == 0) &&
        (el->bits[1] == 0) && (el->bits[0] == 0) && (el->bits[3] == 0) &&
        (el->bits[4] == 0) && (el->bits[5] == 0) && (el->bits[6] == 0)) {
      res = 1;
    }
    if (getSignBigDecimal(*el) == 1) {
      res = -res;
    }
  }
  return res;
}

int getPowerBigDecimal(s21_big_decimal dec) {
  return (dec.bits[7] >> 16u) & 255;
}

int s21_bit_subBigDecimal(s21_big_decimal bit1, s21_big_decimal bit2,
                          s21_big_decimal *res) {
  int flag = 0;
  int mindone = 0;
  for (int j = 0; j < 96; ++j) {
    if (getBitBigDecimal(bit1, j) && getBitBigDecimal(bit2, j)) {
      and_patternBigDecimal(&mindone, res, j);
    } else if (getBitBigDecimal(bit1, j) == 1 &&
               getBitBigDecimal(bit2, j) == 0) {
      one_zero_patternBigDecimal(&mindone, res, j);
    } else if (getBitBigDecimal(bit1, j) == 0 &&
               getBitBigDecimal(bit2, j) == 1) {
      zero_one_patternBigDecimal(&mindone, res, j);
    } else if (getBitBigDecimal(bit1, j) == 0 &&
               getBitBigDecimal(bit2, j) == 0) {
      and_patternBigDecimal(&mindone, res, j);
    }
  }
  return (flag);
}
void one_zero_patternBigDecimal(int *mindone, s21_big_decimal *res, int j) {
  if (*mindone) {
    setBitBigDecimal(res, j, 0);
    *mindone = 0;
  } else {
    setBitBigDecimal(res, j, 1);
  }
}
void and_patternBigDecimal(int *mindone, s21_big_decimal *res, int j) {
  if (*mindone) {
    setBitBigDecimal(res, j, 1);
  } else {
    setBitBigDecimal(res, j, 0);
  }
}
void zero_one_patternBigDecimal(int *mindone, s21_big_decimal *res, int j) {
  if (*mindone) {
    setBitBigDecimal(res, j, 0);
  } else {
    *mindone = 1;
    setBitBigDecimal(res, j, 1);
  }
}