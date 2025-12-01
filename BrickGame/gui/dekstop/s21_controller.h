#pragma once

#include <QObject>
#include <QThread>

#include "../../brick_game/snake/s21_backend.h"
#include "../../brick_game/tetris/s21_backend.h"
#include "s21_view.h"

namespace s21 {

class Controller : public QObject {
  Q_OBJECT

 private:
  mainSnake* snake_;
  View* view_;
  QThread* gameThread_ = nullptr;

 public:
  explicit Controller(View* view, QObject* parent = nullptr)
      : QObject(parent), snake_(nullptr), view_(view) {
    connect(view_, &View::quitRequested, this, &Controller::handleQuit);
  }
  ~Controller() { delete snake_; }

  void gameChoose(GameType type) {
    if (type == GameType::Tetris) {
      GameInfo_t* gi = new GameInfo_t();
      UserAction_t* act = new UserAction_t();
      initGameInfo(gi);

      view_->settingView(gi, act, type);
      view_->updateClock();

      if (!gameThread_) {
        gameThread_ = QThread::create([this, gi, act]() {
          gameLoop(gi, act);

          clearGameInfo(gi);

          emit gameOver();
        });

        connect(gameThread_, &QThread::finished, gameThread_,
                &QObject::deleteLater);
        connect(this, &Controller::gameOver, this, &Controller::handleOverGame);
        gameThread_->start();
      }
    } else if (type == GameType::Snake) {
      if (!snake_) snake_ = new mainSnake();

      GameInfo_t* gi = new GameInfo_t();
      UserAction_t* act = new UserAction_t();
      initGameInfo(gi);

      view_->settingView(gi, act, type);
      view_->updateClock();

      if (!gameThread_) {
        gameThread_ = QThread::create([this, gi, act]() {
          int win = snake_->snakeLoop(gi, act);

          clearGameInfo(gi);

          if (win == 1)
            emit gameWin();
          else if (win == 2)
            emit gameOver();
        });

        connect(gameThread_, &QThread::finished, gameThread_,
                &QObject::deleteLater);
        connect(this, &Controller::gameOver, this, &Controller::handleOverGame);
        connect(this, &Controller::gameWin, this, &Controller::handleOverGame);
        gameThread_->start();
      }
    }
  }

 signals:
  void gameWin();
  void gameOver();
  void quitGame();

 private slots:
  void handleOverGame() {
    if (gameThread_) {
      gameThread_->quit();
      gameThread_->wait();
      gameThread_ = nullptr;
    }
  }
  void handleQuit() {
    if (gameThread_) {
      gameThread_->quit();
      gameThread_->wait();
      gameThread_ = nullptr;
    }

    emit quitGame();
  }
};

}  // namespace s21
