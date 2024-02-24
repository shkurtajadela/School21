#include "../helpers/s21_helpfunc.h"
#include "../s21_decimal.h"
#include "s21_arithmetic.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) {
    exit(1);
  }
  memset(result, 0, sizeof(s21_decimal));
  s21_error_type error = {0};
  if (checkErrorMul(value_1, value_2, &error)) {
    int power_result = makePower(value_1, value_2);
    if (checkForOverflow(value_1, value_2)) {
      int overflow_status = multiplicationBigDecimal(
          decimalToBigDecimal(value_1), decimalToBigDecimal(value_2), result,
          power_result);
      if (overflow_status) {
        if (getSign(value_1) == 1) {
          makeInf(result);
          error.plus_inf++;
        } else {
          makeNegInf(result);
          error.minus_inf++;
        }
      }
    } else {
      multiplication(value_1, value_2, result);
    }
    setPower(result, power_result > 28 ? 28
                     : (!getPower(value_1) || (!getPower(value_2)))
                         ? (getPower(value_1) + getPower(value_2))
                         : power_result);
    if ((getSign(value_1) * getSign(value_2)) == 1) {
      setBit(result, 127, 0);
    } else {
      setBit(result, 127, 1);
    }
  }
  return error.plus_inf ? 1 : error.minus_inf ? 2 : error.nan ? 3 : 0;
}

int makePower(s21_decimal value_1, s21_decimal value_2) {
  int power_1 = getPower(value_1);
  int power_2 = getPower(value_2);
  if (power_1 == 0) {
    power_1++;
  }
  if (power_2 == 0) {
    power_2++;
  }
  int result = power_1 * power_2;
  if (result == 1) {
    result--;
  } else {
    result = power_1 + power_2;
  }
  return result;
}

int checkForOverflow(s21_decimal value_1, s21_decimal value_2) {
  int overflow_status = 0;
  int position_of_value_1 = 96;
  int position_of_value_2 = 96;
  find_one(value_1, &position_of_value_1);
  find_one(value_2, &position_of_value_2);
  if (position_of_value_1 == 96) position_of_value_1 = 0;
  if (position_of_value_2 == 96) position_of_value_2 = 0;
  if ((position_of_value_1 + position_of_value_2) >= 96) {
    overflow_status++;
  }
  return overflow_status;
}

void multiplication(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  s21_decimal value_2_copied = value_2;
  s21_decimal sum = {0};
  for (int index = 0; index < 96; index++) {
    value_2_copied = value_2;
    if (getBit(value_1, index) == 1) {
      for (int i = 0; i < index; i++) {
        value_2_copied = leftshift(value_2_copied);
        setBit(&value_2_copied, 96, 0);
      }
      memset(result, 0, sizeof(s21_decimal));
      int a = 0;
      addition(sum, value_2_copied, result, &a);
      sum = *result;
    }
  }
}

int multiplicationBigDecimal(s21_big_decimal big_value_1,
                             s21_big_decimal big_value_2, s21_decimal *result,
                             int power_result) {
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
  if (power_result > 28) {
    while (power_result - 28) {
      big_result = bank_roundBigDeicmal(big_result);
      power_result--;
    }
  }
  return bigDecimalToDecimal(big_result, result, power_result);
}

s21_big_decimal decimalToBigDecimal(s21_decimal value) {
  s21_big_decimal result = {0};
  result.bits[0] = value.bits[0];
  result.bits[1] = value.bits[1];
  result.bits[2] = value.bits[2];
  result.bits[7] = value.bits[3];
  return result;
}

int checkForOverflowBigDecimal(s21_big_decimal value, int power_result) {
  while (power_result != 0) {
    value = bank_roundBigDeicmal(value);
    power_result--;
  }
  int overflow_status = 0;
  int position = 223;
  find_oneBigDecimal(value, &position);
  if (position == 223) position = 0;
  if (position >= 96) {
    overflow_status++;
  }
  return overflow_status;
}

int bigDecimalToDecimal(s21_big_decimal value, s21_decimal *result,
                        int power_result) {
  int overflow_status = 0;
  if (checkForOverflowBigDecimal(value, power_result)) {
    overflow_status++;
  }
  int position = 223;
  find_oneBigDecimal(value, &position);
  int index_big_decimal = position;
  int index = 95;
  for (; ((index_big_decimal >= position - 95) && (index_big_decimal >= 0));
       index_big_decimal--, index--) {
    if (getBitBigDecimal(value, index_big_decimal) == 1) {
      setBit(result, index, 1);
    } else {
      setBit(result, index, 0);
    }
  }
  return overflow_status;
}

void nullBigDecimal(s21_big_decimal *value) {
  for (int i = 0; i < 7; i++) {
    value->bits[i] = 0;
  }
}

int getBitBigDecimal(s21_big_decimal decimal, int index) {
  return (index >= 0 && index < 256)
             ? !!(decimal.bits[index / 32] & (1u << (index % 32)))
             : -1;
}

int setBitBigDecimal(s21_big_decimal *decimal, int index, int value) {
  if (index >= 0 && index < 256) {
    if (value) {
      decimal->bits[index / 32] |= (1u << (index % 32));
    } else {
      decimal->bits[index / 32] &= ~(1u << (index % 32));
    }
  }
  return (index >= 0 && index < 256) ? 1 : -1;
}

s21_big_decimal leftshiftBigDecimal(s21_big_decimal bit) {
  for (int i = 223; find_oneBigDecimal(bit, &i); i--) {
    setBitBigDecimal(&bit, i, 0);
    setBitBigDecimal(&bit, i + 1, 1);
  }
  return bit;
}

int find_oneBigDecimal(s21_big_decimal bit, int *pos) {
  int flag = 0;
  for (int i = *pos; i >= 0; i--) {
    if (getBitBigDecimal(bit, i) == 1) {
      *pos = i;
      flag = 1;
      break;
    }
  }
  return (flag);
}

void additionBigDecimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result) {
  nullBigDecimal(result);
  for (int index = 0; index < 224; index++) {
    switch (getBitBigDecimal(value_1, index) +
            getBitBigDecimal(value_2, index) +
            getBitBigDecimal(*result, index)) {
      case 0:
        setBitBigDecimal(result, index, 0);
        break;
      case 1:
        setBitBigDecimal(result, index, 1);
        break;
      case 2:
        setBitBigDecimal(result, index, 0);
        setBitBigDecimal(result, index + 1, 1);
        break;
      case 3:
        setBitBigDecimal(result, index, 1);
        setBitBigDecimal(result, index + 1, 1);
        break;
    }
  }
}
