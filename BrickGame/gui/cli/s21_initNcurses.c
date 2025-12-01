#include "s21_frontend.h"

void initNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  srand(time(NULL));
  mousemask(0, NULL);
}