#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

s21_big_decimal s21_banking_rouding(s21_big_decimal num) {
  s21_big_decimal buff = num;
  int position = s21_find_last_bit(buff);
  int scale = s21_get_scale_big_decimal(buff);
  int sign = s21_get_sign_big_decimal(buff);
  s21_set_scale_big_decimal(&buff, 0);
  s21_set_sign_big_decimal(&buff, 0);

  s21_big_decimal part_of_div = buff;
  s21_big_decimal res_div = s21_init_big_decimal();
  s21_big_decimal rem_of_div = s21_init_big_decimal();
  s21_big_decimal ten = {{0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};

  bool flag = true;
  s21_big_decimal bank_res;
  while ((scale > 28) || (position > 95 && scale > 0 && flag)) {
    buff = part_of_div;
    part_of_div = s21_div_binary(buff, ten, &res_div);
    scale--;
    position = s21_find_last_bit(part_of_div);
    if (position == 0) {
      flag = false;
    }
  }
  if (!s21_check_mantissa_overflow(part_of_div)) {
    bank_res = part_of_div;
  } else {
    s21_big_decimal value = part_of_div;
    s21_normalization(&res_div, &part_of_div);
    s21_sub_binary(res_div, part_of_div, &rem_of_div);
    s21_set_scale_big_decimal(&rem_of_div, 0);
    bank_res = s21_bank_rouding_main(value, rem_of_div, scale, sign);
  }
  return bank_res;
}

s21_big_decimal s21_bank_rouding_main(s21_big_decimal value,
                                      s21_big_decimal rem_of_div, int scale,
                                      int sign) {
  s21_big_decimal zero = {{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
  s21_big_decimal one = {{0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
  s21_big_decimal five = {{0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
  s21_big_decimal bank_res = s21_init_big_decimal();

  if (s21_equal_binary(value, zero)) {
    bank_res = zero;
    scale = 0;
  } else {
    if (s21_equal_binary(rem_of_div, five)) {
      if (((value.bits[0]) & 1) == 1) {
        s21_add_binary(value, one, &bank_res);
      } else {
        bank_res = value;
      }
    } else if (s21_comparison_binary(rem_of_div, five)) {
      bank_res = value;
    } else {
      s21_add_binary(value, one, &bank_res);
    }
  }
  s21_set_scale_big_decimal(&bank_res, scale);
  s21_set_sign_big_decimal(&bank_res, sign);
  return bank_res;
}
