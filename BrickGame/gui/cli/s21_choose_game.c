#include "s21_frontend.h"

void s21_chooseTetris() {
  initNcurses();
  int win = 0;
  GameInfo_t gi;
  UserAction_t act;
  initGameInfo(&gi);
  std::atomic<bool> running(true);

  std::thread gameThread([&]() {
    win = gameLoop(&gi, &act);
    running = false;
  });

  std::thread renderThread([&]() {
    while (running) {
      gameField(&gi, 0);
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  });

  gameThread.join();
  renderThread.join();
  nodelay(stdscr, FALSE);
  if (win == 2) {
    caputField();
    int ch = 0;
    while ((ch = getch()) != 'q') {
    }
  }
  clearGameInfo(&gi);
  endwin();
}

void s21_chooseSnake() {
  initNcurses();
  int win = 0;
  GameInfo_t gi;
  UserAction_t act;

  initGameInfo(&gi);
  std::atomic<bool> running(true);

  std::thread gameThread([&]() {
    s21::mainSnake snake;

    win = snake.snakeLoop(&gi, &act);
    running = false;
  });

  std::thread renderThread([&]() {
    while (running) {
      gameField(&gi, 1);
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  });

  gameThread.join();
  renderThread.join();
  nodelay(stdscr, FALSE);
  if (win == 1) {
    winField();
    int ch = 0;
    while ((ch = getch()) != 'q') {
    }
  } else if (win == 2) {
    caputField();
    int ch = 0;
    while ((ch = getch()) != 'q') {
    }
  }
  clearGameInfo(&gi);
  endwin();
}