#include "s21_frontend.h"

void caputField() {
  clear();

  borderWindow();
  mvprintw(12, 8, "GAME OVER");

  refresh();
}

void winField() {
  clear();

  borderWindow();
  mvprintw(12, 8, "GAME WIN");

  refresh();
}