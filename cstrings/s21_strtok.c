// Breaks string str into a series of tokens separated by delim.

#include "s21_string.h"

unsigned int is_delim(char c, const char *delim) {
  while (*delim != '\0') {
    if (c == *delim) return 1;
    delim++;
  }
  return 0;
}
char *s21_strtok(char *str, const char *delim) {
  static char *backup_string;  // start of the next search
  if (!str) {
    str = backup_string;
  }
  if (!str) {
    // user is bad user
    return s21_NULL;
  }
  // handle beginning of the string containing delims
  while (1) {
    if (is_delim(*str, delim)) {
      str++;
      continue;
    }
    if (*str == '\0') {
      // we've reached the end of the string
      return s21_NULL;
    }
    break;
  }
  char *ret = str;
  while (1) {
    if (*str == '\0') {
      /*end of the input string and
      next exec will return s21_NULL*/
      backup_string = str;
      return ret;
    }
    if (is_delim(*str, delim)) {
      *str = '\0';
      backup_string = str + 1;
      return ret;
    }
    str++;
  }
}
