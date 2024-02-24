#include "s21_helpfunc.h"

#include "../s21_arithmetic/s21_arithmetic.h"
#include "../s21_decimal.h"

//  begin bits[3] spec functions

// memset в сочентании с проверкой
void memcheck(s21_decimal *result) {
  if (result == NULL) {
    exit(1);
  }
  memset(result, 0, sizeof(s21_decimal));
}

int getPower(s21_decimal dec) { return (dec.bits[3] >> 16u) & 255; }

void clearPower(s21_decimal *dec) {
  int sign = 0;
  if (getSign(*dec) == -1) {
    sign = 1;
  }
  dec->bits[3] = 0;
  if (sign) {
    dec->bits[3] |= 1u << 31;
  }
}

int setPower(s21_decimal *dec, int power) {
  int is_error = 0;
  if (power < 0) {
    is_error = 1;
  } else {
    clearPower(dec);
    dec->bits[3] |= power << 16;  // set new power
  }
  return is_error;
}

int getSign(s21_decimal decimal) {
  return ((decimal.bits[3] >> 31) & 1u) ? -1 : 1;
}

void setSign(s21_decimal *decimal, int sign) {
  if (sign == 1) {
    setBit(decimal, 127, 0);
  } else if (sign == -1) {
    setBit(decimal, 127, 1);
  }
}

////
// end bits[3] spec functions
///////////////////////////////////////////////////////
//  start getSet bit
////
int getBit(s21_decimal decimal, int index) {
  int res = 0;
  res = subGetBit(decimal.bits[(int)(index / 32)], (int)index % 32);
  return res;
}

int subGetBit(uint32_t bits, int pos) {  // вспомогательная по getBit
  int res = 0;
  if (bits & (1 << pos)) {
    res = 1;
  }
  return (res);
}

int setBit(s21_decimal *decimal, int index, int value) {
  if (index >= 0 && index < 128) {
    if (value) {
      decimal->bits[index / 32] |= (1u << (index % 32));
    } else {
      decimal->bits[index / 32] &= ~(1u << (index % 32));
    }
  }
  return (index >= 0 && index < 128) ? 1 : -1;
}
////
//  end getSet bit
/////////////////////////////////////
