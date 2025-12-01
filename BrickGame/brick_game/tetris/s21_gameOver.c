#include "s21_backend.h"

bool canAddNewFigure(const GameStatus_t* gs) {
  bool flag = false;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (gs->Figure[i][j]) {
        int x = gs->posX + j;
        int y = gs->posY + i;
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || gs->field[y][x])
          flag = true;
      }
    }
  }

  return flag;
}