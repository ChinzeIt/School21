#pragma once

#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

#include "s21_controller.h"
#include "s21_view.h"

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  Controller* controll;
  QWidget* menuWidget;
  QWidget* gameOverWidget;
  QWidget* gameWinWidget;
  View* gameView;
  QStackedWidget* stack;

 public:
  MainWindow() {
    setFixedSize(800, 700);
    QFont font("Times New Roman", 32, QFont::Bold);
    gameView = new View(this);
    controll = new Controller(gameView, this);
    menuWidget = new QWidget(this);
    menuWidget->setFixedSize(800, 700);

    gameOverWidget = new QWidget(this);
    QLabel* goLabel = new QLabel("GAME OVER", gameOverWidget);
    goLabel->setGeometry(200, 200, 400, 100);
    goLabel->setAlignment(Qt::AlignCenter);
    goLabel->setFont(font);

    gameWinWidget = new QWidget(this);
    QLabel* gwinLabel = new QLabel("GAME WIN", gameWinWidget);
    gwinLabel->setGeometry(200, 200, 400, 100);
    gwinLabel->setAlignment(Qt::AlignCenter);
    gwinLabel->setFont(font);

    QPushButton* tetrisButton = new QPushButton("Tetris", menuWidget);
    tetrisButton->setGeometry(200, 170, 400, 100);

    QPushButton* snakeButton = new QPushButton("Snake", menuWidget);
    snakeButton->setGeometry(200, 290, 400, 100);

    QPushButton* exitButton = new QPushButton("Exit", menuWidget);
    exitButton->setGeometry(200, 410, 400, 100);

    stack = new QStackedWidget(this);
    stack->setFixedSize(800, 700);
    stack->addWidget(menuWidget);
    stack->addWidget(gameView);
    stack->addWidget(gameOverWidget);
    stack->addWidget(gameWinWidget);
    stack->setCurrentIndex(0);

    connect(tetrisButton, &QPushButton::clicked, this,
            &MainWindow::startTetris);
    connect(snakeButton, &QPushButton::clicked, this, &MainWindow::startSnake);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitGame);
    connect(controll, &Controller::quitGame, this, &MainWindow::exitGame);
    connect(controll, &Controller::gameWin, this, &MainWindow::showGameWin);
    connect(controll, &Controller::gameOver, this, &MainWindow::showGameOver);
  }

 private slots:
  void startTetris() {
    stack->setCurrentIndex(1);
    controll->gameChoose(GameType::Tetris);
  }

  void startSnake() {
    stack->setCurrentIndex(1);
    controll->gameChoose(GameType::Snake);
  }

  void exitGame() { QApplication::quit(); }

  void showGameOver() { stack->setCurrentIndex(2); }

  void showGameWin() { stack->setCurrentIndex(3); }
};

}  // namespace s21
