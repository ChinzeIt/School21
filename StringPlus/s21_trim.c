#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;

  if (src != S21_NULL && trim_chars != S21_NULL) {
    s21_size_t start = 0;
    s21_size_t end = s21_strlen(src);

    while (start < end && s21_strchr(trim_chars, src[start])) {
      start++;
    }
    while (end > start && s21_strchr(trim_chars, src[end - 1])) {
      end--;
    }
    s21_size_t len_trim = end - start;
    res = (char *)malloc(len_trim + 1);
    if (res != S21_NULL) {
      s21_strncpy(res, src + start, len_trim);
      res[len_trim] = '\0';
    }
  }
  return res;
}