// Compares at most the first n bytes of str1 and str2.

#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t len = 0;
  while (str1[len] && (str1[len] == str2[len]) && len < n) len++;
  int result;
  if (len == n)
    result = (int)(str1[len - 1] - str2[len - 1]);
  else
    result = (int)(str1[len] - str2[len]);
  return result;
}