#include "s21_frontend.h"

void borderWindow() {
  mvprintw(BORDERZ, BORDERZ, "+");
  mvprintw(BORDERH, BORDERZ, "+");
  mvprintw(BORDERZ, BORDERW, "+");
  mvprintw(BORDERH, BORDERW, "+");

  for (int x = 1; x < BORDERW; x++) {
    mvprintw(BORDERZ, x, "-");
    mvprintw(BORDERH, x, "-");
  }

  for (int y = 1; y < BORDERH; y++) {
    mvprintw(y, BORDERZ, "|");
    mvprintw(y, BORDERW, "|");
  }
}