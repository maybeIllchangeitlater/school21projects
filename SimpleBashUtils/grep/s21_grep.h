#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERROR_1 "s21_grep: %s: File not found\n"
#define ERROR_2 "s21_grep: Invalid flag -- '%c'\n"

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int fileindex;
  int is_EOF;
  int do_we_print;
  int do_we_print_filename;
  int grabbing_multiple_patterns_EOL_deletion_flag;
  int lflag_match;
  char pattern_file[2048];
  char filename[2048];
  int linecounter;
  int match_found;
  int multiple_files;
  char pattern[2048];
} options;

int checkflags(int argc, char** argv, options* config);
void grabpattern(char** argv, options* config);
void grabpattern_from_file(options* config);
void parse(FILE* file, options* config);
void print_grep(char* string, options* config);
char* grabstringfromfile(FILE* file, char* currentline, options* config);

#endif