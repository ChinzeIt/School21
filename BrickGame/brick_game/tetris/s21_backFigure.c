#include "s21_backend.h"

void addFigure(int **Figure) {
  int chooseFigure = (rand() % 7);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      Figure[i][j] = packageFigure(chooseFigure, i, j);
    }
  }
}

void copyNext(GameStatus_t *gs) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      gs->Figure[i][j] = gs->next[i][j];
    }
  }

  gs->posY = 0;
  gs->posX = rand() % (WIDTH - widthForStart(gs->Figure));
}

int widthForStart(int **Figure) {
  int max_width = 0;

  if (Figure[0][2] && Figure[0][3] && Figure[1][1] && Figure[1][2]) {
    max_width = 3;
  } else if (Figure[0][1] && Figure[0][2] && Figure[1][2] && Figure[1][3]) {
    max_width = 3;
  } else {
    for (int i = 0; i < 4; i++) {
      int row_width = 0;
      for (int j = 0; j < 4; j++) {
        if (Figure[i][j]) row_width++;
      }
      if (row_width > max_width) max_width = row_width;
    }
  }
  return max_width;
}

int packageFigure(int chooseFigure, int i, int j) {
  int shape[7][4][4] = {
      {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  return shape[chooseFigure][i][j];
}