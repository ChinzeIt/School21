#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

int s21_get_sign_decimal(s21_decimal num) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num.bits[3];
  return buff.bits7.sign;
}

void s21_set_sign_decimal(s21_decimal* num, int sign) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num->bits[3];
  if (sign == S21_POSITIVE) {
    buff.bits7.sign = S21_POSITIVE;
  } else {
    buff.bits7.sign = S21_NEGATIVE;
  }
  num->bits[3] = buff.last_int;
}

int s21_get_sign_big_decimal(s21_big_decimal num) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num.bits[7];
  return buff.bits7.sign;
}

void s21_set_sign_big_decimal(s21_big_decimal* num, int sign) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num->bits[7];
  if (sign == S21_POSITIVE) {
    buff.bits7.sign = S21_POSITIVE;
  } else {
    buff.bits7.sign = S21_NEGATIVE;
  }
  num->bits[7] = buff.last_int;
}

int s21_get_scale_decimal(s21_decimal num) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num.bits[3];
  return buff.bits7.scale;
}

void s21_set_scale_decimal(s21_decimal* num, int scale_value) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num->bits[3];
  buff.bits7.scale = scale_value;
  num->bits[3] = buff.last_int;
}

int s21_get_scale_big_decimal(s21_big_decimal num) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num.bits[7];
  return buff.bits7.scale;
}

void s21_set_scale_big_decimal(s21_big_decimal* num, int scale_value) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num->bits[7];
  buff.bits7.scale = scale_value;
  num->bits[7] = buff.last_int;
}

int s21_get_bit_decimal(s21_decimal num, int bit_place) {
  int int_number = bit_place / 32;
  int bit_number = bit_place % 32;
  int bit_value;
  if ((num.bits[int_number] & (1 << bit_number)) == 0) {
    bit_value = 0;
  } else {
    bit_value = 1;
  }
  return bit_value;
}

void s21_set_bit_decimal(s21_decimal* num, int bit_place, int value) {
  int int_number = bit_place / 32;
  int bit_number = bit_place % 32;
  if (value == 0) {
    num->bits[int_number] &= ~(1 << bit_number);
  } else {
    num->bits[int_number] |= (1 << bit_number);
  }
}

int s21_get_bit_big_decimal(s21_big_decimal num, int bit_place) {
  int int_number = bit_place / 32;
  int bit_number = bit_place % 32;
  int bit_value;
  if ((num.bits[int_number] & (1 << bit_number)) == 0) {
    bit_value = 0;
  } else {
    bit_value = 1;
  }
  return bit_value;
}

void s21_set_bit_big_decimal(s21_big_decimal* num, int bit_place, int value) {
  int int_number = bit_place / 32;
  int bit_number = bit_place % 32;
  if (value == 0) {
    num->bits[int_number] &= ~(1 << bit_number);
  } else {
    num->bits[int_number] |= (1 << bit_number);
  }
}