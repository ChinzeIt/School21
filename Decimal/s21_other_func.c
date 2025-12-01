#include "s21_decimal.h"
#include "support_func/s21_decimal_support_func.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_name_of_const error = S21_OTHER_FUNC_OK;

  if (s21_checking_decimal_for_correct(value) == true) {
    int sign = s21_get_sign_decimal(value);
    int scale = s21_get_scale_decimal(value);
    *result = s21_init_decimal();

    s21_set_sign_decimal(&value, S21_POSITIVE);
    s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal buff = s21_init_decimal();

    s21_truncate(value, &buff);
    if (scale == 0) {
      *result = buff;
    } else if (sign == S21_NEGATIVE) {
      s21_add(buff, one, &buff);
      *result = buff;
    } else if (sign == S21_POSITIVE) {
      *result = buff;
    }
    s21_set_sign_decimal(result, sign);
  } else {
    error = S21_OTHER_FUNC_CALC_ER;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_name_of_const error = S21_OTHER_FUNC_OK;

  if (s21_checking_decimal_for_correct(value) == true) {
    int sign = s21_get_sign_decimal(value);
    int scale = s21_get_scale_decimal(value);
    s21_set_sign_decimal(&value, 0);

    *result = s21_init_decimal();
    s21_truncate(value, result);
    s21_decimal truncate = *result;
    s21_decimal five = {{0x5, 0x0, 0x0, 0x0}};
    s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};

    s21_big_decimal value_big = s21_init_big_decimal();
    s21_big_decimal ten = {{0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
    s21_big_decimal res_big = s21_init_big_decimal();
    s21_decimal_to_big_decimal(value, &value_big);
    s21_big_decimal integer = value_big;

    s21_set_scale_big_decimal(&value_big, 0);
    while (scale > 1) {
      integer = s21_div_binary(value_big, ten, &res_big);
      value_big = integer;
      scale--;
    }
    s21_set_scale_big_decimal(&integer, scale);
    s21_from_big_decimal_to_decimal(integer, result);
    s21_decimal round = *result;
    s21_decimal diff = s21_init_decimal();
    s21_sub(round, truncate, &diff);
    s21_set_scale_decimal(&diff, 0);

    if (s21_is_less(diff, five) == S21_COMPARISON_TRUE) {
      *result = truncate;
    } else {
      s21_add(truncate, one, result);
    }
    s21_set_sign_decimal(result, sign);
  } else {
    error = S21_OTHER_FUNC_CALC_ER;
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_name_of_const error = S21_OTHER_FUNC_OK;

  if (s21_checking_decimal_for_correct(value) == true) {
    int sign = s21_get_sign_decimal(value);
    *result = s21_init_decimal();
    s21_big_decimal value_big = s21_init_big_decimal();
    s21_big_decimal one = {{0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
    s21_big_decimal res_big = s21_init_big_decimal();
    s21_decimal_to_big_decimal(value, &value_big);

    s21_big_decimal integer = s21_div_binary(value_big, one, &res_big);
    error = S21_OTHER_FUNC_OK;
    s21_from_big_decimal_to_decimal(integer, result);
    s21_set_sign_decimal(result, sign);
  } else {
    error = S21_OTHER_FUNC_CALC_ER;
  }
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_name_of_const error = S21_OTHER_FUNC_OK;

  if (s21_checking_decimal_for_correct(value) == true) {
    *result = value;
    int sign = s21_get_sign_decimal(value);
    if (sign == S21_POSITIVE && (s21_is_zero_dec(*result) == false)) {
      s21_set_sign_decimal(result, S21_NEGATIVE);
    } else {
      s21_set_sign_decimal(result, S21_POSITIVE);
    }
  } else {
    error = S21_OTHER_FUNC_CALC_ER;
  }
  return error;
}