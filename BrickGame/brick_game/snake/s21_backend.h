#pragma once

#include <chrono>
#include <deque>
#include <thread>

#include "../s21_current_state_button.h"

namespace s21 {
enum class Turn { TUP, TRIGHT, TDOWN, TLEFT };

struct Point {
  int x, y;
};

class moveSnake {
 public:
  static void moveForward(std::deque<Point>& snake, Turn& turn,
                          GameStatus_t* gs);
  static void snakeButton(UserAction_t* act, GameStatus_t* gs, Turn& turn,
                          std::deque<Point>& snake);
};

class appleSnake {
 public:
  static void spawnApple(GameStatus_t* gs);
  static void eatApple(std::deque<Point>& snake, GameStatus_t* gs);
  static void guarantApple(GameStatus_t* gs);
};

class statisticSnake {
 public:
  static void updateLevel(GameStatus_t* gs);
  static int initHighScoreSnake();
  static void saveScore(GameStatus_t* gs);
};

class mainSnake {
 protected:
  GameStatus_t* gs_ = new GameStatus_t();
  Turn turn_ = Turn::TRIGHT;

  std::deque<Point> snake_;

  void updateField();

 public:
  mainSnake();
  int snakeLoop(GameInfo_t* gi, UserAction_t* act);
};

}  // namespace s21