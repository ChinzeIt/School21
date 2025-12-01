#include "s21_backend.h"

namespace s21 {
void moveSnake::moveForward(std::deque<Point>& snake, Turn& turn,
                            GameStatus_t* gs) {
  Point head = snake.front();
  Point newHead = head;

  switch (turn) {
    case Turn::TUP:
      if (newHead.y - 1 < 0) {
        gs->gameOver = true;
        return;
      }
      newHead.y -= 1;
      break;
    case Turn::TRIGHT:
      if (newHead.x + 1 >= WIDTH) {
        gs->gameOver = true;
        return;
      }
      newHead.x += 1;
      break;
    case Turn::TDOWN:
      if (newHead.y + 1 >= HEIGHT) {
        gs->gameOver = true;
        return;
      }
      newHead.y += 1;
      break;
    case Turn::TLEFT:
      if (newHead.x - 1 < 0) {
        gs->gameOver = true;
        return;
      }
      newHead.x -= 1;
      break;
  }

  for (const auto& segment : snake) {
    if (segment.x == newHead.x && segment.y == newHead.y) {
      gs->gameOver = true;
      return;
    }
  }

  snake.push_front(newHead);
  snake.pop_back();
}

void moveSnake::snakeButton(UserAction_t* act, GameStatus_t* gs, Turn& turn,
                            std::deque<Point>& snake) {
  if (gs->pause && *act != Start && *act != Terminate) *act = Pause;

  switch (*act) {
    case Start:
      gs->pause = 0;
      if (gs->speed == PAUSE) gs->speed = gs->memorySpeed;
      if (gs->level < 10 && gs->score - 5 * gs->level >= 0)
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
      switch (turn) {
        case Turn::TUP:
          turn = Turn::TLEFT;
          moveForward(snake, turn, gs);
          gs->timerDown = time(NULL);
          break;
        case Turn::TRIGHT:
          turn = Turn::TUP;
          moveForward(snake, turn, gs);
          gs->timerDown = time(NULL);
          break;
        case Turn::TDOWN:
          turn = Turn::TRIGHT;
          moveForward(snake, turn, gs);
          gs->timerDown = time(NULL);
          break;
        case Turn::TLEFT:
          turn = Turn::TDOWN;
          moveForward(snake, turn, gs);
          gs->timerDown = time(NULL);
          break;
      }
      break;
    case Right:
      switch (turn) {
        case Turn::TUP:
          turn = Turn::TRIGHT;
          moveForward(snake, turn, gs);
          gs->timerDown = time(NULL);
          break;
        case Turn::TRIGHT:
          turn = Turn::TDOWN;
          moveForward(snake, turn, gs);
          gs->timerDown = time(NULL);
          break;
        case Turn::TDOWN:
          turn = Turn::TLEFT;
          moveForward(snake, turn, gs);
          gs->timerDown = time(NULL);
          break;
        case Turn::TLEFT:
          turn = Turn::TUP;
          moveForward(snake, turn, gs);
          gs->timerDown = time(NULL);
          break;
      }
      break;
    case Up:
      break;
    case Down:
      break;
    case Action:
      moveForward(snake, turn, gs);
      appleSnake::eatApple(snake, gs);
      gs->timerDown = time(NULL);
      break;
  }
}
}  // namespace s21