#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t sym_h = s21_strlen(haystack);
  s21_size_t sym_n = s21_strlen(needle);
  int error = 0;
  char *ptr = S21_NULL;

  if (sym_n > sym_h) {
    ptr = S21_NULL;
    error = 1;
  }

  if (sym_n == 0) {
    ptr = (char *)haystack;
    error = 1;
  }

  if (error == 0) {
    bool flg = true;
    for (s21_size_t i = 0; i <= sym_h - sym_n && flg; i++) {
      if (s21_strncmp(haystack + i, needle, sym_n) == 0) {
        ptr = (char *)(haystack + i);
        flg = false;
      }
    }
  }
  return ptr;
}