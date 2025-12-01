#include "s21_backend.h"

namespace s21 {
void statisticSnake::updateLevel(GameStatus_t* gs) {
  if (gs->level < 10 && gs->score - 5 * gs->level >= 0) {
    gs->speed -= 0.1;
    gs->level++;
  }
}

int statisticSnake::initHighScoreSnake() {
  FILE* file = fopen("game/scoreSnake.txt", "r");
  char line[256];
  int high_score = 0;

  if (file) {
    if (fgets(line, sizeof(line), file)) {
      high_score = atoi(line);
    }
    fclose(file);
  }

  return high_score;
}

void statisticSnake::saveScore(GameStatus_t* gs) {
  if (gs->score > gs->high_score) {
    gs->high_score = gs->score;
    FILE* file = fopen("game/scoreSnake.txt", "w");
    if (file) {
      fprintf(file, "%d", gs->high_score);
      fclose(file);
    }
  }
}
}  // namespace s21