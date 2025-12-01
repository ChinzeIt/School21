#include "s21_sprintf.h"

void s21_sprintf(char *str, const char *format, ...) {
  va_list arguments;
  va_start(arguments, format);
  while (*format) {
    if (*format == '%') {
      format++;
      int padding = 0, precision = 0;
      chek_flag(&format, &padding, &precision);
      switch (*format) {
        case 'c':
          spec_c(&str, va_arg(arguments, int), padding);
          break;
        case 'd':
          if (flags.h)
            spec_d(&str, (short)va_arg(arguments, int), padding, precision);
          else if (flags.l)
            spec_d(&str, va_arg(arguments, long long), padding, precision);
          else
            spec_d(&str, va_arg(arguments, int), padding, precision);
          break;
        case 'f':
          spec_f(&str, va_arg(arguments, double), padding, precision);
          break;
        case 's':
          spec_s(&str, va_arg(arguments, char *), padding, precision);
          break;
        case 'u':
          if (flags.h)
            spec_u(&str, (unsigned short)va_arg(arguments, unsigned int),
                   padding, precision);
          else if (flags.l)
            spec_u(&str, va_arg(arguments, unsigned long), padding, precision);
          else
            spec_u(&str, va_arg(arguments, unsigned int), padding, precision);
          break;
        case '%':
          *str++ = '%';
          break;
      }
    } else
      *str++ = *format;
    format++;
  }
  *str++ = '\0';
  va_end(arguments);
}

void init() {
  flags.count = 0;
  flags.znak = false;
  flags.plus = false;
  flags.minus = false;
  flags.space = false;
  flags.defaluteprec = false;
  flags.h = false;
  flags.l = false;
}

void chek_flag(const char **format, int *padding, int *precision) {
  int count_flag = 0, count_mod = 0;
  init();
  while ((**format == '+' || **format == '-' || **format == ' ') &&
         count_flag < 3) {
    switch (**format) {
      case '+':
        flags.plus = true;
        (*format)++;
        break;
      case '-':
        flags.minus = true;
        (*format)++;
        break;
      case ' ':
        flags.space = true;
        (*format)++;
        break;
    }
    count_flag++;
  }
  while (**format >= '0' && **format <= '9') {
    *padding = *padding * 10 + (**format - '0');
    (*format)++;
  }
  if (**format == '.') {
    (*format)++;
    while (**format >= '0' && **format <= '9') {
      *precision = *precision * 10 + (**format - '0');
      (*format)++;
    }
  } else
    flags.defaluteprec = true;
  while ((**format == 'h' || **format == 'l') && count_mod < 2) {
    switch (**format) {
      case 'h':
        flags.h = true;
        (*format)++;
        break;
      case 'l':
        flags.l = true;
        (*format)++;
        break;
    }
    count_mod++;
  }
}

void spec_c(char **str, char symbol, int padding) {
  padding--;
  if (!flags.minus)
    while (padding-- > 0) *(*str)++ = ' ';
  *(*str)++ = symbol;
  if (flags.minus)
    while (padding-- > 0) *(*str)++ = ' ';
}

void spec_d(char **str, long long symbol, int padding, int precision) {
  if (symbol == 0) {
    if (precision == 0) padding--;
    padding_zero_for_d(str, &padding, &precision);
    if (flags.defaluteprec) *(*str)++ = '0';
  } else {
    if (symbol < 0) {
      flags.znak = true;
      flags.space = false;
      symbol = -symbol;
      --padding;
    }
    char template[1024] = {0};
    while (symbol > 0) {
      template[flags.count++] = (symbol % 10) + '0';
      symbol /= 10;
    }
    padding_zero_for_d(str, &padding, &precision);
    while (flags.count > 0) *(*str)++ = template[--flags.count];
  }
  if (flags.minus)
    while (padding-- > 0) *(*str)++ = ' ';
}

void padding_zero_for_d(char **str, int *padding, int *precision) {
  *padding = *padding - flags.count - flags.plus;
  *precision -= flags.count;
  if (*padding < 0 && *precision > 0) {
    if (flags.plus && !flags.znak) *(*str)++ = '+';
    flags.plus = false;
    if (flags.space) *(*str)++ = ' ';
    flags.space = false;
    if (flags.znak) *(*str)++ = '-';
    flags.znak = false;
    while ((*precision)-- > 0) *(*str)++ = '0';
  } else if (*precision > 0)
    *padding -= *precision;
  if (*padding < 0 && flags.space) *(*str)++ = ' ';
  if (!flags.plus && flags.minus && flags.space && *padding > 0)
    *(*str)++ = ' ';
  if (*padding >= 0 && flags.minus && flags.space) --(*padding);
  if (flags.plus && flags.znak) (*padding)++;
  if (!flags.minus)
    while ((*padding)-- > 0) *(*str)++ = ' ';
  if (flags.plus && !flags.znak) *(*str)++ = '+';
  if (flags.znak) *(*str)++ = '-';
  if (!flags.minus && *precision > 0)
    while ((*precision)-- > 0) *(*str)++ = '0';
  if (flags.minus && *precision > 0)
    while ((*precision)-- > 0) *(*str)++ = '0';
}

