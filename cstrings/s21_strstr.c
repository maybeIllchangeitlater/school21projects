// Finds the first occurrence of the entire string needle (not including the
// terminating null character) which appears in the string haystack.

#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  const char *result = s21_NULL;
  for (; result == s21_NULL && *haystack != '\0'; haystack++) {
    if (s21_strncmp(needle, haystack, s21_strlen(needle)) == 0)
      result = haystack;
  }
  return (char *)result;
}