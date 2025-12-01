#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t len_src = s21_strlen(src);
  s21_size_t len_str = s21_strlen(str);
  char *res = S21_NULL;

  if (start_index <= len_src && (len_src != 0 || len_str != 0)) {
    res = (char *)calloc((len_src + len_str + 1), sizeof(char));
    if (res != S21_NULL) {
      s21_size_t src_i = 0, str_i = 0, res_i = 0;
      while (src_i < start_index) {
        res[res_i] = src[src_i];
        src_i++;
        res_i++;
      }
      while (str_i < len_str) {
        res[res_i] = str[str_i];
        str_i++;
        res_i++;
      }
      while (src_i < len_src) {
        res[res_i] = src[src_i];
        src_i++;
        res_i++;
      }
    }
  }
  return res;
}