#include "s21_backend.h"

void chekLevel(GameStatus_t* gs) {
  if (gs->level < 10 && gs->score - 600 * gs->level >= 0) {
    gs->speed -= 0.1;
    gs->level++;
  }
}