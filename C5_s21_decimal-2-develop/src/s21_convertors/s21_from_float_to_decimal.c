#include "../s21_decimal.h"

// zeroes the cut-off part of the array from the <start> position to 0
void s21_clear_garbage(int start, char *src_arr) {
  for (int i = start; i >= 0; i--) src_arr[i] = 0;
}

// bank rounding of an array of decimal digits
// from the <start_significant_part>
void s21_bankers_rounding(int start_significant_part, char *src_arr) {
  int tail = src_arr[start_significant_part];
  int pre_tail = src_arr[start_significant_part + 1];
  if (tail > 5 || (tail == 5 && pre_tail % 2 != 0)) {
    if (pre_tail == 9) {
      int i = 1;
      src_arr[start_significant_part + 1]++;
      while (src_arr[start_significant_part + i] == 10 &&
             start_significant_part + i < 96) {
        src_arr[start_significant_part + i] = 0;
        src_arr[start_significant_part + 1 + i]++;
        i++;
      }
    } else {
      src_arr[start_significant_part + 1]++;
    }
  }
  s21_clear_garbage(start_significant_part, src_arr);
}

// converting an integer part of a float to an array of decimal digits
int s21_float_to_array_up(float abs_src, char *src_arr) {
  int digit = 0;
  int i = 0;
  while (abs_src >= 1.0) {
    digit = (int)fmod(abs_src, 10.0);
    abs_src /= 10.0;
    src_arr[i] = digit;
    i++;
  }
  return i;
}

// converting the fractional part of float to an array of decimal digits
int s21_float_to_array_down(float abs_src, char *src_arr) {
  int digit = 0;
  int count = 0;
  int flag = 0;
  int i = 0;
  while ((i != 29) && (count != 8)) {
    abs_src *= 10.0;
    digit = fmod(abs_src, 10.0);
    src_arr[i] = digit;
    if (digit != 0) flag = 1;
    if (flag) count++;
    i++;
  }
  return i;
}

// array flip
void s21_reverse_arr(char *src_arr, int size) {
  char buf_arr[36] = {0};
  for (int i = 0; i < size; i++) buf_arr[size - i - 1] = src_arr[i];
  for (int i = 0; i < size; i++) src_arr[i] = buf_arr[i];
}

// removing zeros in the array starting from the <end_src> position
// returns a position with a non-zero element
int s21_remove_end_zeros(char *src_arr, int end_src) {
  while (src_arr[end_src] == 0) end_src--;
  return end_src;
}

// removing zeros at the beginning of the array
// returns a position with a non-zero element
int s21_remove_start_zeros(char *src_arr) {
  int start_src = 0;
  while (src_arr[start_src] == 0) start_src++;
  return start_src;
}

// filling one array with another
// from the <end_src> position to the <start_src> position
void s21_assign_arr(int end_src, int start_src, char *arr_1, char *arr_2) {
  for (int j = end_src; j >= start_src; j--) arr_1[j] = arr_2[j];
}

// converting a float with an integer part to an array of decimal digits
void s21_float_with_int_to_arr(int *start, int *end, int *exp, float src,
                               char *src_arr) {
  src *= 1e7;
  int size = s21_float_to_array_up(src, src_arr);  // number of array elements
  int start_significant_part =
      size - 7 -
      1;  // the position of the minor category of the significant part
  (*end) =
      size - 1;  // the position of the senior category of the significant part
  s21_bankers_rounding(start_significant_part, src_arr);
  int before_point = size - 7;  // digits in the int part
  int after_point = 7 - before_point;
  (*exp) = (after_point > 0) ? after_point : 0;
  (*start) = (after_point > 0) ? (*end) + 1 - (after_point + before_point)
                               : (*end) + 1 - before_point;
  // removing insignificant zeros at the end
  while (src_arr[(*start)] == 0 && (*exp) > 0) {
    (*start)++;
    (*exp)--;
  }
}

// converting a float without an integer part to an array of decimal digits
void s21_float_without_int_to_arr(int *start, int *end, int *exp, float src,
                                  char *src_arr) {
  (*end) = s21_float_to_array_down(src, src_arr);
  s21_reverse_arr(src_arr, (*end));
  s21_bankers_rounding((*start), src_arr);
  (*start) = s21_remove_start_zeros(src_arr);
  (*exp) = (*end) - (*start);
  (*end) = s21_remove_end_zeros(src_arr, (*end) - 1);
}

// converting a decimal number represented by an array
// to a binary number represented by an array
int s21_dec_to_bin_arr(int start, int end, char *dec_arr, char *bin_arr) {
  int bin_ind = 0;
  int flag = 0;
  int size = end - start + 1;
  while (!flag) {
    char buf_dec_arr[36] = {0};
    int mod = 0;
    int div = 0;
    for (int j = end; j >= start; j--) {
      mod = dec_arr[j] % 2;
      div = dec_arr[j] / 2;
      buf_dec_arr[j] = div;
      if (j - 1 < start) {
        bin_arr[bin_ind] = mod;
        bin_ind++;
      } else if (mod) {
        dec_arr[j - 1] += 10;
      }
    }
    s21_assign_arr(end, start, dec_arr, buf_dec_arr);
    if (size != 1) end = s21_remove_end_zeros(dec_arr, end);
    size = end - start + 1;
    if (size == 1 && (dec_arr[start] == 1 || dec_arr[start] == 0)) {
      flag = 1;
      bin_arr[bin_ind] = div;
    }
  }
  return bin_ind;
}

// float --> decimal
// 0 - successful
// 1- error
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int ans = 0;
  float abs_src = fabs(src);
  if ((abs_src > 0 && abs_src < 1e-28f) || abs_src > DEC_MAX || dst == NULL) {
    ans = 1;
  } else {
    int exp = 0;
    int sign = 0;
    if (src < 0.0) sign = 1;
    s21_decimal_set_zero(dst);
    s21_decimal_set_sign(dst, sign);
    float abs_src = fabs(src);
    if (abs_src != 0.0) {
      char src_arr[36] = {0};
      int start_src = 0;
      int end_src = 0;
      if (abs_src >= 1.0) {
        s21_float_with_int_to_arr(&start_src, &end_src, &exp, abs_src, src_arr);
      } else {
        s21_float_without_int_to_arr(&start_src, &end_src, &exp, abs_src,
                                     src_arr);
      }
      char bin_src_arr[96] = {0};
      int bin_ind =
          s21_dec_to_bin_arr(start_src, end_src, src_arr, bin_src_arr);
      for (int i = 0; i <= bin_ind; i++)
        s21_decimal_set_bit(dst, i, bin_src_arr[i]);
      s21_decimal_set_scale(dst, exp);
    }
  }
  return ans;
}
