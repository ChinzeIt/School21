#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

int s21_shift_left(s21_big_decimal *num, int step) {
  s21_name_of_const flag = S21_ARITHMETIC_OK;

  if ((s21_find_last_bit(*num) + step) > 223) {
    flag = S21_ARITHMETIC_BIG;
  } else {
    for (int i = 223; (i >= 0) && (flag == S21_ARITHMETIC_OK); i--) {
      if (i - step >= 0) {
        s21_set_bit_big_decimal(num, i,
                                s21_get_bit_big_decimal(*num, i - step));
      } else {
        s21_set_bit_big_decimal(num, i, 0);
      }
    }
  }
  return flag;
}

void s21_shift_right(s21_big_decimal *num, int step) {
  for (int i = 0; i <= 223; i++) {
    if (i + step <= 223) {
      s21_set_bit_big_decimal(num, i, s21_get_bit_big_decimal(*num, i + step));
    } else {
      s21_set_bit_big_decimal(num, i, 0);
    }
  }
}
