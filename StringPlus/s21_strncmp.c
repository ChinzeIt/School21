#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int error = 0;
  bool flg = true;

  for (s21_size_t i = 0; i < n && flg; i++) {
    if (str1[i] != str2[i]) {
      error = str1[i] - str2[i];
      flg = false;
    }
  }
  return error;
}
