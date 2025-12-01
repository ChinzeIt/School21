#include "s21_cat.h"

int main(int argc, char **argv) {
  init();
  if (argc > 1) {
    if (!parse(argc, argv)) writing(argc, argv);
  } else {
    printf("use: s21_cat [-beEnstT] [FILE ...]\n");
  }
  return 0;
}

void init() {
  opt.b = false;
  opt.e = false;
  opt.v = false;
  opt.s = false;
  opt.t = false;
  opt.n = false;
}

int parse(int n, char **str) {
  bool flag = false;
  int cheking;
  int index = 0;
  const char *optshort = "+benstET";
  opterr = 0;
  while (true) {
    cheking = getopt_long(n, str, optshort, long_options, &index);
    if (cheking == -1) break;
    switch (cheking) {
      case 'b':
        opt.b = true;
        break;
      case 'e':
        opt.v = true;
        opt.e = true;
        break;
      case 'E':
        opt.e = true;
        break;
      case 's':
        opt.s = true;
        break;
      case 't':
        opt.v = true;
        opt.t = true;
        break;
      case 'T':
        opt.t = true;
        break;
      case 'n':
        opt.n = true;
        break;
      default:
        printf("s21_cat: not find option in line\n");
        printf("use: s21_cat [-beEnstT] [FILE ...]\n");
        flag = true;
    }
  }
  if (opt.b) opt.n = false;
  return flag;
}

void writing(int n, char **str) {
  int symbol = 0;
  size_t line_number = 1;
  size_t count_line = 0;
  bool new_line = true;
  for (int i = optind; i < n; i++) {
    FILE *file = fopen(str[i], "r");
    if (file == NULL) {
      printf("s21_cat: can not find file or directory\n");
      continue;
    }
    while ((symbol = fgetc(file)) != EOF) {
      if (opt.b && new_line && symbol != '\n') {
        printf("%6ld\t", line_number);
        line_number += 1;
        new_line = false;
      }
      if (opt.e && symbol == '\n') {
        printf("$");
      }
      if (opt.n && new_line) {
        printf("%6ld\t", line_number);
        line_number += 1;
        new_line = false;
      }
      if (opt.s) {
        if (symbol == '\n') {
          count_line += 1;
          if (count_line > 2) continue;
        } else {
          count_line = 0;
        }
      }
      if (opt.t && symbol == '\t') {
        printf("^");
        symbol = 'I';
      }
      if (opt.v && symbol != '\n' && symbol != '\t') {
        if (symbol >= 0 && symbol <= 31) {
          printf("^");
          symbol += 64;
        } else if (symbol == 127) {
          printf("^");
          symbol -= 64;
        }
      }
      if (symbol == '\n') {
        new_line = true;
      }
      printf("%c", symbol);
    }
    fclose(file);
  }
}