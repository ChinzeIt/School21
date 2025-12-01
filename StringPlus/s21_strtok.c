#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *ptr = S21_NULL;
  char *new_str = S21_NULL;
  bool flg = true;

  if (str != S21_NULL) ptr = str;
  if (ptr == S21_NULL) flg = false;

  if (flg) {
    while (*ptr && s21_strchr(delim, *ptr)) {
      ptr++;
    }
    if (*ptr == '\0') {
      ptr = S21_NULL;
      flg = false;
    }
    if (flg) {
      new_str = ptr;
      while (!s21_strchr(delim, *ptr)) {
        ptr++;
      }
      if (*ptr) {
        *ptr = '\0';
        ptr++;
      } else {
        ptr = S21_NULL;
      }
    }
  }
  return new_str;
}
