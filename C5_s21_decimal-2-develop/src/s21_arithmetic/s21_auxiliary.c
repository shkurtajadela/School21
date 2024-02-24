#include "../s21_decimal.h"

// GET_FUNCTIONS

// returns a bit from decimal by the specified number (0..127)
int s21_decimal_get_bit(s21_decimal dst, int index) {
  int num_int = index / 32;
  int num_bit = index % 32;
  return (dst.bits[num_int] & (1u << num_bit)) >> num_bit;
}

// returns the power of 10 in decimal
int s21_decimal_get_scale(s21_decimal src) {
  int exp = src.bits[3];
  if (exp & (1 << 31U)) exp &= ~(1u << 31);
  exp >>= 16u;
  return exp;
}

// returns decimal sign
// 1 - '-'
// 0 - '+'
int s21_decimal_get_sign(s21_decimal vl) {
  int ret_val = 0;
  if (vl.bits[0] != 0 || vl.bits[1] != 0 || vl.bits[2] != 0) {
    if (vl.bits[3] & (1 << 31U)) {
      ret_val = 1;
    }
  }
  return ret_val;
}

// SET_FUNCTIONS

// sets the specified bit to decimal by number
void s21_decimal_set_bit(s21_decimal *dst, int index, int bit) {
  int num_int = index / 32;
  int num_bit = index % 32;
  if (bit == 0) {
    dst->bits[num_int] &= ~(1u << num_bit);
  } else {
    dst->bits[num_int] |= (1u << num_bit);
  }
}

// sets the power of 10 to decimal
void s21_decimal_set_scale(s21_decimal *dst, int exp) {
  for (int i = 31; i >= 0; i--) {
    int bin = (exp >> i) & 1;
    if (i < 7) s21_decimal_set_bit(dst, i + 96 + 16, bin);
  }
}

bool s21_decimal_get_sign_bool(s21_decimal dec) {
  return s21_int_get_bit(dec.bits[3], 31);
}

// sets the decimal sign
// 1 - '-'
// 0 - '+'
void s21_decimal_set_sign(s21_decimal *dst, int sign) {
  s21_decimal_set_bit(dst, 127, sign);
}

