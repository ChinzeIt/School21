package web.mapper;

import domain.model.Game;
import domain.model.Matrix;
import web.model.GameWeb;

public class GameWebMapper {
    public static GameWeb toWeb(Game game) {
        return new GameWeb(web.mapper.MatrixWebMapper.toWeb(game.getMatrix()), game.getUUID());
    }

    public static Game toDomain(GameWeb game) {
        Matrix matrix = MatrixWebMapper.toDomain(game.getMatrix());
        return new Game(game.getUuid(), matrix);
    }
}