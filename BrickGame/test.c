#include <check.h>

#include "brick_game/tetris/s21_backend.h"

START_TEST(test_score_logic) {
  GameStatus_t gs = {};
  int c = 1;
  score(&c, &gs);
  ck_assert_int_eq(gs.score, 100);
  c = 2;
  score(&c, &gs);
  ck_assert_int_eq(gs.score, 400);
  c = 3;
  score(&c, &gs);
  ck_assert_int_eq(gs.score, 1100);
  c = 4;
  score(&c, &gs);
  ck_assert_int_eq(gs.score, 2600);
}
END_TEST

START_TEST(test_updateScore_logic) {
  GameStatus_t gs = {};
  gs.score = 800;
  gs.high_score = 500;
  updateScore(&gs);
  ck_assert_int_eq(gs.high_score, 800);

  gs.score = 200;
  updateScore(&gs);
  ck_assert_int_eq(gs.high_score, 800);
}
END_TEST

START_TEST(test_chekLevel_logic) {
  GameStatus_t gs = {};
  gs.score = 600;
  gs.level = 1;
  gs.speed = 1.0;
  chekLevel(&gs);
  ck_assert_int_eq(gs.level, 2);
  ck_assert_double_eq_tol(gs.speed, 0.9, 0.01);
}
END_TEST

START_TEST(test_makeField_and_clearFigure_logic) {
  GameStatus_t gs = {};
  gs.field = create_matrix(HEIGHT, WIDTH);
  gs.Figure = create_matrix(4, 4);
  gs.posX = 3;
  gs.posY = 2;

  gs.Figure[1][1] = 1;
  gs.Figure[2][2] = 1;

  makeField(&gs);

  ck_assert_int_eq(gs.field[3][4], 1);
  ck_assert_int_eq(gs.field[4][5], 1);

  clearFigure(&gs);

  ck_assert_int_eq(gs.field[3][4], 0);
  ck_assert_int_eq(gs.field[4][5], 0);

  remove_matrix(gs.field, HEIGHT);
  remove_matrix(gs.Figure, 4);
}
END_TEST

START_TEST(test_canMove_logic) {
  GameStatus_t gs = {};
  UserAction_t act = Left;

  gs.field = create_matrix(HEIGHT, WIDTH);
  gs.Figure = create_matrix(4, 4);
  gs.posX = 5;
  gs.posY = 5;

  gs.Figure[0][0] = 1;

  ck_assert_int_eq(canMove(&gs, &act), true);

  gs.field[5][4] = 1;
  ck_assert_int_eq(canMove(&gs, &act), false);

  remove_matrix(gs.field, HEIGHT);
  remove_matrix(gs.Figure, 4);
}
END_TEST

START_TEST(test_canRotate_logic) {
  GameStatus_t gs = {};
  UserAction_t act = Action;

  gs.field = create_matrix(HEIGHT, WIDTH);
  gs.Figure = create_matrix(4, 4);
  gs.posX = 4;
  gs.posY = 0;

  gs.Figure[0][1] = 1;
  gs.Figure[1][1] = 1;
  gs.Figure[2][1] = 1;
  gs.Figure[3][1] = 1;

  ck_assert_int_eq(canRotate(&gs, &act), true);

  gs.field[1][4] = 1;
  ck_assert_int_eq(canRotate(&gs, &act), false);

  remove_matrix(gs.field, HEIGHT);
  remove_matrix(gs.Figure, 4);
}
END_TEST

START_TEST(test_checkSquare_logic) {
  int** fig = (int**)malloc(4 * sizeof(int*));
  for (int i = 0; i < 4; ++i) fig[i] = (int*)calloc(4, sizeof(int));
  fig[0][0] = fig[0][1] = fig[1][0] = fig[1][1] = 1;

  ck_assert(!checkSquare(fig));

  fig[1][1] = 0;
  ck_assert(checkSquare(fig));

  for (int i = 0; i < 4; ++i) free(fig[i]);
  free(fig);
}
END_TEST

