package datasource.service;

import datasource.model.GameDataS;

import java.util.UUID;

public interface GameStorageServiceInterface {
    void save(GameDataS game);
    GameDataS getSave(UUID uuid);
}
