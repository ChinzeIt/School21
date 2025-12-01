#ifndef S21_GREP
#define S21_GREP

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct opt {
  char *patterns[4096];
  int pattern_count;
  bool i, v, c, l, n, h, s, o;
} opt;

void init();
int parser_opt(int n, char **str);
int read_patterns(char *filename);
void add_pattern(char *pattern);
void openfile(int n, char **str);
void options(char **str, int file_count, FILE *file, int i);
int options_under(char *line);

#endif