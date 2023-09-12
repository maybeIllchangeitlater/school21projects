// Searches for the last occurrence of the character c (an unsigned char) in the
// string pointed to by the argument str.

#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *temp = s21_NULL;
  int len = 0;
  while (*str != '\0') {
    str++;
    len++;
  }

  while (len >= 0) {
    if (*str == c) {
      temp = str;
      break;
    }
    str--;
    len--;
  }
  return (char *)temp;
}