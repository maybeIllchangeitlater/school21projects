
#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *return_pointer = s21_NULL;
  if (str) {
    for (s21_size_t i = 0; i < n; i++) {
      if (*(char *)str == c) {
        return_pointer = (char *)str;
        break;
      }
      str++;
    }
  }
  return return_pointer;
}