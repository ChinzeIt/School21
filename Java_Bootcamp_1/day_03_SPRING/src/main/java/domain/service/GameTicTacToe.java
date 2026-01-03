package domain.service;

import domain.model.Game;
import domain.model.Matrix;

public class GameTicTacToe  implements GameInterface{
    private Game game;

    public GameTicTacToe(Game game) {
        this.game=game;
    }
    @Override
    public Matrix nextMove() {
        Matrix matrix = game.getMatrix();

        int[] bestMove = MiniMax.getBestMove(matrix);

        if (bestMove[0]!=-1) matrix.set(bestMove[0], bestMove[1], 2);

        return matrix;
    }

    @Override
    public boolean isValid() {
        Matrix m = game.getMatrix();

        int countX=0;
        int countO=0;

        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                int v = m.get(i, j);
                if (v==1) ++countO;
                else if (v==2) ++countX;
                else if (v!=0) return false;
            }
        }

        return Math.abs(countO-countX) <= 1;
    }

    @Override
    public boolean endGame() {
        Matrix m = game.getMatrix();

        if (MiniMax.evalute(m)!=0)
            return true;

        for (int i=0; i<3; ++i)
            for (int j = 0; j < 3; ++j)
                if (m.get(i,j)==0) return false;

        return true;
    }
}
