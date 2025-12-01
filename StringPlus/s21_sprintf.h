#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include "s21_string.h"

struct flags {
  int count;
  bool znak, plus, minus, space, defaluteprec, h, l;
} flags;

void init();
void chek_flag(const char **format, int *padding, int *precision);
void spec_c(char **str, char symbol, int padding);
void spec_d(char **str, long long symbol, int padding, int precision);
void padding_zero_for_d(char **str, int *padding, int *precision);
void spec_f(char **str, double symbol, int padding, int precision);
void start_spec_f(char **str, double *symbol, int *precision, int *padding,
                  int *part_int, double *part_double, int *count_d);
void add_symbols_f(char **str, int padding);
int count_double(int part_int, double part_double, int precision);
void spec_s(char **str, char *symbol, int padding, int precision);
void spec_u(char **str, unsigned long symbol, int padding, int precision);

#endif