#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  if (!str || !format) return 0;

  sscanf_context ctx = {.f_ptr = format, .s_ptr = str, .matched = 0};
  va_start(ctx.args, format);

  while (*ctx.f_ptr) {
    if (*ctx.f_ptr == '%') {
      ctx.f_ptr++;
      if (!parse_format(&ctx)) break;
    }
  }

  va_end(ctx.args);
  return ctx.matched;
}

int parse_format(sscanf_context *ctx) {
  char specifier = *ctx->f_ptr++;
  return handle_specifier(ctx, specifier);
}

int handle_specifier(sscanf_context *ctx, char specifier) {
  switch (specifier) {
    case 'c': {
      char *c = va_arg(ctx->args, char *);
      if (*ctx->s_ptr) {
        *c = *ctx->s_ptr++;
        ctx->matched++;
      }
      break;
    }
    case 'd': {
      int *d = va_arg(ctx->args, int *);
      *d = parse_integer(&ctx->s_ptr, 10);
      ctx->matched++;
      break;
    }
    case 'f': {
      double *f = va_arg(ctx->args, double *);
      *f = parse_float(&ctx->s_ptr);
      ctx->matched++;
      break;
    }
    case 's': {
      char *s = va_arg(ctx->args, char *);
      while (*ctx->s_ptr && !isspace(*ctx->s_ptr)) {
        *s++ = *ctx->s_ptr++;
      }
      *s = '\0';
      ctx->matched++;
      break;
    }
    case '%': {
      if (*ctx->s_ptr == '%') {
        ctx->s_ptr++;
        ctx->matched++;
      }
      break;
    }
  }
  return 1;
}

int parse_integer(const char **str, int base) {
  int result = 0;
  int sign = 1;
  if (**str == '-') {
    sign = -1;
    (*str)++;
  }
  while (**str >= '0' && **str <= '9') {
    result = result * base + (**str - '0');
    (*str)++;
  }
  return result * sign;
}

double parse_float(const char **str) {
  double result = 0.0;

  int sign = 1;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  }

  while (**str >= '0' && **str <= '9') {
    result = result * 10.0 + (**str - '0');
    (*str)++;
  }

  if (**str == '.') {
    (*str)++;
    double divisor = 10.0;
    while (**str >= '0' && **str <= '9') {
      result += (**str - '0') / divisor;
      divisor *= 10.0;
      (*str)++;
    }
  }

  return result * sign;
}
