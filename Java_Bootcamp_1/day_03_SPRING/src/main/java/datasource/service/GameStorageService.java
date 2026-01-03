package datasource.service;

import datasource.model.GameDataS;
import datasource.repository.GameRepository;

import java.util.UUID;

public class GameStorageService implements GameStorageServiceInterface {
    private GameRepository repository;

    public GameStorageService(GameRepository repository) {
        this.repository=repository;
    }
    @Override
    public void save (GameDataS game) {
        repository.putSave(game);
    }
    @Override
    public GameDataS getSave(UUID uuid) {
        return repository.getSave(uuid);
    }
}
