#include "s21_backend.h"

void initGameInfo(GameInfo_t* gi) {
  gi->field = create_matrix(HEIGHT, WIDTH);
  gi->next = create_matrix(4, 4);
  gi->score = 0;
  gi->high_score = 0;
  gi->level = 0;
  gi->speed = 0;
  gi->pause = 0;
}

void clearGameInfo(GameInfo_t* gi) {
  remove_matrix(gi->field, HEIGHT);
  remove_matrix(gi->next, 4);
}

void initGameStatus(GameStatus_t* gs) {
  gs->field = create_matrix(HEIGHT, WIDTH);
  gs->next = create_matrix(4, 4);
  gs->Figure = create_matrix(4, 4);
  gs->score = 0;
  gs->high_score = initHighScore();
  gs->level = 1;
  gs->speed = 2.0;
  gs->memorySpeed = 0.0;
  gs->pause = 0;
  gs->flag = true;
  gs->gameOver = false;
  gs->posX = 0;
  gs->posY = 0;

  gs->timerDown = time(NULL);
}

void clearGameStatus(GameStatus_t* gs) {
  remove_matrix(gs->Figure, 4);
  remove_matrix(gs->next, 4);
  remove_matrix(gs->field, HEIGHT);
}

int initHighScore() {
  FILE* file = fopen("game/scoreTetris.txt", "r");
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