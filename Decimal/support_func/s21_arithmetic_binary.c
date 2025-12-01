#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

void s21_add_binary(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  *result = s21_init_big_decimal();
  for (int i = 0; i <= 223; i++) {
    int val_1 = s21_get_bit_big_decimal(value_1, i);
    int val_2 = s21_get_bit_big_decimal(value_2, i);

    s21_set_bit_big_decimal(result, i, val_1 ^ val_2);

    if (val_1 == 1 && val_2 == 1) {
      int j = i + 1;
      while ((val_1 = s21_get_bit_big_decimal(value_1, j)) != 0) {
        s21_set_bit_big_decimal(&value_1, j, 0);
        j++;
      }
      s21_set_bit_big_decimal(&value_1, j, 1);
    }
  }
}

void s21_sub_binary(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  *result = s21_init_big_decimal();
  int scale = s21_get_scale_big_decimal(value_1);

  for (int i = 0; i <= 224; i++) {
    int val_1 = s21_get_bit_big_decimal(value_1, i);
    int val_2 = s21_get_bit_big_decimal(value_2, i);

    s21_set_bit_big_decimal(result, i, val_1 ^ val_2);

    if (val_1 == 0 && val_2 == 1) {
      int j = i + 1;
      while ((val_1 = s21_get_bit_big_decimal(value_1, j)) != 1) {
        s21_set_bit_big_decimal(&value_1, j, 1);
        j++;
      }
      s21_set_bit_big_decimal(&value_1, j, 0);
    }
  }
  s21_set_scale_big_decimal(result, scale);
}

void s21_mul_binary(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result) {
  s21_big_decimal copy_num_1 = value_1;
  s21_big_decimal buff_1 = s21_init_big_decimal();

  int lenght_val_2 = s21_find_last_bit(value_2);

  for (int i = 0; i <= lenght_val_2; i++) {
    if (s21_get_bit_big_decimal(value_2, i) == 1) {
      s21_add_binary(copy_num_1, buff_1, result);
      s21_shift_left(&copy_num_1, 1);
      buff_1 = *result;
    } else {
      s21_shift_left(&copy_num_1, 1);
    }
  }
  int scale_res =
      s21_get_scale_big_decimal(value_1) + s21_get_scale_big_decimal(value_2);
  s21_set_scale_big_decimal(result, scale_res);
}

s21_big_decimal s21_div_binary(s21_big_decimal value_1, s21_big_decimal value_2,
                               s21_big_decimal *result) {
  s21_big_decimal buff = s21_init_big_decimal();
  s21_big_decimal buff_2 = s21_init_big_decimal();
  s21_big_decimal rem_of_div = value_1;
  s21_big_decimal divider = value_2;
  s21_big_decimal temp_res = s21_init_big_decimal();
  s21_big_decimal ten = {{0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
  s21_big_decimal smth = s21_init_big_decimal();
  *result = s21_init_big_decimal();

  s21_normaliz_for_div(&rem_of_div, &divider);
  int scale_res = 0, count = 0, count_2 = 0;
  while ((s21_is_zero(rem_of_div) == false) && (scale_res < 29)) {
    int last_bit_num_1 = 0;
    int bit_buff = 0, bit_res = 0;
    if (count > 0) s21_mul_binary(*result, ten, result);
    while (s21_comparison_binary(rem_of_div, divider) == 1) {
      s21_mul_binary(rem_of_div, ten, &buff);
      rem_of_div = buff;
      scale_res++;
      if (count_2 > 0) s21_mul_binary(*result, ten, result);
      count_2++;
    }
    count_2 = 0;
    last_bit_num_1 = s21_find_last_bit(rem_of_div);
    bit_buff = s21_find_last_bit(rem_of_div) - s21_find_last_bit(divider);
    bit_res = bit_buff;
    for (int i = 0; i <= last_bit_num_1; i++) {
      s21_set_bit_big_decimal(&buff_2, i,
                              s21_get_bit_big_decimal(rem_of_div, bit_buff));
      bit_buff++;
    }
    s21_division_num(&buff_2, divider, &temp_res, rem_of_div, bit_res);
    s21_shift_right(&temp_res, 1);
    s21_shift_right(&buff_2, 1);
    rem_of_div = buff_2;
    buff = s21_init_big_decimal();
    buff_2 = s21_init_big_decimal();
    if (scale_res == 0) {
      smth = temp_res;
    }
    s21_add_binary(temp_res, *result, result);
    temp_res = s21_init_big_decimal();
    count++;
  }
  s21_set_scale_big_decimal(result, scale_res);
  return smth;
}

void s21_division_num(s21_big_decimal *buff_2, s21_big_decimal divider,
                      s21_big_decimal *temp_res, s21_big_decimal rem_of_div,
                      int bit_res) {
  while (bit_res >= 0) {
    if (s21_comparison_binary(*buff_2, divider) == 0) {
      s21_set_bit_big_decimal(temp_res, 0, 1);
      s21_sub_binary(*buff_2, divider, buff_2);
    } else {
      s21_set_bit_big_decimal(temp_res, 0, 0);
    }
    s21_shift_left(temp_res, 1);
    s21_shift_left(buff_2, 1);
    bit_res--;
    s21_set_bit_big_decimal(buff_2, 0,
                            s21_get_bit_big_decimal(rem_of_div, bit_res));
  }
}