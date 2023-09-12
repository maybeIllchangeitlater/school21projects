#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_1 "s21_cat: %s: No such file or directory\n"
#define ERROR_2 "s21_cat: invalid option -- '%c'\n"

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int next_line_is_empty;
  int do_we_print;
  int previous_was_eol;
  int indexoffirstfile;
  int linecounter;
} options;

int checkflags(int argc, char** argv, options* config);
void printdata(FILE* file, options* config);
void flag_b(char symb, options* config);
void check_next_symbol(FILE* file, char ch, options* config);
void flag_n(options* config);
void flag_s(FILE* file, char symb, options* config);
void flag_t(char symb, options* config);
void flag_v(char symb, options* config);

#endif