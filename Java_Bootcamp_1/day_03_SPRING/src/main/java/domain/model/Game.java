package domain.model;

import java.util.UUID;

public class Game {
    private final Matrix matrix;
    private final UUID uuid;

    public Game () {
        matrix = new Matrix();
        uuid = UUID.randomUUID();
    }

    public Game(UUID uuid, Matrix matrix) {
        this.uuid = uuid;
        this.matrix = matrix;
    }

    public Matrix getMatrix() {
        return matrix;
    }

    public UUID getUUID() {
        return uuid;
    }
}
