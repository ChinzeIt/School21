package datasource.mapper;

import datasource.model.GameDataS;
import domain.model.Game;
import domain.model.Matrix;

import java.util.UUID;

public class GameDataMapper {
    public static GameDataS toDataSource(Game game) {
        return new GameDataS(MatrixDataMapper.toDataSource(game.getMatrix()), game.getUUID());
    }

    public static Game toDomain(GameDataS game) {
        UUID savedUuid = game.getUUID();
        Matrix savedMatrix = MatrixDataMapper.toDomain(game.getMatrix());

        return new Game(savedUuid, savedMatrix);
    }
}
