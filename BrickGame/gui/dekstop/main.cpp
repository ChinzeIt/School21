#include "s21_mainWindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::MainWindow w;
  w.show();

  return app.exec();
}