#include <gtest/gtest.h>

#include "brick_game/snake/s21_backend.h"

TEST(SnakeTest, SnakeLoopBasicMovement) {
  s21::mainSnake snake;

  GameInfo_t gi;
  initGameInfo(&gi);

  UserAction_t act = Down;

  int win = snake.snakeLoop(&gi, &act);

  EXPECT_TRUE(win == 2);

  bool nonEmpty = false;
  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x)
      if (gi.field[y][x] != 0) nonEmpty = true;

  EXPECT_TRUE(nonEmpty);

  clearGameInfo(&gi);
}

TEST(SnakeTest, AppleSpawnOnOccupiedField) {
  GameStatus_t gs{};
  initGameStatus(&gs);
  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x) gs.field[y][x] = 1;
  gs.field[0][0] = 0;

  s21::appleSnake::spawnApple(&gs);

  EXPECT_EQ(gs.field[0][0], 4);

  clearGameStatus(&gs);
}

TEST(SnakeTest, EatAppleIncreasesScoreAndSnake) {
  GameStatus_t gs{};
  initGameStatus(&gs);

  std::deque<s21::Point> snake;
  snake.push_back({5, 5});
  gs.field[5][5] = 4;

  int oldScore = gs.score;
  size_t oldSize = snake.size();

  s21::appleSnake::eatApple(snake, &gs);

  EXPECT_EQ(gs.score, oldScore + 1);
  EXPECT_EQ(snake.size(), oldSize + 1);
  EXPECT_EQ(gs.field[5][5], 4);

  clearGameStatus(&gs);
}

TEST(SnakeStatTest, UpdateLevelIncreasesLevelAndReducesSpeed) {
  GameStatus_t gs{};
  gs.level = 1;
  gs.score = 10;
  gs.speed = 2.0;

  s21::statisticSnake::updateLevel(&gs);

  EXPECT_EQ(gs.level, 2);
  EXPECT_NEAR(gs.speed, 1.9, 1e-6);
}

TEST(SnakeStatTest, SaveScoreUpdatesHighScore) {
  GameStatus_t gs{};
  gs.high_score = 5;
  gs.score = 10;

  s21::statisticSnake::saveScore(&gs);

  EXPECT_EQ(gs.high_score, 10);
}

TEST(MoveSnakeTest, MoveRightWithinBounds) {
  std::deque<s21::Point> snake = {{WIDTH - 2, 5}};
  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TRIGHT;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_FALSE(gs.gameOver);
  EXPECT_EQ(snake.front().x, WIDTH - 1);
  EXPECT_EQ(snake.front().y, 5);
}

TEST(MoveSnakeTest, MoveRightOutOfBounds) {
  std::deque<s21::Point> snake = {{WIDTH - 1, 5}};
  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TRIGHT;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_TRUE(gs.gameOver);
}

TEST(MoveSnakeTest, MoveDownWithinBounds) {
  std::deque<s21::Point> snake = {{5, HEIGHT - 2}};
  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TDOWN;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_FALSE(gs.gameOver);
  EXPECT_EQ(snake.front().x, 5);
  EXPECT_EQ(snake.front().y, HEIGHT - 1);
}

TEST(MoveSnakeTest, MoveDownOutOfBounds) {
  std::deque<s21::Point> snake = {{5, HEIGHT - 1}};
  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TDOWN;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_TRUE(gs.gameOver);
}

TEST(MoveSnakeTest, MoveUpWithinBounds) {
  std::deque<s21::Point> snake = {{5, 1}};
  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TUP;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_FALSE(gs.gameOver);
  EXPECT_EQ(snake.front().x, 5);
  EXPECT_EQ(snake.front().y, 0);
}

TEST(MoveSnakeTest, MoveUpOutOfBounds) {
  std::deque<s21::Point> snake = {{5, 0}};
  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TUP;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_TRUE(gs.gameOver);
}

TEST(MoveSnakeTest, MoveLeftWithinBounds) {
  std::deque<s21::Point> snake = {{5, 5}};
  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TLEFT;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_FALSE(gs.gameOver);
  EXPECT_EQ(snake.front().x, 4);
  EXPECT_EQ(snake.front().y, 5);
}

TEST(MoveSnakeTest, MoveLeftOutOfBounds) {
  std::deque<s21::Point> snake = {{0, 5}};
  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TLEFT;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_TRUE(gs.gameOver);
}

TEST(MoveSnakeTest, CollisionWithSelf) {
  std::deque<s21::Point> snake = {{5, 5}, {5, 6}, {5, 7}};

  GameStatus_t gs{};
  s21::Turn turn = s21::Turn::TDOWN;

  s21::moveSnake::moveForward(snake, turn, &gs);

  EXPECT_TRUE(gs.gameOver);
}

