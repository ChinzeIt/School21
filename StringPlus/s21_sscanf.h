#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include "s21_string.h"

typedef struct {
  const char *f_ptr;
  const char *s_ptr;
  va_list args;
  int matched;
} sscanf_context;

int parse_format(sscanf_context *ctx);
int handle_specifier(sscanf_context *ctx, char specifier);
int parse_integer(const char **str, int base);
double parse_float(const char **str);

#endif