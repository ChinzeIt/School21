#include "s21_decimal.h"
#include "support_func/s21_decimal_support_func.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = s21_init_decimal();
  s21_big_decimal num_1 = s21_init_big_decimal();
  s21_big_decimal num_2 = s21_init_big_decimal();
  s21_big_decimal res_big = s21_init_big_decimal();

  s21_decimal_to_big_decimal(value_1, &num_1);
  s21_decimal_to_big_decimal(value_2, &num_2);
  s21_decimal_to_big_decimal(*result, &res_big);
  s21_normalization(&num_1, &num_2);

  int sign_1 = s21_get_sign_big_decimal(num_1);
  int sign_2 = s21_get_sign_big_decimal(num_2);
  int scale = s21_get_scale_big_decimal(num_1);
  s21_name_of_const error = S21_ARITHMETIC_OK;

  if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE) {
    s21_add_binary(num_1, num_2, &res_big);
  } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE) {
    s21_add_binary(num_1, num_2, &res_big);
    s21_set_sign_big_decimal(&res_big, S21_NEGATIVE);
  }
  num_1 = s21_abs(num_1);
  num_2 = s21_abs(num_2);
  int is = s21_comparison_binary(num_1, num_2);
  if (sign_1 != sign_2) {
    if (is == S21_COMPARISON_TRUE) {
      s21_sub_binary(num_2, num_1, &res_big);
      s21_set_sign_big_decimal(&res_big, sign_2);
    } else {
      s21_sub_binary(num_1, num_2, &res_big);
      s21_set_sign_big_decimal(&res_big, sign_1);
    }
  }
  s21_set_scale_big_decimal(&res_big, scale);
  error = s21_from_big_decimal_to_decimal(res_big, result);

  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = s21_init_decimal();
  s21_big_decimal num_1 = s21_init_big_decimal();
  s21_big_decimal num_2 = s21_init_big_decimal();
  s21_big_decimal res_big = s21_init_big_decimal();

  s21_decimal_to_big_decimal(value_1, &num_1);
  s21_decimal_to_big_decimal(value_2, &num_2);
  s21_decimal_to_big_decimal(*result, &res_big);
  s21_normalization(&num_1, &num_2);

  int sign_1 = s21_get_sign_big_decimal(num_1);
  int sign_2 = s21_get_sign_big_decimal(num_2);
  int scale = s21_get_scale_big_decimal(num_1);
  int is_greater = s21_is_greater_or_equal(value_1, value_2);
  s21_name_of_const error = S21_ARITHMETIC_OK;

  if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE &&
      is_greater == S21_COMPARISON_TRUE) {
    s21_sub_binary(num_1, num_2, &res_big);
  } else if (sign_1 == S21_POSITIVE && sign_2 == S21_POSITIVE &&
             is_greater == S21_COMPARISON_FALSE) {
    s21_sub_binary(num_2, num_1, &res_big);
    s21_set_sign_big_decimal(&res_big, S21_NEGATIVE);
  } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE &&
             is_greater == S21_COMPARISON_FALSE) {
    s21_sub_binary(num_1, num_2, &res_big);
    s21_set_sign_big_decimal(&res_big, S21_NEGATIVE);
  } else if (sign_1 == S21_NEGATIVE && sign_2 == S21_NEGATIVE &&
             is_greater == S21_COMPARISON_TRUE) {
    s21_sub_binary(num_2, num_1, &res_big);
    s21_set_sign_big_decimal(&res_big, S21_POSITIVE);
  }
  if (sign_1 != sign_2) {
    if (is_greater == S21_COMPARISON_TRUE) {
      s21_add_binary(num_1, num_2, &res_big);
    } else {
      s21_add_binary(num_1, num_2, &res_big);
      s21_set_sign_big_decimal(&res_big, S21_NEGATIVE);
    }
  }
  s21_set_scale_big_decimal(&res_big, scale);
  error = s21_from_big_decimal_to_decimal(res_big, result);

  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = s21_init_decimal();
  s21_big_decimal num_1 = s21_init_big_decimal();
  s21_big_decimal num_2 = s21_init_big_decimal();
  s21_big_decimal res_big = s21_init_big_decimal();

  s21_decimal_to_big_decimal(value_1, &num_1);
  s21_decimal_to_big_decimal(value_2, &num_2);
  s21_decimal_to_big_decimal(*result, &res_big);

  int sign_1 = s21_get_sign_big_decimal(num_1);
  int sign_2 = s21_get_sign_big_decimal(num_2);
  s21_name_of_const error = S21_ARITHMETIC_OK;

  if ((s21_is_zero(num_1) == false) && (s21_is_zero(num_2) == false)) {
    s21_mul_binary(num_1, num_2, &res_big);
    if (sign_1 == sign_2) s21_set_sign_big_decimal(&res_big, S21_POSITIVE);
    if (sign_1 != sign_2) s21_set_sign_big_decimal(&res_big, S21_NEGATIVE);
    error = s21_from_big_decimal_to_decimal(res_big, result);
  }

  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = s21_init_decimal();
  s21_big_decimal num_1 = s21_init_big_decimal();
  s21_big_decimal num_2 = s21_init_big_decimal();
  s21_big_decimal res_big = s21_init_big_decimal();

  s21_decimal_to_big_decimal(value_1, &num_1);
  s21_decimal_to_big_decimal(value_2, &num_2);
  s21_decimal_to_big_decimal(*result, &res_big);

  int sign_1 = s21_get_sign_big_decimal(num_1);
  int sign_2 = s21_get_sign_big_decimal(num_2);
  s21_name_of_const error = S21_ARITHMETIC_OK;

  if ((s21_is_zero(num_1) == false) && (s21_is_zero(num_2) == false)) {
    s21_div_binary(num_1, num_2, &res_big);
    if (sign_1 == sign_2) s21_set_sign_big_decimal(&res_big, S21_POSITIVE);
    if (sign_1 != sign_2) s21_set_sign_big_decimal(&res_big, S21_NEGATIVE);
    error = s21_from_big_decimal_to_decimal(res_big, result);
  } else {
    if (s21_is_zero(num_2) == true) error = S21_ARITHMETIC_DIV_BY_ZERO;
    if (s21_is_zero(num_1) == true) error = S21_ARITHMETIC_OK;
  }

  return error;
}