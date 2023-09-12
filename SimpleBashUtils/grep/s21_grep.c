#include "s21_grep.h"

int main(int argc, char** argv) {
  if (argc > 2) { 
    options config = {0};
    checkflags(argc, argv, &config);
    if (!config.f && !config.e) grabpattern(argv, &config);
    if (config.fileindex < argc - 1) config.multiple_files = 1;
    for (int x = config.fileindex; x < argc; x++) {
      FILE* file = fopen(argv[x], "r");
      if (file != NULL) {
        strcpy(config.filename, argv[x]);
        parse(file, &config);
        fclose(file);
        config.linecounter = 0;
        config.lflag_match = 0;
        config.is_EOF = 0;
        config.do_we_print_filename = 0;
      } else if (!config.s)
        fprintf(stderr, ERROR_1, argv[x]);
    }
  }
}

int checkflags(int argc, char** argv, options* config) {
  int opt, status = 1;
  optind = 1;
  const struct option long_options[] = {{NULL, 0, NULL, 0}};
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", long_options, NULL)) !=
         -1) {
    if (opt == 'v')
      config->v = 1;
    else if (opt == 'i')
      config->i = 1;
    else if (opt == 'n')
      config->n = 1;
    else if (opt == 'c')
      config->c = 1;
    else if (opt == 'l')
      config->l = 1;
    else if (opt == 'h')
      config->h = 1;
    else if (opt == 's')
      config->s = 1;
    else if (opt == 'o')
      config->o = 1;
    else if (opt == 'f') {
      config->f = 1;
      strcpy(config->pattern_file, optarg);
      grabpattern_from_file(config);
    } else if (opt == 'e') {
      config->e = 1;
      (int)strlen(config->pattern) == 0
          ? strcat(config->pattern, optarg)
          : (strcat(config->pattern, "|"), strcat(config->pattern, optarg));
    } else if (opt == '?') {
      if (!config->s) fprintf(stderr, ERROR_2, opt);
      status = 0;
      break;
    }
  }
  config->fileindex = optind;
  if(config->v) config->o = 0;
  return status;
}

void grabpattern(char** argv, options* config) {
  int x = config->fileindex;
  for (int i = 0; i < (int)strlen(argv[x]); i++) {
    config->pattern[i] = argv[x][i];
  }
  config->fileindex++;
}

void grabpattern_from_file(options* config) {
  FILE* pattern_file = fopen(config->pattern_file, "r");
  char temp[2048];
  if (pattern_file != NULL) {
    while (!config->is_EOF) {
      config->grabbing_multiple_patterns_EOL_deletion_flag = 1;
      grabstringfromfile(pattern_file, temp, config);
      (int)strlen(config->pattern) == 0
          ? strcat(config->pattern, temp)
          : (strcat(config->pattern, "|"), strcat(config->pattern, temp));
    }
    config->grabbing_multiple_patterns_EOL_deletion_flag = 0;
    fclose(pattern_file);
    config->is_EOF = 0;
  }
}

char* grabstringfromfile(FILE* file, char* currentline, options* config) {
  char symb;
  int line_len = 0;
  while (
      (symb = getc(file)) != EOF &&
      !(config->grabbing_multiple_patterns_EOL_deletion_flag && symb == '\n')) {
    currentline[line_len] = symb;
    (line_len)++;
    if (symb == '\n') break;
  }
  if (line_len != 0) {
    currentline[line_len] = '\0';
    (line_len)++;
  }
  if (config->grabbing_multiple_patterns_EOL_deletion_flag && symb == EOF)
    config->is_EOF = 1;
  return currentline;
}
void print_grep(char* string, options* config) {
  if (config->do_we_print_filename && config->do_we_print && !config->c &&
      !config->l)
    printf("%s:", config->filename);
  if (config->n && !config->c && !config->l)
    config->do_we_print ? printf("%d:", ++config->linecounter)
                        : config->linecounter++;
  if (config->do_we_print && !config->l && !config->o) printf("%s", string);
  if (config->do_we_print_filename && config->is_EOF &&
      (config->c || config->l)) {
    printf("%s:", config->filename);
  }
  if (config->c && config->is_EOF) {
    printf("%d\n", config->linecounter);
  }
  if (config->l && config->lflag_match && config->is_EOF) {
    printf("%s\n", config->filename);
  }
  if (string[(int)(strlen(string)) - 1] != '\n' && config->do_we_print)
    printf("\n");
}

void parse(FILE* file, options* config) {
  char currentstring[2048];
  do {
    grabstringfromfile(file, currentstring, config);
    regex_t reegex;
    regmatch_t reegm[1];
    char* endind = currentstring;
    int mask = 0;
    mask = config->i ? mask | REG_ICASE : mask | REG_EXTENDED;
    regcomp(&reegex, (config->pattern), mask);
    int compare_result = regexec(&reegex, endind, 1, reegm, 0);
    config->match_found = !compare_result ? 1 : 0;
    if (config->v) config->match_found = config->match_found ? 0 : 1;
    config->do_we_print = config->match_found ? 1 : 0;
    if (config->l) config->do_we_print = 0;
    if (config->multiple_files && !config->h &&
        (config->do_we_print || config->c))
      config->do_we_print_filename = 1;
    if (config->c && config->match_found) {
      if (!config->lflag_match) config->linecounter++;
      config->do_we_print = 0;
    }
    if (config->l && config->match_found) config->lflag_match = 1;
    print_grep(currentstring, config);
    if (config->o && config->do_we_print) {
      do {
        printf("%.*s\n", (int)(reegm[0].rm_eo - reegm[0].rm_so),
               endind + reegm[0].rm_so);
        endind = endind + (int)reegm[0].rm_eo;
      } while (regexec(&reegex, endind, 1, reegm, 0) == 0);
    }
    regfree(&reegex);
  } while (!feof(file));
  config->is_EOF = 1;
  config->do_we_print = 0;
  print_grep(currentstring, config);
}

// fix -v somehow (low priority)
// disable getopt errors
// f & e flags, high priority, multiple patterns work
// oop, print in separate function, make code more readable, clear garbage
// variables, use better naming

// EOL at EOF
// fix -o
