#include <check.h>
#include <limits.h>

#include "s21_decimal.h"
#include "support_func/s21_decimal_support_func.h"

START_TEST(test_from_int_to_decimal_positive) {
  s21_decimal result = {{0}};
  int num = 12345;
  ck_assert_int_eq(s21_from_int_to_decimal(num, &result), S21_CONVERTER_OK);
  ck_assert_uint_eq(result.bits[0], 12345);
  ck_assert_int_eq(s21_get_sign_decimal(result), S21_POSITIVE);
}
END_TEST

START_TEST(test_from_int_to_decimal_negative) {
  s21_decimal result = {{0}};
  int num = -2147483648;
  ck_assert_int_eq(s21_from_int_to_decimal(num, &result), S21_CONVERTER_OK);
  ck_assert_uint_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(s21_get_sign_decimal(result), S21_NEGATIVE);
}
END_TEST

START_TEST(test_from_int_to_decimal_zero) {
  s21_decimal result = {{0}};
  int num = 0;
  ck_assert_int_eq(s21_from_int_to_decimal(num, &result), S21_CONVERTER_OK);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(s21_get_sign_decimal(result), S21_POSITIVE);
}
END_TEST

START_TEST(test_from_int_to_decimal_null) {
  ck_assert_int_eq(s21_from_int_to_decimal(0, NULL), S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_positive) {
  s21_decimal src = {{0}};
  s21_from_int_to_decimal(123, &src);
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), S21_CONVERTER_OK);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_from_decimal_to_int_negative) {
  s21_decimal src;
  s21_from_int_to_decimal(-456, &src);
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), S21_CONVERTER_OK);
  ck_assert_int_eq(result, -456);
}
END_TEST

START_TEST(test_from_decimal_to_int_scale) {
  s21_decimal src = s21_init_decimal();
  src.bits[0] = 1234;
  s21_set_scale_decimal(&src, 1);
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &result), S21_CONVERTER_OK);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_from_decimal_to_int_invalid) {
  s21_decimal invalid = {{1, 2, 3, 0x800F0000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(invalid, &result),
                   S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_int_null) {
  s21_decimal src = {{0}};
  ck_assert_int_eq(s21_from_decimal_to_int(src, NULL), S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_positive2) {
  s21_decimal result;
  float num = 123.1233978271484375;
  ck_assert_int_eq(s21_from_float_to_decimal(num, &result), S21_CONVERTER_OK);
}
END_TEST

START_TEST(test_from_float_to_decimal_negative2) {
  s21_decimal result = {{0}};
  float num = -789.12;
  ck_assert_int_eq(s21_from_float_to_decimal(num, &result), S21_CONVERTER_OK);
}
END_TEST

START_TEST(test_from_float_to_decimal_zero) {
  s21_decimal result = {{0}};
  float num = 0.0f;
  ck_assert_int_eq(s21_from_float_to_decimal(num, &result), S21_CONVERTER_OK);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(s21_get_scale_decimal(result), 0);
}
END_TEST

START_TEST(test_float_to_dec_overflow) {
  s21_decimal result = {{0}};
  float num = 7.922816e28f;
  ck_assert_int_eq(s21_from_float_to_decimal(num, &result), S21_CONVERTER_OK);
}
END_TEST

START_TEST(test_float_to_dec_underflow) {
  s21_decimal result = {{0}};
  float num = 7.922816e-30f;
  ck_assert_int_eq(s21_from_float_to_decimal(num, &result),
                   S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_large3) {
  s21_decimal result = {{0}};
  float num = 8e28f;
  ck_assert_int_eq(s21_from_float_to_decimal(num, &result),
                   S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_nan_inf) {
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_from_float_to_decimal(NAN, &result),
                   S21_CONVERTER_ERROR);
  ck_assert_int_eq(s21_from_float_to_decimal(INFINITY, &result),
                   S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_null) {
  ck_assert_int_eq(s21_from_float_to_decimal(0.0f, NULL), S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_positive) {
  s21_decimal src = {{0}};
  s21_from_float_to_decimal(123.456f, &src);
  float result = 0.0;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &result), S21_CONVERTER_OK);
  ck_assert_float_eq_tol(result, 123.456f, 1e-3);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative) {
  s21_decimal src = {{0}};
  s21_from_float_to_decimal(-789.12f, &src);
  float result;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &result), S21_CONVERTER_OK);
  ck_assert_float_eq_tol(result, -789.12f, 1e-2);
}
END_TEST

START_TEST(test_from_decimal_to_float_scale) {
  s21_decimal src = s21_init_decimal();
  src.bits[0] = 1234;
  s21_set_scale_decimal(&src, 3);
  float result = 0.0;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &result), S21_CONVERTER_OK);
  ck_assert_float_eq_tol(result, 1.234f, 1e-3);
}
END_TEST

