// #include "../s21_decimal.h"
#include "s21_helpfunc.h"

void s21_powNormilize(s21_decimal* value1, s21_decimal* value2) {
  int sign_value1 = getSign(*value1);
  int sign_value2 = getSign(*value2);

  int power_value1 = getPower(*value1);
  int power_value2 = getPower(*value2);
  if ((power_value1 > 28) || (power_value2 > 28)) {
    powerValueTo28(value1, power_value1);  // хотя бы 1 > 28
    powerValueTo28(value2, power_value2);
    setPower(value1, 28);
    setPower(value2, 28);
  } else {  // оба меньше или равны 28
    if (power_value1 >= power_value2) {
      powerValueToXUp(value2, power_value1, &power_value2);
      powerValueToXDown(value1, &power_value1, power_value2);
      setPower(value2, power_value2);
      setPower(value1, power_value2);
    } else {
      powerValueToXUp(value1, power_value2, &power_value1);
      powerValueToXDown(value2, &power_value2, power_value1);
      setPower(value1, power_value1);
      setPower(value2, power_value1);
    }
  }

  setSign(value1, sign_value1);
  setSign(value2, sign_value2);
}

void powerValueTo28(s21_decimal* value, int power) {
  s21_decimal result = {0};
  s21_decimal decimal_ten = {0};
  decimal_ten.bits[0] = 10;
  while (power - 28) {
    if (power > 28) {
      result = bank_round(*value);
    } else {
      s21_mul(*value, decimal_ten, &result);
    }
    *value = result;
    power > 28 ? power-- : power++;
  }
}

void powerValueToXUp(s21_decimal* value, int power, int* lesser_power) {
  s21_decimal result = {0};
  s21_decimal decimal_ten = {0};
  decimal_ten.bits[0] = 10;
  while ((power - *lesser_power) && (!checkForOverflow(*value, decimal_ten))) {
    s21_mul(*value, decimal_ten, &result);
    *value = result;
    power > *lesser_power ? ++*lesser_power : 0;
  }
}

void powerValueToXDown(s21_decimal* value, int* power_1, int power_2) {
  while (*power_1 - power_2) {
    *value = bank_round(*value);
    *power_1 > power_2 ? --*power_1 : 0;
  }
}
