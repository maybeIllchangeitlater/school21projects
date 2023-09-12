#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *copy_str = (unsigned char *)str;
  while (n > 0) {
    *copy_str++ = c;
    n--;
  }
  return str;
}
