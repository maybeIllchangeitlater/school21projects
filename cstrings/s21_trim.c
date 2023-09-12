// Returns a new string in which all leading and trailing
// occurrences of a set of specified characters (trim_chars) from the given
// string (src) are removed. In case of any error, return NULL

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *start = (char *)src;
  char *end = (char *)(src + s21_strlen(src) - 1);
  while (*start != '\0' && s21_strchr(trim_chars, *start)) start++;
  while (end >= start && s21_strchr(trim_chars, *end)) end--;
  s21_size_t trimmed_len = end - start + 1;
  char *res = malloc(sizeof(char) * (trimmed_len + 1));
  s21_strncpy(res, start, trimmed_len);
  res[trimmed_len] = '\0';
  return (void *)res;
}
