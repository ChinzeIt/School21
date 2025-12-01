#include "s21_backend.h"

void executionButton(GameStatus_t* gs, UserAction_t* act) {
  if (gs->pause && *act != Start && *act != Terminate) *act = Pause;

  switch (*act) {
    case Start:
      gs->pause = 0;
      if (gs->speed == PAUSE) gs->speed = gs->memorySpeed;
      if (gs->level < 10 && gs->score - 600 * gs->level >= 0)
        gs->speed = 2 - gs->level % 10;
      gs->memorySpeed = gs->speed;
      break;
    case Pause:
      gs->pause = 1;
      gs->speed = PAUSE;
      break;
    case Terminate:
      gs->flag = false;
      return;
    case Left:
      if (!gs->pause && canMove(gs, act)) (gs->posX)--;
      *act = (UserAction_t)0;
      break;
    case Right:
      if (!gs->pause && canMove(gs, act)) (gs->posX)++;
      *act = (UserAction_t)0;
      break;
    case Up:
      break;
    case Down:
      if (!gs->pause && canMove(gs, act)) {
        (gs->posY)++;
        gs->timerDown = time(NULL);
      }
      *act = (UserAction_t)0;
      break;
    case Action:
      if (canRotate(gs, act) && checkSquare(gs->Figure))
        rotateFigure(gs->Figure);
      *act = (UserAction_t)0;
      break;
  }
}

bool canMove(const GameStatus_t* gs, const UserAction_t* act) {
  bool flag = true;
  int dx = 0, dy = 0;

  switch (*act) {
    case Left:
      dx = -1;
      break;
    case Right:
      dx = 1;
      break;
    case Down:
      dy = 1;
      break;
    default:
      break;
  }

  for (int i = 0; i < 4 && flag; i++) {
    for (int j = 0; j < 4 && flag; j++) {
      if (gs->Figure[i][j]) {
        int newX = gs->posX + j + dx;
        int newY = gs->posY + i + dy;

        if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT ||
            gs->field[newY][newX])
          flag = false;
      }
    }
  }

  return flag;
}

bool canRotate(const GameStatus_t* gs, const UserAction_t* act) {
  int temp[4][4] = {0};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp[i][j] = gs->Figure[3 - j][i];
    }
  }

  GameStatus_t tempGS = *gs;
  int* rotatedFigure[4];
  for (int i = 0; i < 4; i++) {
    rotatedFigure[i] = temp[i];
  }
  tempGS.Figure = rotatedFigure;

  return canMove(&tempGS, act);
}

bool checkSquare(int** Figure) {
  bool flag = true;
  int count = 0;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (Figure[i][j]) count++;
    }
  }

  if (count == 4) flag = false;

  return flag;
}

void rotateFigure(int** Figure) {
  int temp[4][4] = {0};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp[i][j] = Figure[3 - j][i];
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      Figure[i][j] = temp[i][j];
    }
  }
}