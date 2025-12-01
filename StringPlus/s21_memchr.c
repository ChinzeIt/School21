#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *memchrStr = (const unsigned char *)str;
  void *result = S21_NULL;
  for (s21_size_t i = 0; i < n && !result; i++) {
    if (memchrStr[i] == c) {
      result = (void *)&memchrStr[i];
    }
  }
  return result;
}