#include "s21_frontend.h"

int main(int argc, char* argv[]) {
  if (argc > 1 && argv[1][0] == '0') {
    s21_chooseTetris();
  } else if (argc > 1 && argv[1][0] == '1') {
    s21_chooseSnake();
  } else {
    printf("Number not game");
  }
  return 0;
}