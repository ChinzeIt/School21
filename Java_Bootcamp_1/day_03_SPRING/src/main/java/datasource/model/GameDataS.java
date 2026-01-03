package datasource.model;

import java.util.UUID;

public class GameDataS {
    private final MatrixDataS matrix;
    private final UUID uuid;

    public GameDataS(MatrixDataS matrix, UUID uuid) {
        this.matrix = matrix;
        this.uuid = uuid;
    }

    public UUID getUUID() {
        return uuid;
    }

    public MatrixDataS getMatrix() {
        return matrix;
    }
}
