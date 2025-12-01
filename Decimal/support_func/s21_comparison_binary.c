#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

s21_big_decimal s21_abs(s21_big_decimal num) {
  s21_big_decimal module = num;
  s21_set_sign_big_decimal(&module, S21_POSITIVE);
  return module;
}

int s21_comparison_binary(s21_big_decimal num1, s21_big_decimal num2) {
  if (s21_get_scale_big_decimal(num1) != s21_get_scale_big_decimal(num2)) {
    s21_normalization(&num1, &num2);
  }
  int bit1 = 0, bit2 = 0;
  bool flag = true;
  for (int i = 223; i >= 0 && flag; i--) {
    bit1 = s21_get_bit_big_decimal(num1, i);
    bit2 = s21_get_bit_big_decimal(num2, i);
    if (bit1 != bit2) {
      flag = false;
    }
  }
  s21_name_of_const comp_res = S21_COMPARISON_FALSE;
  if (bit1 < bit2) {
    comp_res = S21_COMPARISON_TRUE;
  } else {
    comp_res = S21_COMPARISON_FALSE;
  }
  return comp_res;
}

int s21_equal_binary(s21_big_decimal num1, s21_big_decimal num2) {
  s21_name_of_const equal_res = S21_COMPARISON_TRUE;
  if (s21_get_scale_big_decimal(num1) != s21_get_scale_big_decimal(num2)) {
    s21_normalization(&num1, &num2);
  }
  bool flag = true;
  for (int i = 223; i >= 0 && flag; i--) {
    if (s21_get_bit_big_decimal(num1, i) != s21_get_bit_big_decimal(num2, i)) {
      flag = false;
      equal_res = S21_COMPARISON_FALSE;
    }
  }
  return equal_res;
}
