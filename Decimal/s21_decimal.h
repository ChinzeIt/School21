#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define _GNU_SOURCE

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

typedef union s21_big_decimal_bits7 {
  int last_int;
  struct bits7 {
    uint32_t zero_0_15 : 16;
    uint32_t scale : 8;
    uint32_t zero_24_30 : 7;
    uint32_t sign : 1;
  } bits7;
} s21_big_decimal_bits7;

typedef enum {
  S21_POSITIVE = 0,
  S21_NEGATIVE = 1,
  S21_ARITHMETIC_OK = 0,
  S21_ARITHMETIC_BIG = 1,
  S21_ARITHMETIC_SMALL = 2,
  S21_ARITHMETIC_DIV_BY_ZERO = 3,
  S21_ERROR = 4,
  S21_COMPARISON_FALSE = 0,
  S21_COMPARISON_TRUE = 1,
  S21_CONVERTER_OK = 0,
  S21_CONVERTER_ERROR = 1,
  S21_OTHER_FUNC_OK = 0,
  S21_OTHER_FUNC_CALC_ER = 1,
} s21_name_of_const;

// Arithmetic operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison operators
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);

// Convertor operators
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Other functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif