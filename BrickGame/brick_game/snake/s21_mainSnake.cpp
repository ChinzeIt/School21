#include "s21_backend.h"

namespace s21 {
mainSnake::mainSnake() {
  snake_.clear();
  int startX = WIDTH / 2;
  int startY = HEIGHT / 2;
  for (int i = 0; i < 4; i++) snake_.push_back({startX - i, startY});
  initGameStatus(gs_);
  gs_->timerDown = time(NULL);
  gs_->high_score = statisticSnake::initHighScoreSnake();
}

int mainSnake::snakeLoop(GameInfo_t* gi, UserAction_t* act) {
  int win = 0;
  updateField();
  appleSnake::spawnApple(gs_);

  while (gs_->flag && !gs_->gameOver) {
    statisticSnake::saveScore(gs_);

    if (gs_->score == 200) {
      win = 1;
      break;
    }

    userInput(act, true);
    moveSnake::snakeButton(act, gs_, turn_, snake_);

    if (gs_->gameOver) {
      win = 2;
      break;
    }

    if (*act == Left || *act == Right || *act == Action) {
      *act = Down;
    }

    time_t currentTime = time(NULL);
    if (!gs_->pause && difftime(currentTime, gs_->timerDown) >= gs_->speed) {
      moveSnake::moveForward(snake_, turn_, gs_);
      appleSnake::eatApple(snake_, gs_);
      gs_->timerDown = currentTime;
    }

    appleSnake::guarantApple(gs_);

    statisticSnake::updateLevel(gs_);

    if (gs_->gameOver) {
      win = 2;
      break;
    }

    updateField();
    updateCurrentState(gi, gs_);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  clearGameStatus(gs_);

  return win;
}

void mainSnake::updateField() {
  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x)
      if (gs_->field[y][x] != 4) gs_->field[y][x] = 0;

  for (size_t i = 0; i < snake_.size(); i++) {
    const Point& p = snake_[i];

    if (p.y < 0 || p.y >= HEIGHT || p.x < 0 || p.x >= WIDTH) continue;

    int val = (i == 0 ? 2 : (i + 1 == snake_.size() ? 3 : 1));
    gs_->field[p.y][p.x] = val;
  }
}
}  // namespace s21