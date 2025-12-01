#include "s21_current_state_button.h"

#include <ncurses.h>

void userInput(UserAction_t* action, bool hold) {
  if (hold) hold = false;
  int ch = 0;

  while ((ch = getch()) != ERR) {
    switch (ch) {
      case 's':
      case 'S':
        *action = Start;
        break;
      case 'p':
      case 'P':
        *action = Pause;
        break;
      case 'q':
      case 'Q':
        *action = Terminate;
        break;
      case KEY_LEFT:
        *action = Left;
        break;
      case KEY_RIGHT:
        *action = Right;
        break;
      case KEY_UP:
        *action = Up;
        break;
      case KEY_DOWN:
        *action = Down;
        break;
      case ' ':
        *action = Action;
        break;
    }
  }
}

GameInfo_t updateCurrentState(GameInfo_t* gi, GameStatus_t* gs) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      gi->field[y][x] = gs->field[y][x];
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      gi->next[i][j] = gs->next[i][j];
    }
  }
  gi->score = gs->score;
  gi->high_score = gs->high_score;
  gi->level = gs->level;
  if (gs->speed != PAUSE) gi->speed = gs->speed * 10;
  gi->pause = gs->pause;

  return *gi;
}