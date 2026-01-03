package web.model;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.UUID;

public class GameWeb {
    private final MatrixWeb matrix;
    private final UUID uuid;

    public GameWeb(MatrixWeb matrix, UUID uuid) {
        this.matrix = matrix;
        this.uuid = uuid;
    }

    public GameWeb() {
        this.matrix = new MatrixWeb();
        this.uuid = UUID.randomUUID();
    }

    public UUID getUuid() {
        return uuid;
    }

    public MatrixWeb getMatrix() {
        return matrix;
    }
}
