#ifndef FRONTEND_H
#define FRONTEND_H

#include <atomic>
#include <thread>

#include "../../brick_game/snake/s21_backend.h"
#include "../../brick_game/tetris/s21_backend.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <ncurses.h>
#include <stdio.h>

#include "../../brick_game/s21_current_state_button.h"

#define BORDERH 25
#define BORDERW 25
#define BORDERZ 0

void initNcurses();
void gameField(GameInfo_t* gi, int choose);
void borderWindow();
void caputField();
void winField();

#ifdef __cplusplus
}
#endif

void s21_chooseTetris();
void s21_chooseSnake();

#endif