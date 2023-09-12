// Searches for the first occurrence of the character c (an unsigned char) in
// the string pointed to, by the argument str.

#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  const char *temp = s21_NULL;
  while (*str != '\0') {
    if (*str == c) {
      temp = str;
      break;
    }
    str++;
  }
  return (char *)temp;
}