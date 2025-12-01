#include "s21_grep.h"

int main(int argc, char **argv) {
  init();
  if (argc > 2) {
    if (!parser_opt(argc, argv)) openfile(argc, argv);
  } else {
    printf("use: [-eivclnhsf(file)o] and file name\n");
  }
  return 0;
}

void init() {
  opt.pattern_count = 0;
  opt.i = false;
  opt.v = false;
  opt.c = false;
  opt.l = false;
  opt.n = false;
  opt.h = false;
  opt.s = false;
  opt.o = false;
  for (int i = 0; i < 4096; i++) {
    opt.patterns[i] = NULL;
  }
}

void add_pattern(char *pattern) {
  opt.patterns[opt.pattern_count] = malloc(strlen(pattern) + 1);
  strcpy(opt.patterns[opt.pattern_count], pattern);
  opt.pattern_count++;
}

int read_patterns(char *filename) {
  bool flag = false;
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("s21_grep: can not find file or directory");
    flag = true;
  }

  char line[1024];
  while (fgets(line, sizeof(line), file)) {
    add_pattern(line);
  }

  fclose(file);
  return flag;
}

int parser_opt(int n, char **str) {
  bool flag = false;
  int option;
  while ((option = getopt_long(n, str, "e:f:ivclnsho", NULL, NULL)) != -1) {
    switch (option) {
      case 'e':
        add_pattern(optarg);
        break;
      case 'f':
        if (read_patterns(optarg)) flag = true;
        break;
      case 'i':
        opt.i = true;
        break;
      case 'v':
        opt.v = true;
        break;
      case 'c':
        opt.c = true;
        break;
      case 'l':
        opt.l = true;
        break;
      case 'n':
        opt.n = true;
        break;
      case 'h':
        opt.h = true;
        break;
      case 's':
        opt.s = true;
        break;
      case 'o':
        opt.o = true;
        break;
      default:
        flag = true;
    }
  }
  if (opt.pattern_count == 0 && optind < n) {
    add_pattern(str[optind]);
    optind++;
  }

  return flag;
}

void openfile(int n, char **str) {
  int file_count = n - optind;
  for (int i = optind; i < n; i++) {
    FILE *file = fopen(str[i], "r");
    if (file) {
      options(str, file_count, file, i);
    } else {
      if (!opt.s) printf("s21_grep: no such file or directory");
    }
  }
  for (int j = 0; j < opt.pattern_count; j++) {
    free(opt.patterns[j]);
  }
}

void options(char **str, int file_count, FILE *file, int i) {
  char line[1024];
  int match_count = 0;
  int line_number = 0;
  bool print_filename = file_count > 1 && !opt.h;
  while (fgets(line, sizeof(line), file)) {
    line_number++;
    bool match_found = false;
    match_found = options_under(line);
    if (opt.v) {
      match_found = !match_found;
    }
    if (match_found) {
      match_count++;
      if (!opt.c && !opt.l) {
        if (print_filename) {
          printf("%s:", str[i]);
        }
        if (opt.n) {
          printf("%d:", line_number);
        }
        printf("%s", line);
      }
    }
  }
  fclose(file);
  if (opt.c && print_filename) {
    printf("%s:%d\n", str[i], match_count);
  } else if (opt.c && !print_filename) {
    printf("%d\n", match_count);
  }
  if (opt.l && match_count > 0) {
    printf("%s\n", str[i]);
  }
}

int options_under(char *line) {
  bool match_found = false;
  for (int j = 0; j < opt.pattern_count; j++) {
    regex_t regex;
    int ret = regcomp(&regex, opt.patterns[j],
                      REG_EXTENDED | (opt.i ? REG_ICASE : 0));
    if (ret == 0) {
      ret = regexec(&regex, line, 0, NULL, 0);
      if (ret == 0) {
        match_found = true;
        if (opt.o) {
          regmatch_t pmatch[1];
          bool flago = true;
          while ((ret = regexec(&regex, line, 1, pmatch, 0)) == 0 && flago) {
            int start = pmatch[0].rm_so;
            int end = pmatch[0].rm_eo;
            int res = end - start;
            printf("%.*s\n", res, line + start);
            match_found = false;
            flago = false;
          }
        }
      }
    }
    regfree(&regex);
  }
  return match_found;
}