// sets all decimal bits to zero
void s21_decimal_set_zero(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

// SCALE_FUNCTIONS

// brings two decimal values to the same dimension
// 0 - successful
// 1 - NULL
int s21_convert_to_same_scale(s21_decimal *vl_1, s21_decimal *vl_2, int round) {
  int ret_val = 0;
  if (vl_1 == NULL || vl_2 == NULL) {
    ret_val = 1;  // NULL input case
  } else {
    int scale_1 = s21_decimal_get_scale(*vl_1);
    int scale_2 = s21_decimal_get_scale(*vl_2);
    int diff_scale = scale_1 - scale_2;
    if (diff_scale != 0) {
      s21_decimal *greater_decimal = diff_scale < 0 ? vl_1 : vl_2;
      s21_decimal *less_decimal = diff_scale < 0 ? vl_2 : vl_1;
      for (int i = 0; i < abs(diff_scale); i++) {
        if (s21_scale_shifter(greater_decimal, 1, round) == 1) {
          s21_scale_shifter(less_decimal, -1, round);
        }
      }
    }
  }
  return ret_val;
}

// shifts the decimal number one position to the right
// changes the degree of 10
// 0 - successful
// 1 - beyond decimal boundaries (> 28)
int shift_one_step_forward(s21_decimal *vl) {
  int ret_val = 0;
  unsigned long long MAX_UNS = 4294967295;
  unsigned long long mant_bits_0 = 10 * (unsigned long long)vl->bits[0];
  unsigned long long mant_bits_1 = 10 * (unsigned long long)vl->bits[1];
  unsigned long long mant_bits_2 = 10 * (unsigned long long)vl->bits[2];
  if ((((mant_bits_2 >> 32) & MAX_UNS) == 0) &&
      (mant_bits_2 & MAX_UNS) + ((mant_bits_1 >> 32) & MAX_UNS) < MAX_UNS) {
    vl->bits[0] = mant_bits_0 & MAX_UNS;
    vl->bits[1] = (mant_bits_1 & MAX_UNS) + ((mant_bits_0 >> 32) & MAX_UNS);
    vl->bits[2] = (mant_bits_2 & MAX_UNS) + ((mant_bits_1 >> 32) & MAX_UNS);
    s21_decimal_set_scale(vl, s21_decimal_get_scale(*vl) + 1);
  } else {
    ret_val = 1;  //  err overflow bits[2]
  }
  return ret_val;
}

// shifts the decimal number one position to the left
// changes the degree of 10
// 0 - successful
// 1 - beyond decimal boundaries (< 0)
int shift_one_step_behind(s21_decimal *vl, int shift, int round, int i) {
  int ret_val = 0;
  unsigned long long MAX_UNS = 4294967295;
  unsigned long long mant_bits_1_0 = 0;
  unsigned long long mant_bits_2_1 = 0;
  mant_bits_2_1 = (((unsigned long long)vl->bits[2] & MAX_UNS) << 32) +
                  (unsigned long long)vl->bits[1];
  vl->bits[2] = (mant_bits_2_1 / 10) >> 32;
  vl->bits[1] = (mant_bits_2_1 / 10) & MAX_UNS;
  mant_bits_1_0 =
      ((mant_bits_2_1 % 10) << 32) + (unsigned long long)vl->bits[0];
  vl->bits[0] = (mant_bits_1_0 / 10) & MAX_UNS;
  if (round == 1 && i == abs(shift) - 1 &&
      (mant_bits_1_0 % 10 > 5 ||
       (mant_bits_1_0 % 10 == 5 && vl->bits[0] % 2 == 1))) {  // bank rounding
    s21_decimal one = {{1, 0, 0, vl->bits[3]}};
    if (s21_decimal_get_sign(*vl)) {
      s21_decimal_invert_sign(&one);
    }
    if (s21_add(*vl, one, vl)) {
      ret_val = 1;
    }
  }
  if (round == 2 && i == abs(shift) - 1 &&
      mant_bits_1_0 % 10 >= 5) {  // arithmetic rounding
    s21_decimal one = {{1, 0, 0, vl->bits[3]}};
    if (s21_add(*vl, one, vl)) {
      ret_val = 1;
    }
  }
  return ret_val;
}

// shifts the decimal number by shift positions, with the corresponding
// changes the degree of 10
// Возвращает 0 в случае успеха
// 1 - beyond decimal boundaries (< 0 or > 28)
int s21_scale_shifter(s21_decimal *vl, int shift, int round) {
  int ret_val = 0;
  if (vl == NULL) {
    ret_val = 1;  // NULL input
  } else {
    int new_scale = s21_decimal_get_scale(*vl) + shift;
    if (new_scale < 0 ||
        new_scale > 28) {  // beyond decimal boundaries (< 0 or > 28)
      ret_val = 1;

    } else if (shift > 0) {
      // multiplying the mantissa by 10
      for (int i = 0; i < shift && !ret_val; i++) {
        ret_val = shift_one_step_forward(vl);
      }

    } else if (shift < 0) {
      // dividing the mantissa by 10
      for (int i = 0; i < abs(shift); i++) {
        ret_val = shift_one_step_behind(vl, shift, round, i);
      }
      s21_decimal_set_scale(vl, new_scale);
    }
  }
  return ret_val;
}

// bringing two decimal to the same dimension
void s21_decimal_rescale(s21_decimal *value_1, s21_decimal *value_2) {
  s21_dbl_decimal dbl_dec_value_1 = s21_decimal_to_dbl_decimal(*value_1);
  s21_dbl_decimal dbl_dec_value_2 = s21_decimal_to_dbl_decimal(*value_2);
  s21_decimal_rescale_dbl_dec(&dbl_dec_value_1, &dbl_dec_value_2);
  *value_1 = s21_dbl_decimal_to_decimal(dbl_dec_value_1);
  *value_2 = s21_dbl_decimal_to_decimal(dbl_dec_value_2);
}

// OTHER_FUNCTIONS

// checking decimal for equality to zero
int s21_decimal_is_zero(s21_decimal dec) {
  return !(dec.bits[0] + dec.bits[1] + dec.bits[2]);
}

// inversion of the decimal sign
void s21_decimal_invert_sign(s21_decimal *dst) { dst->bits[3] ^= (1 << 31); }

// returns a bit from int at the specified position
bool s21_int_get_bit(unsigned int num, int pos) { return (num >> pos) & 1; }
