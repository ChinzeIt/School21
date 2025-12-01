#ifndef CURRENT_STATE_BUTTON_H
#define CURRENT_STATE_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tetris/s21_backend.h"

// Main userinput and field
GameInfo_t updateCurrentState(GameInfo_t* gi, GameStatus_t* gs);
void userInput(UserAction_t* action, bool hold);

#ifdef __cplusplus
}
#endif

#endif