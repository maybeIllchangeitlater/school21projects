// Returns a new string in which a specified string (str) is inserted at a
// specified index position (start_index) in the given string (src). In case of
// any error, return NULL - needs werk
// pls don't leak

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  s21_size_t str_len = s21_strlen(str);
  s21_size_t src_len = s21_strlen(src);
  if (start_index > src_len) return s21_NULL;
  char *result = malloc((src_len + str_len + 1) * sizeof(char));
  if (result == s21_NULL) return s21_NULL;
  s21_strncpy(result, src, start_index);
  s21_strncpy(result + start_index, str, str_len);
  s21_strncpy(result + start_index + str_len, src + start_index,
              src_len - start_index);
  result[src_len + str_len] = '\0';
  return (void *)result;
}