#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

int s21_from_big_decimal_to_decimal(s21_big_decimal num, s21_decimal *decimal) {
  s21_name_of_const code_error = S21_ARITHMETIC_OK;
  *decimal = s21_init_decimal();
  s21_big_decimal buff = num;
  int sign = s21_get_sign_big_decimal(buff);
  s21_set_sign_big_decimal(&buff, 0);
  int scale = s21_get_scale_big_decimal(buff);
  int position = s21_find_last_bit(buff);
  s21_big_decimal result = buff;

  if (scale > 0 && (position > 95 || scale > 28)) {
    result = s21_banking_rouding(buff);
    scale = s21_get_scale_big_decimal(result);
  }

  if (!s21_check_mantissa_overflow(result)) {
    if (sign == S21_POSITIVE) {
      code_error = S21_ARITHMETIC_BIG;
    } else {
      code_error = S21_ARITHMETIC_SMALL;
    }
  }

  if (code_error == S21_ARITHMETIC_OK) {
    for (int i = 0; i < 4; i++) {
      decimal->bits[i] = result.bits[i];
    }
    decimal->bits[3] = result.bits[7];
    s21_set_scale_decimal(decimal, scale);
    s21_set_sign_decimal(decimal, sign);
  }

  return code_error;
}

bool s21_check_mantissa_overflow(s21_big_decimal num) {
  bool flag = true;
  if ((num.bits[6] || num.bits[5] || num.bits[4] || num.bits[3]) != 0) {
    flag = false;
  }
  return flag;
}