TEST(SnakeButtonTest, StartUnpause) {
  GameStatus_t gs{};
  gs.pause = 1;
  gs.speed = PAUSE;
  gs.memorySpeed = 2;

  UserAction_t act = Start;
  s21::Turn turn = s21::Turn::TRIGHT;
  std::deque<s21::Point> snake = {{5, 5}};

  s21::moveSnake::snakeButton(&act, &gs, turn, snake);

  EXPECT_EQ(gs.pause, 0);
  EXPECT_EQ(gs.speed, gs.memorySpeed);
}

TEST(SnakeButtonTest, PauseButton) {
  GameStatus_t gs{};
  gs.speed = 2;

  UserAction_t act = Pause;
  s21::Turn turn = s21::Turn::TRIGHT;
  std::deque<s21::Point> snake = {{5, 5}};

  s21::moveSnake::snakeButton(&act, &gs, turn, snake);

  EXPECT_EQ(gs.pause, 1);
  EXPECT_EQ(gs.speed, PAUSE);
}

TEST(SnakeButtonTest, TerminateButton) {
  GameStatus_t gs{};
  gs.flag = true;

  UserAction_t act = Terminate;
  s21::Turn turn = s21::Turn::TRIGHT;
  std::deque<s21::Point> snake = {{5, 5}};

  s21::moveSnake::snakeButton(&act, &gs, turn, snake);

  EXPECT_FALSE(gs.flag);
}

TEST(SnakeButtonTest, LeftTurnAllDirections) {
  GameStatus_t gs{};
  UserAction_t act = Left;

  std::deque<s21::Point> snake = {{5, 5}};

  s21::Turn turn = s21::Turn::TUP;
  s21::moveSnake::snakeButton(&act, &gs, turn, snake);
  EXPECT_EQ(turn, s21::Turn::TLEFT);

  turn = s21::Turn::TRIGHT;
  s21::moveSnake::snakeButton(&act, &gs, turn, snake);
  EXPECT_EQ(turn, s21::Turn::TUP);

  turn = s21::Turn::TDOWN;
  s21::moveSnake::snakeButton(&act, &gs, turn, snake);
  EXPECT_EQ(turn, s21::Turn::TRIGHT);

  turn = s21::Turn::TLEFT;
  s21::moveSnake::snakeButton(&act, &gs, turn, snake);
  EXPECT_EQ(turn, s21::Turn::TDOWN);
}

TEST(SnakeButtonTest, RightTurnAllDirections) {
  GameStatus_t gs{};
  UserAction_t act = Right;

  std::deque<s21::Point> snake = {{5, 5}};

  s21::Turn turn = s21::Turn::TUP;
  s21::moveSnake::snakeButton(&act, &gs, turn, snake);
  EXPECT_EQ(turn, s21::Turn::TRIGHT);

  turn = s21::Turn::TRIGHT;
  s21::moveSnake::snakeButton(&act, &gs, turn, snake);
  EXPECT_EQ(turn, s21::Turn::TDOWN);

  turn = s21::Turn::TDOWN;
  s21::moveSnake::snakeButton(&act, &gs, turn, snake);
  EXPECT_EQ(turn, s21::Turn::TLEFT);

  turn = s21::Turn::TLEFT;
  s21::moveSnake::snakeButton(&act, &gs, turn, snake);
  EXPECT_EQ(turn, s21::Turn::TUP);
}

TEST(SnakeButtonTest, UpDoesNothing) {
  GameStatus_t gs{};
  UserAction_t act = Up;
  std::deque<s21::Point> snake = {{5, 5}};
  s21::Turn turn = s21::Turn::TRIGHT;

  s21::moveSnake::snakeButton(&act, &gs, turn, snake);

  EXPECT_EQ(turn, s21::Turn::TRIGHT);
  EXPECT_FALSE(gs.pause);
  EXPECT_FALSE(gs.flag);
}

TEST(SnakeButtonTest, ActionButtonMovesAndEatsApple) {
  GameStatus_t gs{};
  initGameStatus(&gs);
  UserAction_t act = Action;
  gs.field[5][5] = 4;
  gs.score = 0;

  std::deque<s21::Point> snake = {{5, 4}};
  s21::Turn turn = s21::Turn::TDOWN;

  s21::moveSnake::snakeButton(&act, &gs, turn, snake);

  EXPECT_EQ(snake.front().x, 5);
  EXPECT_EQ(snake.front().y, 5);

  EXPECT_EQ(gs.score, 1);

  EXPECT_NE(gs.timerDown, 0);
  clearGameStatus(&gs);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
