#include "s21_backend.h"

void clearLines(GameStatus_t* gs) {
  int count = 0;
  for (int i = 0; i < HEIGHT; i++) {
    bool full = true;
    for (int j = 0; j < WIDTH && full; j++) {
      if (!gs->field[i][j]) full = false;
    }

    if (full) {
      updateLine(gs->field, i);
      count++;
    }
  }
  score(&count, gs);
}

void updateLine(int** Field, int i) {
  for (int z = i; z > 0; z--) {
    for (int v = 0; v < WIDTH; v++) {
      Field[z][v] = Field[z - 1][v];
    }
  }

  for (int v = 0; v < WIDTH; v++) {
    Field[0][v] = 0;
  }
}