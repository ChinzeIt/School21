#include "s21_backend.h"

int gameLoop(GameInfo_t* gi, UserAction_t* act) {
  GameStatus_t gs = {};
  initGameStatus(&gs);
  int win = 0;

  addFigure(gs.next);
  copyNext(&gs);
  addFigure(gs.next);

  while (gs.flag && !gs.gameOver) {
    loop(&gs, act);
    updateCurrentState(gi, &gs);
    usleep(DELAY);
  }

  if (gs.gameOver) win = 2;

  clearGameStatus(&gs);

  return win;
}

void loop(GameStatus_t* gs, UserAction_t* act) {
  updateScore(gs);
  chekLevel(gs);
  userInput(act, true);
  clearFigure(gs);
  executionButton(gs, act);
  time_t currentTime = time(NULL);
  if (difftime(currentTime, gs->timerDown) >= gs->speed) {
    UserAction_t tmp = Down;
    if (canMove(gs, &tmp)) {
      gs->posY++;
    } else {
      makeField(gs);
      clearLines(gs);
      copyNext(gs);
      addFigure(gs->next);
      gs->gameOver = canAddNewFigure(gs);
    }
    gs->timerDown = currentTime;
  }
  makeField(gs);
}