START_TEST(test_from_decimal_to_float_null) {
  s21_decimal src = {{0}};
  ck_assert_int_eq(s21_from_decimal_to_float(src, NULL), S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_decimal_to_big_decimal) {
  s21_decimal src = {{0}};
  s21_from_int_to_decimal(123456, &src);
  ck_assert_int_eq(s21_decimal_to_big_decimal(src, NULL), S21_CONVERTER_ERROR);
}
END_TEST

START_TEST(test_add_two_positives) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 300);
}
END_TEST

START_TEST(test_add_positive_with_negative_representation) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{200, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 100);
}
END_TEST

START_TEST(test_add_two_negatives) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{200, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 300);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_add_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(a, b, &result), 1);
}
END_TEST

START_TEST(test_add_underflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(a, b, &result), 2);
}
END_TEST

START_TEST(test_subtract_larger_from_smaller) {
  s21_decimal a = {{200, 0, 0, 0}};
  s21_decimal b = {{500, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 300);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_subtract_scaled_from_max) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{6, 0, 0, 0}};
  s21_set_scale_decimal(&b, 1);
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_subtract_another_scaled_from_max) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_set_scale_decimal(&b, 1);
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_subtract_negative_from_negative) {
  s21_decimal a = {{200, 0, 0, 0x80000000}};
  s21_decimal b = {{500, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 300);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_subtract_smaller_negative_from_larger) {
  s21_decimal a = {{500, 0, 0, 0x80000000}};
  s21_decimal b = {{200, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 300);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_subtract_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), 1);
}
END_TEST

START_TEST(test_subtract_underflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), 2);
}
END_TEST

START_TEST(test_multiply_two_positives) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_mul(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 6);
}
END_TEST

