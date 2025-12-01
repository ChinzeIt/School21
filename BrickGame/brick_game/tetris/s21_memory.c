#include "s21_backend.h"

int **create_matrix(int rows, int columns) {
  bool flag = true;
  int **result = {0};
  if (rows <= 0 || columns <= 0) {
    flag = false;
  } else {
    result = (int **)calloc(rows, sizeof(int *));
    if (!result) flag = false;

    int count = 0;
    for (int i = 0; i < rows && flag == true; i++) {
      count++;
      result[i] = (int *)calloc(columns, sizeof(int));
      if (!result[i]) flag = false;
    }

    if (!flag) {
      while (count-- >= 0) free(result[count]);
      free(result);
    }
  }

  return result;
}

void remove_matrix(int **matrix, int rows) {
  if (matrix != NULL) {
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
  }
}