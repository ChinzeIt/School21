#include "s21_decimal.h"
#include "support_func/s21_decimal_support_func.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_name_of_const flag = S21_CONVERTER_OK;
  if (!dst) {
    flag = S21_CONVERTER_ERROR;
  } else {
    *dst = s21_init_decimal();

    int sign = S21_POSITIVE;
    if (src < 0) {
      sign = S21_NEGATIVE;
      if (src != -2147483648) src = -src;
    }
    s21_set_sign_decimal(dst, sign);

    dst->bits[0] = src;
  }
  return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_name_of_const flag = S21_CONVERTER_OK;

  if (!dst) {
    flag = S21_CONVERTER_ERROR;
  } else if (src == 0.0) {
    *dst = s21_init_decimal();
    flag = S21_CONVERTER_OK;
  } else if (0 < fabs(src) && fabs(src) < 1e-28) {
    flag = S21_CONVERTER_ERROR;
  } else if (fabs(src) > 79228162514264337593543950335.0 || isinf(src) ||
             isnan(src)) {
    flag = S21_CONVERTER_ERROR;
  } else {
    *dst = s21_init_decimal();

    int sign = S21_POSITIVE;
    if (src < 0) {
      sign = S21_NEGATIVE;
      src = -src;
    }
    s21_set_sign_decimal(dst, sign);

    char tempold[1024], temp[1024];
    sprintf(tempold, "%.28f", src);

    s21_seven_num(tempold, temp);
    s21_delete_zeros(temp);

    int scale = 0, flagscale = 0, i = 0;
    while (temp[i] != '\0' && scale < 28) {
      if (flagscale == 1) scale++;
      if (temp[i] == '.') flagscale = 1;
      i++;
    }
    s21_set_scale_decimal(dst, scale);

    long double x = atof(temp);
    if (scale > 0) x *= pow(10, scale);
    s21_put_float_in_decimal(x, dst);
  }
  return flag;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_name_of_const flag = S21_CONVERTER_OK;

  if (!dst) {
    flag = S21_CONVERTER_ERROR;
  } else if (src.bits[1] != 0 || src.bits[2] != 0) {
    flag = S21_CONVERTER_ERROR;
  } else {
    int scale = s21_get_scale_decimal(src), value = src.bits[0];
    while (scale != 0) {
      value /= 10;
      scale--;
    }

    *dst = (int)value;

    if (s21_get_sign_decimal(src)) *dst = -*dst;
  }
  return flag;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  s21_name_of_const flag = S21_CONVERTER_OK;

  if (!dst) {
    flag = S21_CONVERTER_ERROR;
  } else {
    int count = 0;
    long double x = 0;
    while (count < 96) {
      if (s21_get_bit_decimal(src, count)) x += pow(2, count);
      count++;
    }

    int sign = s21_get_sign_decimal(src), scale = s21_get_scale_decimal(src);
    while (scale != 0) {
      x /= 10;
      scale--;
    }
    if (sign == 1) x = -x;

    *dst = x;
  }
  return flag;
}