#include "s21_string.h"
/*
Parameters:

dest: new buffer.
src: Buffer to copy from.
count: Number of characters to copy.

Return value: The value of dest.

Remarks:

memcpy copies count bytes from src to dest;
If the source and destination regions overlap,
the behavior of memcpy is undefined.
Use s21_memmove to handle overlapping regions.
*/
void *s21_memcpy(void *dest, const void *src, s21_size_t count) {
  const unsigned char *copy_src = (unsigned char *)src;
  unsigned char *copy_dest = (unsigned char *)dest;
  for (size_t i = 0; i < count; i++) {
    copy_dest[i] = copy_src[i];
  }
  return dest;
}