START_TEST(test_clearLines_logic) {
  GameStatus_t gs = {};
  gs.field = create_matrix(HEIGHT, WIDTH);
  gs.Figure = create_matrix(4, 4);

  for (int j = 0; j < WIDTH; j++) {
    gs.field[5][j] = 1;
  }

  gs.score = 0;

  clearLines(&gs);

  ck_assert_int_eq(gs.score, 100);

  for (int j = 0; j < WIDTH; j++) {
    ck_assert_int_eq(gs.field[5][j], 0);
  }

  remove_matrix(gs.field, HEIGHT);
  remove_matrix(gs.Figure, 4);
}
END_TEST

START_TEST(test_canAddNewFigure_logic) {
  GameStatus_t gs = {};
  gs.field = create_matrix(HEIGHT, WIDTH);
  gs.Figure = create_matrix(4, 4);

  gs.posX = 5;
  gs.posY = 0;

  gs.Figure[0][0] = 1;
  ck_assert_int_eq(canAddNewFigure(&gs), false);

  gs.field[0][5] = 1;
  ck_assert_int_eq(canAddNewFigure(&gs), true);

  remove_matrix(gs.field, HEIGHT);
  remove_matrix(gs.Figure, 4);
}
END_TEST

START_TEST(test_rotateFigure_logic) {
  int** fig = (int**)malloc(4 * sizeof(int*));
  for (int i = 0; i < 4; ++i) fig[i] = (int*)calloc(4, sizeof(int));

  fig[0][1] = 1;
  rotateFigure(fig);
  ck_assert_int_eq(fig[1][3], 1);

  for (int i = 0; i < 4; ++i) free(fig[i]);
  free(fig);
}
END_TEST

START_TEST(test_create_matrix_valid) {
  int rows = 4, cols = 4;
  int** matrix = create_matrix(rows, cols);
  ck_assert_ptr_nonnull(matrix);
  for (int i = 0; i < rows; ++i) ck_assert_ptr_nonnull(matrix[i]);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j) ck_assert_int_eq(matrix[i][j], 0);

  remove_matrix(matrix, rows);
}
END_TEST

