package datasource.repository;

import datasource.model.GameDataS;

import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;

public class GameRepository {
    private Map<UUID, GameDataS> storage = new ConcurrentHashMap<>();

    public void putSave(GameDataS game) {
        storage.put(game.getUUID(), game);
    }

    public GameDataS getSave(UUID uuid) {
        return storage.get(uuid);
    }
}
