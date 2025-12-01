#pragma once

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../cli/s21_frontend.h"
namespace s21 {

enum class GameType { Tetris, Snake, Exit };

class View : public QWidget {
  Q_OBJECT

 private:
  QTimer* timer;
  GameInfo_t* gi_ = nullptr;
  UserAction_t* act_ = nullptr;
  GameType currentGame_ = GameType::Exit;

  void drawTetris(QPainter& painter) {
    if (!gi_) return;

    int cellSize = 32;
    painter.setPen(Qt::black);

    for (int y = 0; y < HEIGHT; ++y) {
      for (int x = 0; x < WIDTH; ++x) {
        QRect cell(32 + x * cellSize, 32 + y * cellSize, cellSize, cellSize);
        if (gi_->field[y][x]) painter.fillRect(cell, Qt::blue);
        painter.drawRect(cell);
      }
    }

    int infoX = 32 + WIDTH * cellSize + 50;
    int infoY = 50;

    painter.setFont(QFont("Times New Roman", 16));

    painter.drawText(infoX, infoY, QString("Level: %1").arg(gi_->level));
    infoY += 40;

    painter.drawText(infoX, infoY, QString("Speed: %1").arg(gi_->speed));
    infoY += 40;

    painter.drawText(infoX, infoY, "Next figure:");
    infoY += 30;

    int previewSize = 24;
    for (int y = 0; y < 4; ++y) {
      for (int x = 0; x < 4; ++x) {
        if (gi_->next[y][x]) {
          QRect cell(infoX + x * previewSize, infoY + y * previewSize,
                     previewSize, previewSize);
          painter.fillRect(cell, Qt::red);
          painter.drawRect(cell);
        }
      }
    }
    infoY += 120;

    painter.drawText(infoX, infoY,
                     QString("High Score: %1").arg(gi_->high_score));
    infoY += 40;

    painter.drawText(infoX, infoY, QString("Score: %1").arg(gi_->score));
    infoY += 60;

    if (gi_->pause) {
      painter.setPen(Qt::red);
      painter.drawText(infoX, infoY, "PAUSE ACTIVE");
      infoY += 40;
      painter.setPen(Qt::black);
      painter.drawText(infoX, infoY, "S - start");
    } else {
      painter.drawText(infoX, infoY, "P - pause");
    }

    int bottomY = height() - 30;
    painter.drawText(infoX, bottomY, "Q - quit from BrickGame");
  }

  void drawSnake(QPainter& painter) {
    if (!gi_) return;

    painter.setPen(Qt::black);
    painter.setFont(QFont("Times New Roman", 16));

    int cellSize = 32;
    for (int y = 0; y < HEIGHT; ++y) {
      for (int x = 0; x < WIDTH; ++x) {
        QRect cell(32 + x * cellSize, 32 + y * cellSize, cellSize, cellSize);
        if (gi_->field[y][x] && gi_->field[y][x] != 4 && gi_->field[y][x] != 2)
          painter.fillRect(cell, Qt::green);
        if (gi_->field[y][x] == 4) painter.fillRect(cell, Qt::red);
        if (gi_->field[y][x] == 2) painter.fillRect(cell, Qt::black);
        painter.drawRect(cell);
      }
    }

    int infoX = 32 + WIDTH * cellSize + 50;
    int infoY = 50;

    painter.drawText(infoX, infoY, QString("Level: %1").arg(gi_->level));
    infoY += 40;

    painter.drawText(infoX, infoY, QString("Speed: %1").arg(gi_->speed));
    infoY += 40;

    painter.drawText(infoX, infoY,
                     QString("High Score: %1").arg(gi_->high_score));
    infoY += 40;

    painter.drawText(infoX, infoY, QString("Score: %1").arg(gi_->score));
    infoY += 60;

    if (gi_->pause) {
      painter.setPen(Qt::red);
      painter.drawText(infoX, infoY, "PAUSE ACTIVE");
      infoY += 40;
      painter.setPen(Qt::black);
      painter.drawText(infoX, infoY, "S - start");
    } else {
      painter.drawText(infoX, infoY, "P - pause");
    }

    int bottomY = height() - 30;
    painter.drawText(infoX, bottomY, "Q - quit from BrickGame");
  }

 public:
  explicit View(QWidget* parent = nullptr) : QWidget(parent) {
    setFixedSize(800, 700);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&View::update));
    timer->start(50);
  }

  void settingView(GameInfo_t* gi, UserAction_t* act, GameType type) {
    act_ = act;
    gi_ = gi;
    currentGame_ = type;
  }

  void updateClock() { update(); }

 signals:
  void quitRequested();

 protected:
  void keyPressEvent(QKeyEvent* event) override {
    if (!act_) return;

    switch (event->key()) {
      case Qt::Key_Left:
        *act_ = Left;
        break;
      case Qt::Key_Right:
        *act_ = Right;
        break;
      case Qt::Key_Up:
        *act_ = Up;
        break;
      case Qt::Key_Down:
        *act_ = Down;
        break;
      case Qt::Key_Space:
        *act_ = Action;
        break;
      case Qt::Key_S:
        *act_ = Start;
        break;
      case Qt::Key_P:
        *act_ = Pause;
        break;
      case Qt::Key_Q:
        *act_ = Terminate;
        emit quitRequested();
        break;
    }
  }

  void paintEvent(QPaintEvent*) override {
    QPainter painter(this);
    if (currentGame_ == GameType::Tetris) {
      drawTetris(painter);
    } else if (currentGame_ == GameType::Snake) {
      drawSnake(painter);
    }
  }
};

}  // namespace s21
