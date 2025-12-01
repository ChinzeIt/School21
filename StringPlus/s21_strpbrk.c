#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t sym_str1 = s21_strlen(str1);
  s21_size_t sym_str2 = s21_strlen(str2);
  char *ptr = S21_NULL;
  bool flg = true;

  for (s21_size_t i = 0; i < sym_str1 && flg; i++) {
    for (s21_size_t j = 0; j < sym_str2 && flg; j++) {
      if (str1[i] == str2[j]) {
        ptr = (char *)&str1[i];
        flg = false;
      }
    }
  }
  return (char *)ptr;
}
