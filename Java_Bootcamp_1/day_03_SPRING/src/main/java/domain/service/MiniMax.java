package domain.service;

import domain.model.Matrix;

public class MiniMax {
    private static int MAX_DEPTH=7;

    private static int EMPTY=0;
    private static int O=1;
    private static int X=2;

    public static int[] getBestMove(Matrix matrix) {
        int bestScroe = Integer.MIN_VALUE;
        int[] bestMove = {-1, -1};

        for(int i=0; i<3; ++i) {
            for(int j=0; j<3; ++j) {
                if (matrix.get(i, j)==EMPTY) {
                    matrix.set(i, j, X);
                    int score = minimax(matrix, MAX_DEPTH - 1, false);
                    matrix.set(i, j, EMPTY);

                    if (score>bestScroe) {
                        bestScroe = score;
                        bestMove[0] = i;
                        bestMove[1] = j;
                    }
                }
            }
        }

        return bestMove;
    }

    public static int minimax(Matrix matrix, int depth, boolean isMax) {
        int score = evalute(matrix);

        if (score == 10 || score == -10 || depth == 0 || !hasMoves(matrix)) {
            return score;
        }

        if (isMax) {
            int best = Integer.MAX_VALUE;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (matrix.get(i, j) == EMPTY) {
                        matrix.set(i, j, X);
                        best = Math.min(best, minimax(matrix, depth - 1, false));
                        matrix.set(i, j, EMPTY);
                    }
                }
            }
            return best;
        } else {
            int best = Integer.MAX_VALUE;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (matrix.get(i, j) == EMPTY) {
                        matrix.set(i, j, O);
                        best = Math.min(best, minimax(matrix, depth - 1, true));
                        matrix.set(i, j, EMPTY);
                    }
                }
            }
            return best;
        }
    }

    public static int evalute(Matrix m) {
        for (int i = 0; i < 3; i++) {
            int first = m.get(i, 0);
            if (first != 0 &&
                    first == m.get(i, 1) &&
                    first == m.get(i, 2)) {
                return (first == 2) ? 10 : -10;
            }
        }

        for (int j = 0; j < 3; j++) {
            int first = m.get(0, j);
            if (first != 0 &&
                    first == m.get(1, j) &&
                    first == m.get(2, j)) {
                return (first == 2) ? 10 : -10;
            }
        }

        int center = m.get(1, 1);
        if (center != 0) {
            if (center == m.get(0, 0) && center == m.get(2, 2)) {
                return (center == 2) ? 10 : -10;
            }
            if (center == m.get(0, 2) && center == m.get(2, 0)) {
                return (center == 2) ? 10 : -10;
            }
        }

        return 0;
    }

    private static boolean hasMoves(Matrix matrix) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (matrix.get(i, j) == EMPTY)
                    return true;
        return false;
    }
}
