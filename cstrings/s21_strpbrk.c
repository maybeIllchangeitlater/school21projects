// Finds the first character in the string str1 that matches any character
// specified in str2.

#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int status = 0;
  for (; *str1 != '\0'; str1++)
    if (s21_strchr(str2, *str1)) {
      status = 1;
      break;
    }
  return status ? (char *)str1 : s21_NULL;
}
