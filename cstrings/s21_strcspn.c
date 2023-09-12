// Calculates the length of the initial segment of str1 which consists entirely
// of characters not in str2.

#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t counter = 0;
  for (; counter < s21_strlen(str1); counter++)
    if (s21_strchr(str2, str1[counter])) break;
  return counter;
}