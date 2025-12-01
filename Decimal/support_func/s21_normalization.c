#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

void s21_normalization(s21_big_decimal* value1, s21_big_decimal* value2) {
  int scale1 = s21_get_scale_big_decimal(*value1);
  int sign1 = s21_get_sign_big_decimal(*value1);
  int sign2 = s21_get_sign_big_decimal(*value2);
  int scale2 = s21_get_scale_big_decimal(*value2);
  s21_set_scale_big_decimal(value1, 0);
  s21_set_scale_big_decimal(value2, 0);

  while (scale1 < scale2) {
    s21_big_decimal_multiply_by_10(value1);
    scale1++;
  }
  while (scale2 < scale1) {
    s21_big_decimal_multiply_by_10(value2);
    scale2++;
  }

  s21_set_scale_big_decimal(value1, scale1);
  s21_set_sign_big_decimal(value1, sign1);

  s21_set_scale_big_decimal(value2, scale2);
  s21_set_sign_big_decimal(value2, sign2);
}

int s21_big_decimal_multiply_by_10(s21_big_decimal* value) {
  s21_name_of_const code = S21_ARITHMETIC_OK;
  s21_big_decimal ten = {{0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
  s21_mul_binary(*value, ten, value);
  return code;
}

void s21_normaliz_for_div(s21_big_decimal* value_1, s21_big_decimal* value_2) {
  int scale_1 = s21_get_scale_big_decimal(*value_1);
  int scale_2 = s21_get_scale_big_decimal(*value_2);
  s21_big_decimal buff_num_1 = *value_1;
  s21_big_decimal buff_num_2 = *value_2;
  s21_big_decimal ten = {{0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};

  if (scale_1 > 0) {
    for (int i = 0; i < scale_1; i++) {
      s21_mul_binary(*value_2, ten, &buff_num_2);
      *value_2 = buff_num_2;
    }
  }
  if (scale_2 > 0) {
    for (int i = 0; i < scale_2; i++) {
      s21_mul_binary(*value_1, ten, &buff_num_1);
      *value_1 = buff_num_1;
    }
  }
  s21_set_scale_big_decimal(value_1, 0);
  s21_set_scale_big_decimal(value_2, 0);
}
