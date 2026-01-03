package domain.service;

import domain.model.Matrix;

public interface GameInterface {
    public Matrix nextMove();

    public boolean isValid();

    public boolean endGame();
}
