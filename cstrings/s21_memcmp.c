#include "s21_string.h"
/*
Compares characters in two buffers.

Parameters:
str1: First buffer.
str2: Second buffer.
n: Number of characters to compare. (Compares bytes for memcmp).

Return Value:
The return value indicates the relationship between the buffers.
< 0 buf1 less than buf2
0 buf1 identical to buf2
> 0 buf1 greater than buf2

Remarks:
Compares the first count characters of buf1 and buf2
and returns a value that indicates their relationship.
The sign of a non-zero return value is the sign of the difference
between the first differing pair of values in the buffers.
The values are interpreted as unsigned char for memcmp.
*/
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int char_compare_status = 0;
  if (str1 && str2) {
    const unsigned char *arr_1 = (unsigned char *)str1;
    const unsigned char *arr_2 = (unsigned char *)str2;
    s21_size_t flag = 1;
    if (arr_1 == arr_2) {
      flag = 0;
    }
    while (n > 0 && flag) {
      if (*arr_1 != *arr_2) {
        char_compare_status = *arr_1 - *arr_2;
        flag = 0;
      }
      n--;
      arr_1++;
      arr_2++;
    }
  }
  return char_compare_status;
}
