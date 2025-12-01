#include "s21_string.h"

void *s21_to_upper(const char *str) {
  s21_size_t length = s21_strlen(str);
  char *upper_str = (char *)malloc((length + 1) * sizeof(char));

  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      upper_str[i] = str[i] - ('a' - 'A');
    } else {
      upper_str[i] = str[i];
    }
  }
  upper_str[length] = '\0';

  return upper_str;
}