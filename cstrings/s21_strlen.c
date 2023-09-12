// Computes the length of the string str up to but not including the terminating
// null character.

#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t str_len = 0;
  while (str[str_len] != '\0') str_len++;
  return str_len;
}