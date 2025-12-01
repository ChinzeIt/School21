#include "s21_backend.h"

namespace s21 {
void appleSnake::spawnApple(GameStatus_t* gs) {
  int x = rand() % WIDTH;
  int y = rand() % HEIGHT;

  if (gs->field[y][x] != 0) {
    spawnApple(gs);
    return;
  }

  gs->field[y][x] = 4;
}

void appleSnake::eatApple(std::deque<Point>& snake, GameStatus_t* gs) {
  Point head = snake.front();

  if (gs->field[head.y][head.x] == 4) {
    gs->score++;

    Point tail = snake.back();
    snake.push_back(tail);

    spawnApple(gs);
  }
}

void appleSnake::guarantApple(GameStatus_t* gs) {
  bool no = true;

  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x)
      if (gs->field[y][x] == 4) no = false;

  if (no) spawnApple(gs);
}
}  // namespace s21