START_TEST(test_create_matrix_invalid_zero_rows) {
  int** matrix = create_matrix(0, 5);
  ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(test_create_matrix_invalid_zero_cols) {
  int** matrix = create_matrix(5, 0);
  ck_assert_ptr_null(matrix);
}
END_TEST

START_TEST(test_remove_matrix_null) {
  remove_matrix(NULL, 5);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_start_action) {
  GameStatus_t gs = {};
  UserAction_t act = Start;

  initGameStatus(&gs);

  executionButton(&gs, &act);

  ck_assert_int_eq(gs.pause, 0);
  ck_assert_int_eq(gs.speed, 2);
  clearGameStatus(&gs);
}
END_TEST

START_TEST(test_pause_action) {
  GameStatus_t gs = {};
  UserAction_t act = Pause;

  initGameStatus(&gs);

  executionButton(&gs, &act);

  ck_assert_int_eq(gs.pause, 1);
  ck_assert_int_eq(gs.speed, PAUSE);
  clearGameStatus(&gs);
}
END_TEST

START_TEST(test_terminate_action) {
  GameStatus_t gs = {};
  UserAction_t act = Terminate;

  executionButton(&gs, &act);

  ck_assert_int_eq(gs.flag, 0);
}
END_TEST

START_TEST(test_left_action) {
  GameStatus_t gs = {};
  UserAction_t act = Left;

  initGameStatus(&gs);

  gs.pause = 0;
  gs.posX = 5;

  executionButton(&gs, &act);

  ck_assert_int_eq(gs.posX, 4);
  clearGameStatus(&gs);
}
END_TEST

START_TEST(test_right_action) {
  GameStatus_t gs = {};
  UserAction_t act = Right;

  initGameStatus(&gs);

  gs.pause = 0;
  gs.posX = 5;

  executionButton(&gs, &act);

  ck_assert_int_eq(gs.posX, 6);
  clearGameStatus(&gs);
}
END_TEST

START_TEST(test_down_action) {
  GameStatus_t gs = {};
  UserAction_t act = Down;

  initGameStatus(&gs);

  gs.pause = 0;
  gs.posY = 5;

  executionButton(&gs, &act);

  ck_assert_int_eq(gs.posY, 6);
  ck_assert(gs.timerDown != 0);
  clearGameStatus(&gs);
}
END_TEST

START_TEST(test_action_action) {
  GameStatus_t gs = {};
  UserAction_t act = Action;

  initGameStatus(&gs);

  executionButton(&gs, &act);

  ck_assert_int_eq(gs.posX, 0);
  clearGameStatus(&gs);
}
END_TEST

START_TEST(test_actions_in_pause) {
  GameStatus_t gs = {};
  UserAction_t act = Left;

  gs.pause = 1;
  gs.posX = 5;

  executionButton(&gs, &act);

  ck_assert_int_eq(gs.posX, 5);
}
END_TEST

START_TEST(test_actions_up) {
  GameStatus_t gs = {};
  UserAction_t act = Up;

  initGameStatus(&gs);

  executionButton(&gs, &act);
  clearGameStatus(&gs);
}
END_TEST

START_TEST(test_init_and_clear) {
  GameStatus_t gs = {};
  GameInfo_t gi = {};

  initGameStatus(&gs);
  clearGameStatus(&gs);

  initGameInfo(&gi);
  clearGameInfo(&gi);
}
END_TEST

START_TEST(test_package_figure_valid_range) {
  for (int fig = 0; fig < 7; fig++) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        int val = packageFigure(fig, i, j);
        ck_assert_int_ge(val, 0);
        ck_assert_int_le(val, 1);
      }
    }
  }
}
END_TEST

START_TEST(test_add_figure_fills_non_zero_cells) {
  int** figure = (int**)malloc(4 * sizeof(int*));
  for (int i = 0; i < 4; i++) {
    figure[i] = (int*)malloc(4 * sizeof(int));
    for (int j = 0; j < 4; j++) {
      figure[i][j] = 0;
    }
  }

  addFigure(figure);

  int non_zero = 0;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (figure[i][j]) non_zero++;

  ck_assert_int_ge(non_zero, 4);
  for (int i = 0; i < 4; i++) free(figure[i]);
  free(figure);
}
END_TEST

START_TEST(test_copy_next_copies_figure_correctly) {
  GameStatus_t gs = {};
  initGameStatus(&gs);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) gs.next[i][j] = (i + j) % 2;

  copyNext(&gs);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      ck_assert_int_eq(gs.Figure[i][j], gs.next[i][j]);

  ck_assert_int_eq(gs.posY, 0);
  ck_assert_int_ge(gs.posX, 0);
  ck_assert_int_lt(gs.posX, WIDTH);
  clearGameStatus(&gs);
}
END_TEST

START_TEST(test_width_for_start_calculates_correctly) {
  int** figure = (int**)malloc(4 * sizeof(int*));
  for (int i = 0; i < 4; i++) {
    figure[i] = (int*)calloc(4, sizeof(int));
  }

  figure[1][0] = 1;
  figure[1][1] = 1;
  figure[1][2] = 1;

  int width = widthForStart(figure);
  ck_assert_int_eq(width, 3);

  for (int i = 0; i < 4; i++) free(figure[i]);
  free(figure);
}
END_TEST