START_TEST(test_multiply_scaled_positives) {
  s21_decimal a = {{7, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_set_scale_decimal(&a, 28);
  s21_set_scale_decimal(&b, 28);
  ck_assert_int_eq(s21_mul(a, b, &result), 0);
}
END_TEST

START_TEST(test_multiply_negative_by_positive) {
  s21_decimal a = {{2, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_mul(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 6);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_multiply_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{21, 0, 0, 0}};
  s21_set_scale_decimal(&b, 1);
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_mul(a, b, &result), 1);
}
END_TEST

START_TEST(test_divide_positives_with_scales) {
  s21_decimal a = {{8536, 0, 0, 0}};
  s21_decimal b = {{4124, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_set_scale_decimal(&a, 2);
  s21_set_scale_decimal(&b, 3);
  ck_assert_int_eq(s21_div(a, b, &result), 0);
}
END_TEST

START_TEST(test_divide_negative_by_positive) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{25, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_div(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 4);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_divide_by_zero) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_div(a, b, &result), S21_ARITHMETIC_DIV_BY_ZERO);
  ck_assert_int_eq(s21_div(b, a, &result), S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_divide_small_result) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_div(a, b, &result), 0);
}
END_TEST

START_TEST(test_is_less_zero) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_less_neg_vs_pos) {
  s21_decimal num1 = {{123, 0, 0, 0x80000000}};
  s21_decimal num2 = {{456, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_less_pos_vs_neg) {
  s21_decimal num1 = {{789, 0, 0, 0}};
  s21_decimal num2 = {{321, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_less_both_neg) {
  s21_decimal num1 = {{100, 0, 0, 0x80000000}};
  s21_decimal num2 = {{50, 0, 0, 0x80000000}};
  s21_set_scale_decimal(&num1, 4);
  s21_set_scale_decimal(&num2, 5);
  ck_assert_int_eq(s21_is_less(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_less_both_neg2) {
  s21_decimal num1 = {{100, 0, 0, 0}};
  s21_decimal num2 = {{50, 0, 0, 0}};
  s21_set_sign_decimal(&num1, S21_NEGATIVE);
  s21_set_sign_decimal(&num2, S21_NEGATIVE);
  ck_assert_int_eq(s21_is_less(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_less_both_pos) {
  s21_decimal num1 = {{12345, 0, 0, 0}};
  s21_decimal num2 = {{67890, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_less_equal_numbers_diff_scales) {
  s21_decimal num1 = {{123, 0, 0, 0x00010000}};
  s21_decimal num2 = {{1230, 0, 0, 0x00020000}};
  ck_assert_int_eq(s21_is_less(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_less_max_min_values) {
  s21_decimal max_positive = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal min_negative = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  ck_assert_int_eq(s21_is_less(min_negative, max_positive),
                   S21_COMPARISON_TRUE);
  ck_assert_int_eq(s21_is_less(max_positive, min_negative),
                   S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_less_different_scales) {
  s21_decimal num1 = {{12345, 0, 0, 0x00020000}};
  s21_decimal num2 = {{1234500, 0, 0, 0x00050000}};
  ck_assert_int_eq(s21_is_less(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_equal_different_sign) {
  s21_decimal a = {{123, 0, 0, 0x80000000}};
  s21_decimal b = {{123, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_is_less_positive) {
  s21_decimal a = {{100234, 0, 0, 0}};
  s21_decimal b = {{100234, 0, 0, 0}};
  s21_set_scale_decimal(&a, 2);
  s21_set_scale_decimal(&b, 3);
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 1);
}
END_TEST

START_TEST(test_is_less_negative) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{200, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 1);
}
END_TEST

START_TEST(test_is_less_equal) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_is_less_or_equal_true) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{456, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_less_or_equal_equal) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_less_or_equal_false) {
  s21_decimal num1 = {{456, 0, 0, 0}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_greater_true) {
  s21_decimal num1 = {{456, 0, 0, 0}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_greater_false) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{456, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_greater_equal) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_greater_or_equal_true) {
  s21_decimal num1 = {{456, 0, 0, 0}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_greater_or_equal_equal) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_greater_or_equal_false) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{456, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_equal_true) {
  s21_decimal num1 = {{1234, 0, 0, 0}};
  s21_decimal num2 = {{1234, 0, 0, 0}};
  s21_set_scale_decimal(&num1, 2);
  s21_set_scale_decimal(&num2, 1);
  ck_assert_int_eq(s21_is_equal(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_equal_false) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{456, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_equal_zero) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_equal_diff_sign) {
  s21_decimal num1 = {{123, 0, 0, 0x80000000}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_not_equal_true) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{456, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_is_not_equal_false) {
  s21_decimal num1 = {{123, 0, 0, 0}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_not_equal_zero) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), S21_COMPARISON_FALSE);
}
END_TEST

START_TEST(test_is_not_equal_diff_sign) {
  s21_decimal num1 = {{123, 0, 0, 0x80000000}};
  s21_decimal num2 = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_set_get_sign) {
  s21_decimal num1 = {{5, 0, 0, 0}};
  s21_decimal num2 = {{4, 0, 0, 0}};
  s21_set_bit_decimal(&num1, 0, 0);
  ck_assert_int_eq(s21_is_equal(num1, num2), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_both_non_zero) {
  s21_decimal dec = {0};
  dec.bits[3] = 0x7F000000;
  ck_assert_int_eq(s21_checking_decimal_for_correct(dec), 0);
  ck_assert_int_eq(s21_checking_decimal_for_correct(dec), S21_CONVERTER_OK);
}
END_TEST

START_TEST(test_division_bank_rounding) {
  s21_decimal a = {{UINT_MAX - 1, UINT_MAX, UINT_MAX, 0}};
  s21_decimal b = {{6, 0, 0, 0x10000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[2], UINT_MAX);
  ck_assert_uint_eq(result.bits[1], UINT_MAX);
  ck_assert_uint_eq(result.bits[0], UINT_MAX - 2);
}
END_TEST

START_TEST(test_division_simple_numbers) {
  s21_decimal a = {{13, 0, 0, 0}};
  s21_decimal b = {{9, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_div(a, b, &result), S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_division_another_simple_numbers) {
  s21_decimal a = {{17, 0, 0, 0}};
  s21_decimal b = {{9, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_div(a, b, &result), S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_division_smaller_dividend) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{9, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_div(a, b, &result), S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_0_6_to_max) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{6, 0, 0, 0x10000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(max, b, &result), S21_ARITHMETIC_BIG);
}
END_TEST

START_TEST(test_add_neg_0_6_to_min) {
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{6, 0, 0, 0x10000}};
  s21_set_sign_decimal(&b, S21_NEGATIVE);
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(min, b, &result), S21_ARITHMETIC_SMALL);
}
END_TEST

START_TEST(test_multiplication_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_set_sign_decimal(&b, S21_NEGATIVE);
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_sub(a, b, &result), S21_ARITHMETIC_BIG);
}
END_TEST

START_TEST(test_multiplication_1_6_by_3) {
  s21_decimal a = {0}, b = {0}, result = {0}, rounded = {0};
  s21_from_float_to_decimal(1.6f, &a);
  s21_from_float_to_decimal(3.0f, &b);
  int mul_status = s21_mul(a, b, &result);
  ck_assert_int_eq(mul_status, S21_ARITHMETIC_OK);
  int round_status = s21_round(result, &rounded);
  ck_assert_int_eq(round_status, S21_OTHER_FUNC_OK);
  s21_decimal g = {{0x5, 0, 0, 0}};
  ck_assert_uint_eq(s21_is_equal(rounded, g), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_max_min_values) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(max, (s21_decimal){{1, 0, 0, 0}}, &result), 1);
  ck_assert_int_eq(s21_sub(min, (s21_decimal){{1, 0, 0, 0}}, &result), 2);
  ck_assert_int_eq(s21_mul(max, max, &result), 1);
  ck_assert_int_eq(s21_mul(min, max, &result), 2);
  ck_assert_int_eq(s21_div(min, min, &result), 0);
}
END_TEST

START_TEST(test_shift_left_overflow) {
  s21_big_decimal num = s21_init_big_decimal();
  s21_set_bit_big_decimal(&num, 220, 1);
  int step = 4;
  int result = s21_shift_left(&num, step);
  ck_assert_int_eq(result, S21_ARITHMETIC_BIG);
}
END_TEST

START_TEST(test_max_min_values_scale) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_decimal max2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_decimal result = {{0}};
  s21_set_scale_decimal(&max, 10);
  s21_set_scale_decimal(&max2, 10);
  ck_assert_int_eq(s21_mul(max, max2, &result), 0);
}
END_TEST

START_TEST(test_max_min_values_scale2) {
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0x80000000}};
  s21_decimal result = {{0}};
  s21_set_scale_decimal(&min, 1);
  ck_assert_int_eq(s21_mul(min, min, &result), 1);
}
END_TEST

START_TEST(test_arithmetic_operations_scaled) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{456, 0, 0, 0}};

  s21_decimal result = {{0}};
  s21_decimal result1 = {{0}};
  s21_decimal result2 = {{0}};
  s21_decimal result3 = {{0}};
  s21_set_scale_decimal(&a, 2);
  s21_set_scale_decimal(&b, 1);
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_sub(a, b, &result1), 0);
  ck_assert_int_eq(s21_mul(a, b, &result2), 0);
  ck_assert_int_eq(s21_div(a, b, &result3), 0);
  ck_assert_uint_eq(result.bits[0], 4683);
  ck_assert_uint_eq(result1.bits[0], 4437);
  ck_assert_uint_eq(result1.bits[3], 0x80020000);
  ck_assert_uint_eq(result2.bits[0], 56088);
}
END_TEST

START_TEST(test_arithmetic_operations_negative_scaled) {
  s21_decimal a = {{123, 0, 0, 0x80000000}};
  s21_decimal b = {{456, 0, 0, 0}};

  s21_decimal result = {{0}};
  s21_decimal result1 = {{0}};
  s21_decimal result2 = {{0}};
  s21_decimal result3 = {{0}};
  s21_set_scale_decimal(&a, 2);
  s21_set_scale_decimal(&b, 1);
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(s21_sub(a, b, &result1), 0);
  ck_assert_int_eq(s21_mul(a, b, &result2), 0);
  ck_assert_int_eq(s21_div(a, b, &result3), 0);
  ck_assert_uint_eq(result.bits[0], 4437);
  ck_assert_uint_eq(result1.bits[0], 4683);
  ck_assert_uint_eq(result1.bits[3], 0x80020000);
  ck_assert_uint_eq(result2.bits[0], 56088);
  ck_assert_uint_eq(result2.bits[3], 0x80030000);
}
END_TEST

START_TEST(test_find_last_bit_highest_bit_set) {
  s21_big_decimal num = s21_init_big_decimal();
  s21_big_decimal num2 = s21_init_big_decimal();
  s21_set_bit_big_decimal(&num, 100, 1);
  s21_set_bit_big_decimal(&num2, 223, 1);
  int result = s21_find_last_bit(num);
  int result2 = s21_find_last_bit(num2);
  ck_assert_int_eq(result2, 223);
  ck_assert_int_eq(result, 100);
}
END_TEST

START_TEST(test_sign_combinations) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{50, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_uint_eq(result.bits[0], 50);
  ck_assert_int_eq(s21_get_sign_decimal(result), 1);
}
END_TEST

START_TEST(test_floor_positive) {
  s21_decimal value = {{123456, 0, 0, 0x00030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_floor_negative) {
  s21_decimal value = {{123456, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 124);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_floor_negative2) {
  s21_decimal value = {{123456, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  s21_set_scale_decimal(&value, 29);
  ck_assert_int_eq(s21_floor(value, &result), S21_OTHER_FUNC_CALC_ER);
}
END_TEST

START_TEST(test_floor_max) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(test_floor_min) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST
START_TEST(test_round_positive) {
  s21_decimal value = {{123456, 0, 0, 0x00030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_round_positive2) {
  s21_decimal value = {{123030, 0, 0, 0x00030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_round_negative) {
  s21_decimal value = {{123456, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_round_negative2) {
  s21_decimal value = {{123956, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 124);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_round_negative3) {
  s21_decimal value = {{123956, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  s21_set_scale_decimal(&value, 29);
  ck_assert_int_eq(s21_round(value, &result), S21_OTHER_FUNC_CALC_ER);
}
END_TEST

START_TEST(test_round_max) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(test_round_min) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_truncate_positive) {
  s21_decimal value = {{123456, 0, 0, 0x00030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_truncate_negative) {
  s21_decimal value = {{123456, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST
START_TEST(test_truncate_negative2) {
  s21_decimal value = {{123956, 0, 0, 1}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), S21_OTHER_FUNC_CALC_ER);
}
END_TEST

START_TEST(test_truncate_max) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
}
END_TEST

START_TEST(test_truncate_min) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_truncate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST
START_TEST(test_negate_positive) {
  s21_decimal value = {{123, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_negate_negative) {
  s21_decimal value = {{123, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 123);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST
START_TEST(test_negate_negative2) {
  s21_decimal value = {{123956, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  s21_set_scale_decimal(&value, 29);
  ck_assert_int_eq(s21_negate(value, &result), S21_OTHER_FUNC_CALC_ER);
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_negate_max) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_negate_min) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(s21_negate(value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_uint_eq(result.bits[3], 0);
}
END_TEST

Suite *decimal_suite(void) {
  Suite *s = suite_create("Decimal Tests");
  TCase *tc_int = tcase_create("Int Decimal");
  tcase_add_test(tc_int, test_from_int_to_decimal_positive);
  tcase_add_test(tc_int, test_from_int_to_decimal_negative);
  tcase_add_test(tc_int, test_from_int_to_decimal_zero);
  tcase_add_test(tc_int, test_from_int_to_decimal_null);
  tcase_add_test(tc_int, test_from_decimal_to_int_positive);
  tcase_add_test(tc_int, test_from_decimal_to_int_negative);
  tcase_add_test(tc_int, test_from_decimal_to_int_scale);
  tcase_add_test(tc_int, test_from_decimal_to_int_invalid);
  tcase_add_test(tc_int, test_from_decimal_to_int_null);
  suite_add_tcase(s, tc_int);

  TCase *tc_float = tcase_create("Float Decimal");
  tcase_add_test(tc_float, test_from_float_to_decimal_positive2);
  tcase_add_test(tc_float, test_from_float_to_decimal_negative2);
  tcase_add_test(tc_float, test_from_float_to_decimal_zero);
  tcase_add_test(tc_float, test_float_to_dec_overflow);
  tcase_add_test(tc_float, test_float_to_dec_underflow);
  tcase_add_test(tc_float, test_from_float_to_decimal_large3);
  tcase_add_test(tc_float, test_from_float_to_decimal_nan_inf);
  tcase_add_test(tc_float, test_from_float_to_decimal_null);
  tcase_add_test(tc_float, test_from_decimal_to_float_positive);
  tcase_add_test(tc_float, test_from_decimal_to_float_negative);
  tcase_add_test(tc_float, test_from_decimal_to_float_scale);
  tcase_add_test(tc_float, test_from_decimal_to_float_null);
  suite_add_tcase(s, tc_float);

  TCase *tc_big = tcase_create("Big Decimal");
  tcase_add_test(tc_big, test_decimal_to_big_decimal);
  suite_add_tcase(s, tc_big);

  TCase *tc = tcase_create("Arithmetic");
  tcase_add_test(tc, test_add_two_positives);
  tcase_add_test(tc, test_add_positive_with_negative_representation);
  tcase_add_test(tc, test_add_two_negatives);
  tcase_add_test(tc, test_add_overflow);
  tcase_add_test(tc, test_add_underflow);
  tcase_add_test(tc, test_subtract_larger_from_smaller);
  tcase_add_test(tc, test_subtract_scaled_from_max);
  tcase_add_test(tc, test_subtract_another_scaled_from_max);
  tcase_add_test(tc, test_subtract_negative_from_negative);
  tcase_add_test(tc, test_subtract_smaller_negative_from_larger);
  tcase_add_test(tc, test_subtract_overflow);
  tcase_add_test(tc, test_subtract_underflow);
  tcase_add_test(tc, test_multiply_two_positives);
  tcase_add_test(tc, test_multiply_scaled_positives);
  tcase_add_test(tc, test_multiply_negative_by_positive);
  tcase_add_test(tc, test_multiply_overflow);
  tcase_add_test(tc, test_divide_positives_with_scales);
  tcase_add_test(tc, test_divide_negative_by_positive);
  tcase_add_test(tc, test_divide_by_zero);
  tcase_add_test(tc, test_divide_small_result);
  suite_add_tcase(s, tc);

  TCase *tc_core = tcase_create("Comparison");
  tcase_add_test(tc_core, test_is_less_zero);
  tcase_add_test(tc_core, test_is_less_neg_vs_pos);
  tcase_add_test(tc_core, test_is_less_pos_vs_neg);
  tcase_add_test(tc_core, test_is_less_both_neg2);
  tcase_add_test(tc_core, test_is_less_both_neg);
  tcase_add_test(tc_core, test_is_less_both_pos);
  tcase_add_test(tc_core, test_is_less_equal_numbers_diff_scales);
  tcase_add_test(tc_core, test_is_less_max_min_values);
  tcase_add_test(tc_core, test_is_less_different_scales);
  tcase_add_test(tc, test_is_less_positive);
  tcase_add_test(tc, test_is_less_negative);
  tcase_add_test(tc, test_is_less_negative);
  tcase_add_test(tc, test_is_less_equal);
  tcase_add_test(tc, test_is_equal_true);
  tcase_add_test(tc, test_is_equal_false);
  tcase_add_test(tc, test_is_equal_different_sign);
  tcase_add_test(tc, test_is_less_or_equal_true);
  tcase_add_test(tc, test_is_less_or_equal_equal);
  tcase_add_test(tc, test_is_less_or_equal_false);
  tcase_add_test(tc, test_is_greater_true);
  tcase_add_test(tc, test_is_greater_false);
  tcase_add_test(tc, test_is_greater_equal);
  tcase_add_test(tc, test_is_greater_or_equal_true);
  tcase_add_test(tc, test_is_greater_or_equal_equal);
  tcase_add_test(tc, test_is_greater_or_equal_false);
  tcase_add_test(tc, test_is_equal_true);
  tcase_add_test(tc, test_is_equal_false);
  tcase_add_test(tc, test_is_equal_zero);
  tcase_add_test(tc, test_is_equal_diff_sign);
  tcase_add_test(tc, test_is_not_equal_true);
  tcase_add_test(tc, test_is_not_equal_false);
  tcase_add_test(tc, test_is_not_equal_zero);
  tcase_add_test(tc, test_is_not_equal_diff_sign);
  suite_add_tcase(s, tc_core);

  TCase *tc_floor = tcase_create("Floor");
  tcase_add_test(tc_floor, test_floor_positive);
  tcase_add_test(tc_floor, test_floor_negative);
  tcase_add_test(tc_floor, test_floor_negative2);
  tcase_add_test(tc_floor, test_floor_max);
  tcase_add_test(tc_floor, test_floor_min);
  suite_add_tcase(s, tc_floor);

  TCase *tc_round = tcase_create("Round");
  tcase_add_test(tc_round, test_round_positive);
  tcase_add_test(tc_round, test_round_positive2);
  tcase_add_test(tc_round, test_round_negative);
  tcase_add_test(tc_round, test_round_negative2);
  tcase_add_test(tc_round, test_round_negative3);
  tcase_add_test(tc_round, test_round_max);
  tcase_add_test(tc_round, test_round_min);
  suite_add_tcase(s, tc_round);

  TCase *tc_truncate = tcase_create("Truncate");
  tcase_add_test(tc_truncate, test_truncate_positive);
  tcase_add_test(tc_truncate, test_truncate_negative);
  tcase_add_test(tc_truncate, test_truncate_negative2);
  tcase_add_test(tc_truncate, test_truncate_max);
  tcase_add_test(tc_truncate, test_truncate_min);
  suite_add_tcase(s, tc_truncate);

  TCase *tc_negate = tcase_create("Negate");
  tcase_add_test(tc_negate, test_negate_positive);
  tcase_add_test(tc_negate, test_negate_negative);
  tcase_add_test(tc_negate, test_negate_negative2);
  tcase_add_test(tc_negate, test_negate_zero);
  tcase_add_test(tc_negate, test_negate_max);
  tcase_add_test(tc_negate, test_negate_min);
  suite_add_tcase(s, tc_negate);

  TCase *tc_utils = tcase_create("Utils");
  tcase_add_test(tc_utils, test_set_get_sign);
  tcase_add_test(tc_utils, test_both_non_zero);
  suite_add_tcase(s, tc_utils);

  TCase *tc_res = tcase_create("Arithmetic and Edge Cases");
  tcase_add_test(tc_res, test_division_bank_rounding);
  tcase_add_test(tc_res, test_division_simple_numbers);
  tcase_add_test(tc_res, test_division_another_simple_numbers);
  tcase_add_test(tc_res, test_division_smaller_dividend);
  tcase_add_test(tc_res, test_add_0_6_to_max);
  tcase_add_test(tc_res, test_add_neg_0_6_to_min);
  tcase_add_test(tc_res, test_multiplication_overflow);
  tcase_add_test(tc_res, test_multiplication_1_6_by_3);
  tcase_add_test(tc_res, test_max_min_values);
  tcase_add_test(tc_res, test_shift_left_overflow);
  tcase_add_test(tc_res, test_max_min_values_scale);
  tcase_add_test(tc_res, test_max_min_values_scale2);
  tcase_add_test(tc_res, test_arithmetic_operations_scaled);
  tcase_add_test(tc_res, test_arithmetic_operations_negative_scaled);
  tcase_add_test(tc_res, test_find_last_bit_highest_bit_set);
  tcase_add_test(tc_res, test_sign_combinations);
  suite_add_tcase(s, tc_res);

  return s;
}

int main(void) {
  int number_failed = 0;
  Suite *s = decimal_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
