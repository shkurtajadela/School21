#include "../s21_decimal.h"

// ARITHMETIC_FUNCTIONS

// the sum of two dbl_decimal
// 0 - successful
// 1 - too large or equal to infinity

int s21_add_dbl_decimal(s21_dbl_decimal dbl_dec_value_1,
                        s21_dbl_decimal dbl_dec_value_2,
                        s21_dbl_decimal *dbl_dec_result) {
  int return_code = 0;
  bool t_bit = 0;  // бит переноса
  s21_dbl_decimal_set_zero(dbl_dec_result);
  for (int i = 0; i < 192; i++) {
    dbl_dec_result->bits[i] =
        (dbl_dec_value_1.bits[i] ^ dbl_dec_value_2.bits[i]) ^ t_bit;
    if ((dbl_dec_value_1.bits[i] & dbl_dec_value_2.bits[i]) ||
        (dbl_dec_value_1.bits[i] & t_bit) || (dbl_dec_value_2.bits[i] & t_bit))
      t_bit = 1;
    else
      t_bit = 0;
  }
  dbl_dec_result->scale = dbl_dec_value_1.scale;
  dbl_dec_result->sign = dbl_dec_value_1.sign;
  if (s21_dbl_decimal_highest_bit(*dbl_dec_result) > 95) {
    if (dbl_dec_result->scale <= 0) {
      return_code = 1;
    } else {
      int mod = s21_dbl_decimal_mod_by_ten(dbl_dec_result);
      s21_dbl_decimal_bank_rounding(dbl_dec_result, mod);
    }
  }
  return return_code;
}

// multiplication of two dbl_decimal
// 0 - successful
// 1- too large or equal to infinity
// 2 - too little or equal to negative infinity
int s21_mul_dbl_decimal(s21_dbl_decimal dbl_dec_value_1,
                        s21_dbl_decimal dbl_dec_value_2,
                        s21_dbl_decimal *dbl_dec_result) {
  int return_code = 0;
  s21_dbl_decimal_set_zero(dbl_dec_result);
  if (!s21_dbl_decimal_is_zero(dbl_dec_value_1) &&
      !(s21_dbl_decimal_is_zero(dbl_dec_value_2))) {
    for (int i = 0; i < 192; i++) {
      if (dbl_dec_value_2.bits[i] == 1)
        s21_add_dbl_decimal(*dbl_dec_result, dbl_dec_value_1, dbl_dec_result);
      s21_dbl_decimal_left_shift(&dbl_dec_value_1);
    }
    dbl_dec_result->scale = dbl_dec_value_1.scale + dbl_dec_value_2.scale;
    dbl_dec_result->sign = dbl_dec_value_1.sign ^ dbl_dec_value_2.sign;
    if (s21_dbl_decimal_highest_bit(*dbl_dec_result) > 95 ||
        dbl_dec_result->scale > 28) {
      int mod = 0;
      while (dbl_dec_result->scale > 0 &&
             (s21_dbl_decimal_highest_bit(*dbl_dec_result) > 95 ||
              dbl_dec_result->scale > 28) &&
             dbl_dec_result->scale != 0) {
        mod = s21_dbl_decimal_mod_by_ten(dbl_dec_result);
      }
      if (dbl_dec_result->scale > 0)
        s21_dbl_decimal_bank_rounding(dbl_dec_result, mod);
      else
        return_code = 1;
    }
    if (s21_dbl_decimal_is_zero(*dbl_dec_result)) return_code = 2;
  }
  return return_code;
}

// the difference of two decimal
// 0 - successful
int s21_sub_dbl_decimal(s21_dbl_decimal dbl_dec_value_1,
                        s21_dbl_decimal dbl_dec_value_2,
                        s21_dbl_decimal *dbl_dec_result) {
  int return_code = 0;
  bool t_bit = 0;
  for (int i = 0; i < 192; i++) {
    dbl_dec_result->bits[i] =
        dbl_dec_value_1.bits[i] ^ dbl_dec_value_2.bits[i] ^ t_bit;
    if (dbl_dec_value_1.bits[i] == 0 && dbl_dec_value_2.bits[i] == 1)
      t_bit = 1;
    else if (dbl_dec_value_1.bits[i] == 1 && dbl_dec_value_2.bits[i] == 0)
      t_bit = 0;
  }
  return return_code;
}

