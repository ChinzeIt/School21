#ifndef S21_DECIMAL_SUPPORT_FUNC_H
#define S21_DECIMAL_SUPPORT_FUNC_H

#include "../s21_decimal.h"

// s21_arithmetic_binary.c
void s21_add_binary(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
void s21_sub_binary(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
void s21_mul_binary(s21_big_decimal value_1, s21_big_decimal value_2,
                    s21_big_decimal *result);
s21_big_decimal s21_div_binary(s21_big_decimal value_1, s21_big_decimal value_2,
                               s21_big_decimal *result);
void s21_division_num(s21_big_decimal *buff_2, s21_big_decimal divider,
                      s21_big_decimal *temp_res, s21_big_decimal rem_of_div,
                      int bit_res);

// s21_bank_rouding.c
s21_big_decimal s21_banking_rouding(s21_big_decimal num);
s21_big_decimal s21_bank_rouding_main(s21_big_decimal value,
                                      s21_big_decimal rem_of_div, int scale,
                                      int sign);

// s21_comparison_binary.c
s21_big_decimal s21_abs(s21_big_decimal num);
int s21_comparison_binary(s21_big_decimal num1, s21_big_decimal num2);
int s21_equal_binary(s21_big_decimal num1, s21_big_decimal num2);

// s21_for_converter.c
void s21_seven_num(const char *tempold, char *temp);
void s21_delete_zeros(char *temp);
void s21_put_float_in_decimal(long double x, s21_decimal *dst);
int s21_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst);

// s21_from_big_to_dec.c
int s21_from_big_decimal_to_decimal(s21_big_decimal num, s21_decimal *decimal);
bool s21_check_mantissa_overflow(s21_big_decimal num);

// s21_get_set_func.c
int s21_get_sign_decimal(s21_decimal num);
void s21_set_sign_decimal(s21_decimal *num, int sign);
int s21_get_scale_decimal(s21_decimal num);
void s21_set_scale_decimal(s21_decimal *num, int scale_value);
int s21_get_bit_decimal(s21_decimal num, int bit_place);
void s21_set_bit_decimal(s21_decimal *num, int bit_place, int value);
int s21_get_sign_big_decimal(s21_big_decimal num);
void s21_set_sign_big_decimal(s21_big_decimal *num, int sign);
int s21_get_scale_big_decimal(s21_big_decimal num);
void s21_set_scale_big_decimal(s21_big_decimal *num, int scale_value);
int s21_get_bit_big_decimal(s21_big_decimal num, int bit_place);
void s21_set_bit_big_decimal(s21_big_decimal *num, int bit_place, int value);

// s21_normalization.c
void s21_normalization(s21_big_decimal *value1, s21_big_decimal *value2);
int s21_big_decimal_multiply_by_10(s21_big_decimal *value);
void s21_normaliz_for_div(s21_big_decimal *value_1, s21_big_decimal *value_2);

// s21_other_useful_func.c
s21_decimal s21_init_decimal();
s21_big_decimal s21_init_big_decimal();
int s21_checking_decimal_for_correct(s21_decimal num);
int s21_is_zero(s21_big_decimal num);
int s21_is_zero_dec(s21_decimal num);
int s21_find_last_bit(s21_big_decimal num);

// s21_shift.c
int s21_shift_left(s21_big_decimal *num, int step);
void s21_shift_right(s21_big_decimal *num, int step);

#endif