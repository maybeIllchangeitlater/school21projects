#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *result = malloc(sizeof(char *) * s21_strlen(str) + 1);
  if (result == s21_NULL) return s21_NULL;
  s21_size_t i = 0;
  for (; i < s21_strlen(str); i++) {
    if (str[i] >= 97 && str[i] <= 122)
      result[i] = str[i] - 32;
    else
      result[i] = str[i];
  }
  result[i] = '\0';
  return (void *)result;
}