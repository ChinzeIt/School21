#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

s21_decimal s21_init_decimal() {
  s21_decimal result = {{0, 0, 0, 0}};
  return result;
}

s21_big_decimal s21_init_big_decimal() {
  s21_big_decimal result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  return result;
}

int s21_checking_decimal_for_correct(s21_decimal num) {
  s21_big_decimal_bits7 buff;
  buff.last_int = num.bits[3];
  int err = true;
  if ((buff.bits7.zero_0_15 != 0) || (buff.bits7.zero_24_30 != 0)) {
    err = false;
  } else if (buff.bits7.scale > 28) {
    err = false;
  }
  return err;
}

int s21_is_zero(s21_big_decimal num) {
  bool flag = false;
  if ((num.bits[0] == 0) && (num.bits[1] == 0) && (num.bits[2] == 0) &&
      (num.bits[3] == 0) && (num.bits[4] == 0) && (num.bits[5] == 0) &&
      (num.bits[6] == 0)) {
    flag = true;
  }
  return flag;
}

int s21_is_zero_dec(s21_decimal num) {
  bool flag = false;
  if ((num.bits[0] == 0) && (num.bits[1] == 0) && (num.bits[2] == 0)) {
    flag = true;
  }
  return flag;
}

int s21_find_last_bit(s21_big_decimal num) {
  int position = 0;

  if (s21_is_zero(num) == 1) {
    position = 223;
  } else {
    for (int i = 223; ((s21_get_bit_big_decimal(num, i) & 1) != 1) && i >= 0;
         i--) {
      position++;
    }
  }
  return 223 - position;
}
