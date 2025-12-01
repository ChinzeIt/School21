#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *ptr = S21_NULL;

  s21_size_t sym_str = s21_strlen(str);

  for (s21_size_t len = 0; len <= sym_str; len++) {
    if (str[len] == c) {
      s21_size_t sym = 0;
      sym = len;
      ptr = (char *)&str[sym];
    }
  }
  return (char *)ptr;
}