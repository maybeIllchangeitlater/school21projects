// Appends the string pointed to, by src to the end of the string pointed to, by
// dest up to n characters long.

#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t j = 0, i = s21_strlen(dest);
  for (; j < n && j < s21_strlen(src); i++, j++) {
    dest[i] = src[j];
  }
  dest[i] = '\0';
  return dest;
}