START_TEST(test_width_for_start_first_condition) {
  int** figure = (int**)malloc(4 * sizeof(int*));
  for (int i = 0; i < 4; i++) {
    figure[i] = (int*)calloc(4, sizeof(int));
  }

  figure[0][2] = 1;
  figure[0][3] = 1;
  figure[1][1] = 1;
  figure[1][2] = 1;

  int width = widthForStart(figure);
  ck_assert_int_eq(width, 3);

  for (int i = 0; i < 4; i++) free(figure[i]);
  free(figure);
}
END_TEST

START_TEST(test_width_for_start_second_condition) {
  int** figure = (int**)malloc(4 * sizeof(int*));
  for (int i = 0; i < 4; i++) {
    figure[i] = (int*)calloc(4, sizeof(int));
  }

  figure[0][1] = 1;
  figure[0][2] = 1;
  figure[1][2] = 1;
  figure[1][3] = 1;

  int width = widthForStart(figure);
  ck_assert_int_eq(width, 3);

  for (int i = 0; i < 4; i++) free(figure[i]);
  free(figure);
}
END_TEST

START_TEST(test_update_current_state) {
  GameStatus_t gs = {};
  GameInfo_t gi = {};

  initGameStatus(&gs);
  initGameInfo(&gi);

  gs.field[1][1] = 1;
  gs.next[0][0] = 1;
  gs.score = 100;
  gs.high_score = 200;
  gs.level = 3;
  gs.speed = 5;
  gs.pause = 0;

  updateCurrentState(&gi, &gs);

  ck_assert_int_eq(gi.field[1][1], 1);
  ck_assert_int_eq(gi.next[0][0], 1);
  ck_assert_int_eq(gi.score, 100);
  ck_assert_int_eq(gi.high_score, 200);
  ck_assert_int_eq(gi.level, 3);
  ck_assert_int_eq(gi.speed, 50);
  ck_assert_int_eq(gi.pause, 0);

  clearGameStatus(&gs);
  clearGameInfo(&gi);
}
END_TEST

Suite* game_suite() {
  Suite* s = suite_create("GameLogic");

  TCase* tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_create_matrix_valid);
  tcase_add_test(tc_core, test_create_matrix_invalid_zero_rows);
  tcase_add_test(tc_core, test_create_matrix_invalid_zero_cols);
  tcase_add_test(tc_core, test_remove_matrix_null);
  tcase_add_test(tc_core, test_score_logic);
  tcase_add_test(tc_core, test_updateScore_logic);
  tcase_add_test(tc_core, test_chekLevel_logic);
  tcase_add_test(tc_core, test_makeField_and_clearFigure_logic);
  tcase_add_test(tc_core, test_canMove_logic);
  tcase_add_test(tc_core, test_canRotate_logic);
  tcase_add_test(tc_core, test_checkSquare_logic);
  tcase_add_test(tc_core, test_clearLines_logic);
  tcase_add_test(tc_core, test_canAddNewFigure_logic);
  tcase_add_test(tc_core, test_rotateFigure_logic);
  tcase_add_test(tc_core, test_start_action);
  tcase_add_test(tc_core, test_pause_action);
  tcase_add_test(tc_core, test_terminate_action);
  tcase_add_test(tc_core, test_left_action);
  tcase_add_test(tc_core, test_right_action);
  tcase_add_test(tc_core, test_down_action);
  tcase_add_test(tc_core, test_action_action);
  tcase_add_test(tc_core, test_actions_in_pause);
  tcase_add_test(tc_core, test_actions_up);
  tcase_add_test(tc_core, test_init_and_clear);
  tcase_add_test(tc_core, test_package_figure_valid_range);
  tcase_add_test(tc_core, test_add_figure_fills_non_zero_cells);
  tcase_add_test(tc_core, test_copy_next_copies_figure_correctly);
  tcase_add_test(tc_core, test_width_for_start_calculates_correctly);
  tcase_add_test(tc_core, test_width_for_start_first_condition);
  tcase_add_test(tc_core, test_width_for_start_second_condition);
  tcase_add_test(tc_core, test_update_current_state);

  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  Suite* s = game_suite();
  SRunner* sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}