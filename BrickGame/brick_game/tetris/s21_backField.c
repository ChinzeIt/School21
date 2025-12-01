#include "s21_backend.h"

void makeField(GameStatus_t* gs) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (gs->Figure[i][j]) {
        gs->field[gs->posY + i][gs->posX + j] = 1;
      }
    }
  }
}

void clearFigure(GameStatus_t* gs) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (gs->Figure[i][j]) {
        gs->field[gs->posY + i][gs->posX + j] = 0;
      }
    }
  }
}