void spec_f(char **str, double symbol, int padding, int precision) {
  int part_int = 0, count_d = 0;
  double part_double = 0.0;
  start_spec_f(str, &symbol, &precision, &padding, &part_int, &part_double,
               &count_d);
  padding = padding - count_d - flags.plus - flags.znak;
  add_symbols_f(str, padding);
  if (part_int == 0)
    *(*str)++ = '0';
  else {
    char template[1024] = {0};
    while (part_int > 0) {
      template[flags.count++] = (part_int % 10) + '0';
      part_int /= 10;
    }
    while (flags.count-- > 0) *(*str)++ = template[flags.count];
  }
  if (precision > 0) {
    *(*str)++ = '.';
    for (int i = 0; i < precision; i++) {
      part_double *= 10;
      int part_double_temp = (int)part_double;
      *(*str)++ = part_double_temp + '0';
      part_double -= part_double_temp;
    }
  }
  if (flags.minus)
    while (padding-- > 0) *(*str)++ = ' ';
}

void start_spec_f(char **str, double *symbol, int *precision, int *padding,
                  int *part_int, double *part_double, int *count_d) {
  if (flags.defaluteprec) *precision = 6;
  if (*symbol < 0 || 1.0 / *symbol < 0) {
    flags.plus = false;
    flags.znak = true;
    *symbol = -(*symbol);
  }
  double round = 0.5;
  for (int i = 0; i < *precision; i++) round /= 10.0;
  *symbol += round;
  *part_int = (int)(*symbol);
  *part_double = *symbol - *part_int;
  *count_d = count_double(*part_int, *part_double, *precision);
  if (flags.space && !flags.znak && !flags.plus) {
    *(*str)++ = ' ';
    if (*padding > 0) (*padding)--;
  }
}

void add_symbols_f(char **str, int padding) {
  if (!flags.minus)
    while (padding-- > 0) *(*str)++ = ' ';
  if (flags.plus) *(*str)++ = '+';
  if (flags.znak) *(*str)++ = '-';
}

int count_double(int part_int, double part_double, int precision) {
  int count_d = 0;
  if (part_int == 0)
    count_d++;
  else {
    while (part_int > 0) {
      part_int /= 10;
      count_d++;
    }
  }
  if (precision > 0) {
    count_d++;
    for (int i = 0; i < precision; i++) {
      part_double *= 10;
      int part_temp = (int)part_double;
      part_double -= part_temp;
      count_d++;
    }
  }
  return count_d;
}

void spec_s(char **str, char *symbol, int padding, int precision) {
  char *temp_symbol = symbol;
  while (*temp_symbol++) {
    flags.count++;
  }
  if (flags.defaluteprec) {
    padding -= flags.count;
    if (!flags.minus)
      while (padding-- > 0) *(*str)++ = ' ';
    while (*symbol) *(*str)++ = *symbol++;
  } else {
    padding -= precision;
    if (!flags.minus)
      while (padding-- > 0) *(*str)++ = ' ';
    while (*symbol && precision-- > 0) *(*str)++ = *symbol++;
  }
  if (flags.minus)
    while (padding-- > 0) *(*str)++ = ' ';
}

void spec_u(char **str, unsigned long symbol, int padding, int precision) {
  char template[1024] = {0};
  if (symbol == 0) {
    --precision;
    if (precision > 0)
      padding = padding - 1 - precision;
    else
      --padding;
    if (!flags.minus)
      while (padding-- > 0) *(*str)++ = ' ';
    if (precision > 0) *(*str)++ = '0';
    while (precision-- > 0) *(*str)++ = '0';
    if (flags.defaluteprec) *(*str)++ = '0';
  } else {
    while (symbol > 0) {
      template[flags.count++] = (symbol % 10) + '0';
      symbol /= 10;
    }
    precision -= flags.count;
    if (precision > 0)
      padding = padding - flags.count - precision;
    else
      padding -= flags.count;
    if (!flags.minus)
      while (padding-- > 0) *(*str)++ = ' ';
    while (precision-- > 0) *(*str)++ = '0';
    while (flags.count > 0) {
      flags.count--;
      *(*str)++ = template[flags.count];
    }
  }
  if (flags.minus)
    while (padding-- > 0) *(*str)++ = ' ';
}