#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int len = 0;
  while (str[len] != '\0' && str[len] != c) {
    len++;
  }
  return c == str[len] ? (char *)str + len : S21_NULL;
}
