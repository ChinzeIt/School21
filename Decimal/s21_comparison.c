#include "s21_decimal.h"
#include "support_func/s21_decimal_support_func.h"

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  s21_name_of_const comparative_result = S21_COMPARISON_FALSE;

  s21_big_decimal num_1 = s21_init_big_decimal();
  s21_big_decimal num_2 = s21_init_big_decimal();
  s21_decimal_to_big_decimal(num1, &num_1);
  s21_decimal_to_big_decimal(num2, &num_2);

  int sign1 = s21_get_sign_big_decimal(num_1);
  int sign2 = s21_get_sign_big_decimal(num_2);

  if (s21_is_zero(num_1) && s21_is_zero(num_2)) {
    comparative_result = S21_COMPARISON_FALSE;
  } else if (sign1 == S21_NEGATIVE && sign2 == S21_POSITIVE) {
    comparative_result = S21_COMPARISON_TRUE;
  } else if (sign1 == S21_POSITIVE && sign2 == S21_NEGATIVE) {
    comparative_result = S21_COMPARISON_FALSE;
  } else if (sign1 == S21_NEGATIVE && sign2 == S21_NEGATIVE) {
    comparative_result = s21_comparison_binary(s21_abs(num_2), s21_abs(num_1));
  } else {
    comparative_result = s21_comparison_binary(num_1, num_2);
  }
  return comparative_result;
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  return s21_is_less(num1, num2) || s21_is_equal(num1, num2);
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  return s21_is_less(num2, num1);
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  return s21_is_greater(num1, num2) || s21_is_equal(num1, num2);
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  s21_name_of_const equal_result = S21_COMPARISON_FALSE;

  s21_big_decimal num_1 = s21_init_big_decimal();
  s21_big_decimal num_2 = s21_init_big_decimal();
  s21_decimal_to_big_decimal(num1, &num_1);
  s21_decimal_to_big_decimal(num2, &num_2);

  int sign1 = s21_get_sign_big_decimal(num_1);
  int sign2 = s21_get_sign_big_decimal(num_2);

  if (s21_is_zero(num_1) && s21_is_zero(num_2)) {
    equal_result = S21_COMPARISON_TRUE;
  } else if (sign1 != sign2) {
    equal_result = S21_COMPARISON_FALSE;
  } else {
    equal_result = s21_equal_binary(num_1, num_2);
  }
  return equal_result;
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_equal(num1, num2);
}