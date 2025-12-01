#include "../s21_decimal.h"
#include "s21_decimal_support_func.h"

void s21_seven_num(const char *tempold, char *temp) {
  int count = 0, countseven = 0;
  while (tempold[count] != '\0') {
    if (tempold[count] != '0' && tempold[count] != '.') {
      countseven++;
    }
    if (countseven < 8) {
      temp[count] = tempold[count];
    } else {
      if (tempold[count] != '.')
        temp[count] = '0';
      else
        temp[count] = '.';
    }
    count++;
  }
  temp[count] = '\0';
}

void s21_delete_zeros(char *temp) {
  const char *point_position = strchr(temp, '.');
  if (point_position != NULL) {
    char *end = temp + strlen(temp) - 1;
    while (end > point_position && *end == '0') {
      *end = '\0';
      end--;
    }
    if (*end == '.') {
      *end = '\0';
    }
  }
}

void s21_put_float_in_decimal(long double x, s21_decimal *dst) {
  int countbits = 0;
  while (x >= 1.0 && countbits < 96) {
    if (fmodl(x, 2.0) == 1.0) {
      s21_set_bit_decimal(dst, countbits, 1);
    }
    x = floorl(x / 2.0);
    countbits++;
  }
}

int s21_decimal_to_big_decimal(s21_decimal src, s21_big_decimal *dst) {
  s21_name_of_const flag = S21_CONVERTER_OK;
  if (!dst) {
    flag = S21_CONVERTER_ERROR;
  } else {
    *dst = s21_init_big_decimal();
    for (int i = 0; i < 3; i++) {
      dst->bits[i] = src.bits[i];
    }
    dst->bits[7] = src.bits[3];
  }
  return flag;
}