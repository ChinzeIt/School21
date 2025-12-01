#include "s21_frontend.h"

void gameField(GameInfo_t* gi, int choose) {
  clear();

  borderWindow();

  if (choose == 0) {
    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        if (gi->field[y][x])
          mvprintw(y + 2, x + 3, "#");
        else
          mvprintw(y + 2, x + 3, ".");
      }
    }
  } else {
    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        if (gi->field[y][x] && gi->field[x][y] != 4)
          mvprintw(y + 2, x + 3, "#");
        if (gi->field[y][x] == 4) mvprintw(y + 2, x + 3, "@");
        if (!gi->field[y][x]) mvprintw(y + 2, x + 3, ".");
      }
    }
  }

  // Level and speed
  mvprintw(1, 12, "LEVEL & SPEED");
  mvprintw(2, 15, "%d      %d", gi->level, gi->speed);

  // Next figure
  mvprintw(4, 17, "NEXT");

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (gi->next[i][j]) mvprintw(6 + i, 17 + j, "#");
    }
  }

  // SCORE

  mvprintw(10, 17, "HIGH");
  mvprintw(11, 17, "SCORE");
  mvprintw(13, 18, "%d", gi->high_score);

  mvprintw(16, 17, "SCORE");
  mvprintw(18, 18, "%d", gi->score);

  // CONTROLLER
  mvprintw(20, 15, "Q - QUIT");

  if (gi->pause == 0)
    mvprintw(23, 8, "P - PAUSE");
  else {
    mvprintw(23, 7, "PAUSE ACTIV");
    mvprintw(24, 8, "S - START");
  }

  refresh();
}