// CONVERSION_FUNCTIONS

// decimal --> dbl_decimal
s21_dbl_decimal s21_decimal_to_dbl_decimal(s21_decimal dec) {
  s21_dbl_decimal dbl_dec;
  s21_dbl_decimal_set_zero(&dbl_dec);
  dbl_dec.sign = s21_decimal_get_sign_bool(dec);
  dbl_dec.scale = s21_decimal_get_scale(dec);
  int i = 0;
  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < 32; k++)
      dbl_dec.bits[i++] = s21_int_get_bit(dec.bits[j], k);
  }
  return dbl_dec;
}

// dbl_decimal --> decimal
s21_decimal s21_dbl_decimal_to_decimal(s21_dbl_decimal dbl_dec) {
  s21_decimal dec;
  s21_decimal_set_zero(&dec);
  int k = 95;
  for (int i = 2; i >= 0; i--)
    for (int j = 31; j >= 0; j--)
      dec.bits[i] = (dec.bits[i] << 1) + dbl_dec.bits[k--];
  dec.bits[3] = dbl_dec.sign;
  dec.bits[3] <<= 7;
  k = 128;
  for (int i = 7; i >= 0; i--) {
    dec.bits[3] <<= 1;
    if (dbl_dec.scale >= k) {
      dbl_dec.scale -= k;
      dec.bits[3]++;
    }
    k >>= 1;
  }
  dec.bits[3] <<= 16;
  return dec;
}

// SHIFT_FUNCTIONS

// right shift dbl_decimal
void s21_dbl_decimal_right_shift(s21_dbl_decimal *dbl_dec) {
  for (int i = 0; i < 191; i++) dbl_dec->bits[i] = dbl_dec->bits[i + 1];
  dbl_dec->bits[191] = 0;
}

// left shift dbl_decimal
void s21_dbl_decimal_left_shift(s21_dbl_decimal *dbl_dec) {
  for (int i = 191; i > 0; i--) dbl_dec->bits[i] = dbl_dec->bits[i - 1];
  dbl_dec->bits[0] = 0;
}

// SCALE_FUNCTIONS

