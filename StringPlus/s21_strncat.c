#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *result = dest;
  s21_size_t dest_len = 0;
  while (dest[dest_len] != '\0') {
    dest_len++;
  }

  if (n == 0) {
    return result;
  }
  s21_size_t i = 0;
  while (i < n && src[i] != '\0') {
    dest[dest_len + i] = src[i];
    i++;
  }
  dest[dest_len + i] = '\0';
  return result;
}