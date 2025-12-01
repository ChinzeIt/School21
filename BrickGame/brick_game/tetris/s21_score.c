#include "s21_backend.h"

void score(const int* count, GameStatus_t* gs) {
  switch (*count) {
    case 1:
      gs->score += 100;
      break;
    case 2:
      gs->score += 300;
      break;
    case 3:
      gs->score += 700;
      break;
    case 4:
      gs->score += 1500;
      break;
  }
}

void updateScore(GameStatus_t* gs) {
  if (gs->score > gs->high_score) {
    gs->high_score = gs->score;
    FILE* file = fopen("game/scoreTetris.txt", "w");
    if (file) fclose(file);
  }
}