// bringing two dbl_decimals to the same dimension
void s21_decimal_rescale_dbl_dec(s21_dbl_decimal *dbl_dec_value_1,
                                 s21_dbl_decimal *dbl_dec_value_2) {
  s21_dbl_decimal ten;
  s21_dbl_decimal_set_zero(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  if (!s21_dbl_decimal_is_zero(*dbl_dec_value_1) &&
      !s21_dbl_decimal_is_zero(*dbl_dec_value_2)) {
    if (dbl_dec_value_1->scale > dbl_dec_value_2->scale) {
      int scale_dif = dbl_dec_value_1->scale - dbl_dec_value_2->scale;
      for (int i = 0; i < scale_dif; i++)
        s21_mul_dbl_decimal(*dbl_dec_value_2, ten, dbl_dec_value_2);
      if (s21_dbl_decimal_highest_bit(*dbl_dec_value_2) > 95) {
        s21_dbl_decimal_rescale_bank_rounding(dbl_dec_value_1, dbl_dec_value_2);
      }
      dbl_dec_value_2->scale = dbl_dec_value_1->scale;
    } else if (dbl_dec_value_2->scale > dbl_dec_value_1->scale) {
      s21_decimal_rescale_dbl_dec(dbl_dec_value_2, dbl_dec_value_1);
    }
  } else if (s21_dbl_decimal_is_zero(*dbl_dec_value_1)) {
    dbl_dec_value_1->scale = dbl_dec_value_2->scale;
  } else {
    dbl_dec_value_2->scale = dbl_dec_value_1->scale;
  }
}

// bank rounding on overflow
void s21_dbl_decimal_rescale_bank_rounding(s21_dbl_decimal *dbl_dec_value_1,
                                           s21_dbl_decimal *dbl_dec_value_2) {
  int mod1 = 0, mod2 = 0;
  while (s21_dbl_decimal_highest_bit(*dbl_dec_value_2) > 95) {
    mod1 = s21_dbl_decimal_mod_by_ten(dbl_dec_value_1);
    mod2 = s21_dbl_decimal_mod_by_ten(dbl_dec_value_2);
  }
  s21_dbl_decimal_bank_rounding(dbl_dec_value_1, mod1);
  s21_dbl_decimal_bank_rounding(dbl_dec_value_2, mod2);
  if (s21_dbl_decimal_highest_bit(*dbl_dec_value_2) > 95) {
    mod1 = s21_dbl_decimal_mod_by_ten(dbl_dec_value_1);
    mod2 = s21_dbl_decimal_mod_by_ten(dbl_dec_value_2);
    s21_dbl_decimal_bank_rounding(dbl_dec_value_1, mod1);
    s21_dbl_decimal_bank_rounding(dbl_dec_value_2, mod2);
  }
}

// bringing two dbl_decimals to the same dimension taking into account scale
void s21_dbl_decimal_rescale_to_zero(s21_dbl_decimal *dbl_dec_value_1,
                                     s21_dbl_decimal *dbl_dec_value_2) {
  s21_dbl_decimal ten;
  s21_dbl_decimal_set_zero(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  if (dbl_dec_value_1->scale > dbl_dec_value_2->scale) {
    dbl_dec_value_1->scale -= dbl_dec_value_2->scale;
    dbl_dec_value_2->scale = 0;
    while (dbl_dec_value_1->scale != 0) {
      dbl_dec_value_1->scale--;
      s21_mul_dbl_decimal(*dbl_dec_value_2, ten, dbl_dec_value_2);
    }
  } else {
    dbl_dec_value_2->scale -= dbl_dec_value_1->scale;
    dbl_dec_value_1->scale = 0;
    while (dbl_dec_value_2->scale != 0) {
      dbl_dec_value_2->scale--;
      s21_mul_dbl_decimal(*dbl_dec_value_1, ten, dbl_dec_value_1);
    }
  }
}

// SET_FUNCTIONS

// sets all bits of dbl_decimal to zero
void s21_dbl_decimal_set_zero(s21_dbl_decimal *dbl_dec) {
  dbl_dec->sign = 0;
  dbl_dec->scale = 0;
  for (int i = 0; i < 192; i++) dbl_dec->bits[i] = 0;
}

// OTHER_FUNCTIONS

// returns the remainder of dividing dbl_decimal by 10
int s21_dbl_decimal_mod_by_ten(s21_dbl_decimal *dbl_dec) {
  s21_dbl_decimal result;
  s21_dbl_decimal_set_zero(&result);
  int scale = dbl_dec->scale;
  int sign = dbl_dec->sign;
  s21_dbl_decimal ten;
  s21_dbl_decimal_set_zero(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  s21_dbl_decimal div_res = s21_dbl_decimal_simple_div(*dbl_dec, ten, dbl_dec);
  int res = s21_dbl_decimal_to_decimal(div_res).bits[0];
  dbl_dec->scale = scale - 1;
  dbl_dec->sign = sign;
  return res;
}

// bank rounding dbl_decimal
void s21_dbl_decimal_bank_rounding(s21_dbl_decimal *dbl_dec, int mod) {
  if ((mod == 5 && dbl_dec->bits[0]) || mod > 5) {
    s21_dbl_decimal one;
    s21_dbl_decimal_set_zero(&one);
    one.bits[0] = 1;
    one.scale = dbl_dec->scale;
    one.sign = dbl_dec->sign;
    s21_add_dbl_decimal(*dbl_dec, one, dbl_dec);
    if (s21_dbl_decimal_highest_bit(*dbl_dec) > 95) {
      s21_sub_dbl_decimal(*dbl_dec, one, dbl_dec);
      mod = s21_dbl_decimal_mod_by_ten(dbl_dec);
      s21_dbl_decimal_bank_rounding(dbl_dec, mod);
    }
  }
}

// division of the mantissa
s21_dbl_decimal s21_dbl_decimal_simple_div(s21_dbl_decimal dbl_dec_value_1,
                                           s21_dbl_decimal dbl_dec_value_2,
                                           s21_dbl_decimal *dbl_dec_result) {
  int highest_bit_vl2 = s21_dbl_decimal_highest_bit(dbl_dec_value_2);
  s21_dbl_decimal div_res;
  s21_dbl_decimal_set_zero(&div_res);
  s21_dbl_decimal_set_zero(dbl_dec_result);
  if (s21_dbl_decimal_compare_bits(dbl_dec_value_1, dbl_dec_value_2)) {
    s21_dbl_decimal_align(&dbl_dec_value_1, &dbl_dec_value_2);
  }
  bool flag = 0;
  for (int i = 0; i < 191 && !flag; i++) {
    if (s21_dbl_decimal_compare_bits(dbl_dec_value_1, dbl_dec_value_2)) {
      s21_sub_dbl_decimal(dbl_dec_value_1, dbl_dec_value_2, &dbl_dec_value_1);
      dbl_dec_result->bits[0] = 1;
    }
    if (s21_dbl_decimal_highest_bit(dbl_dec_value_2) <= highest_bit_vl2)
      flag = 1;
    if (!flag) {
      if (s21_dbl_decimal_highest_bit(dbl_dec_value_2) > highest_bit_vl2)
        s21_dbl_decimal_right_shift(&dbl_dec_value_2);
      s21_dbl_decimal_left_shift(dbl_dec_result);
    }
  }
  return dbl_dec_value_1;
}

// returns whole digits dbl_decimal
void s21_dbl_decimal_truncate(s21_dbl_decimal *dbl_dec_value) {
  while (dbl_dec_value->scale > 0) s21_dbl_decimal_mod_by_ten(dbl_dec_value);
}

// comparing the bits of the first and second dbl_decimal
// does not take into account the exponent
// 1 - dbl_dec1 >= dbl_dec2
// 0 - dbl_dec2 > dbl_dec1
bool s21_dbl_decimal_compare_bits(s21_dbl_decimal dbl_dec1,
                                  s21_dbl_decimal dbl_dec2) {
  int i = 191;
  while (i >= 0 && dbl_dec1.bits[i] == dbl_dec2.bits[i]) {
    i--;
  }
  return i == -1 ? 1 : dbl_dec1.bits[i];
}

// checking dbl_decimal for zero
bool s21_dbl_decimal_is_zero(s21_dbl_decimal dbl_dec) {
  bool result = 0;
  for (int i = 0; i < 192; i++) result += dbl_dec.bits[i];
  return !result;
}

// returns the position of the highest bit
int s21_dbl_decimal_highest_bit(s21_dbl_decimal dbl_dec) {
  int i = -1;
  if (!s21_dbl_decimal_is_zero(dbl_dec)) {
    for (i = 191; i >= 0 && dbl_dec.bits[i] != 1; i--) {
    }
  }
  return i;
}

// bringing the mantissas of two dbl_decimal to the same dimension
void s21_dbl_decimal_align(s21_dbl_decimal *dbl_dec_value_1,
                           s21_dbl_decimal *dbl_dec_value_2) {
  if (!s21_dbl_decimal_is_zero(*dbl_dec_value_1) &&
      !s21_dbl_decimal_is_zero(*dbl_dec_value_2)) {
    int l1 = s21_dbl_decimal_highest_bit(*dbl_dec_value_1);
    int l2 = s21_dbl_decimal_highest_bit(*dbl_dec_value_2);
    while (s21_dbl_decimal_highest_bit(*dbl_dec_value_1) !=
           s21_dbl_decimal_highest_bit(*dbl_dec_value_2)) {
      if (s21_dbl_decimal_compare_bits(*dbl_dec_value_1, *dbl_dec_value_2))
        s21_dbl_decimal_left_shift(dbl_dec_value_2);
      else
        s21_dbl_decimal_left_shift(dbl_dec_value_1);
    }
    if (!s21_dbl_decimal_compare_bits(*dbl_dec_value_1, *dbl_dec_value_2))
      s21_dbl_decimal_left_shift(dbl_dec_value_1);
    if (dbl_dec_value_1->bits[0] == 0 && dbl_dec_value_2->bits[0] == 0 &&
        s21_dbl_decimal_highest_bit(*dbl_dec_value_1) > l1 &&
        s21_dbl_decimal_highest_bit(*dbl_dec_value_2) > l2) {
      s21_dbl_decimal_right_shift(dbl_dec_value_1);
      s21_dbl_decimal_right_shift(dbl_dec_value_2);
    }
  }
}
