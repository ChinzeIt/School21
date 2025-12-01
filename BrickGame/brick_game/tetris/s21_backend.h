#ifndef BACkEND_TETRIS_H
#define BACkEND_TETRIS_H

#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20
#define DELAY 7500
#define PAUSE 7500000

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  bool flag;
  int** field;
  int** Figure;
  int** next;
  int score;
  int high_score;
  int level;
  double speed;
  double memorySpeed;
  int pause;
  int posX;
  int posY;
  time_t timerDown;
  bool gameOver;
} GameStatus_t;

#include "../s21_current_state_button.h"

// Init and clear
void initGameInfo(GameInfo_t* gi);
void clearGameInfo(GameInfo_t* gi);
void initGameStatus(GameStatus_t* gs);
void clearGameStatus(GameStatus_t* gs);
int initHighScore();

// Memory
int** create_matrix(int rows, int columns);
void remove_matrix(int** matrix, int rows);

// Loop
int gameLoop(GameInfo_t* gi, UserAction_t* act);
void loop(GameStatus_t* gs, UserAction_t* act);

// Make backend field
void makeField(GameStatus_t* gs);
void clearFigure(GameStatus_t* gs);

// Figure
void addFigure(int** Figure);
void copyNext(GameStatus_t* gs);
int widthForStart(int** Figure);
int packageFigure(int chooseFigure, int i, int j);

// Move
void executionButton(GameStatus_t* gs, UserAction_t* act);
bool canMove(const GameStatus_t* gs, const UserAction_t* act);
bool canRotate(const GameStatus_t* gs, const UserAction_t* act);
bool checkSquare(int** Figure);
void rotateFigure(int** Figure);

// Lines
void clearLines(GameStatus_t* gs);
void updateLine(int** Field, int i);

// Calc score
void score(const int* count, GameStatus_t* gs);
void updateScore(GameStatus_t* gs);

// Level
void chekLevel(GameStatus_t* gs);

// Game Over
bool canAddNewFigure(const GameStatus_t* gs);

#ifdef __cplusplus
}
#endif

#endif