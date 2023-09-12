// Copies up to n characters from the string pointed to, by src to dest.

#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n && i < s21_strlen(src); i++) dest[i] = src[i];
  return dest;
}