package web.controller;

import datasource.mapper.GameDataMapper;
import datasource.model.GameDataS;
import datasource.service.GameStorageService;
import domain.model.Game;
import domain.service.GameInterface;
import domain.service.GameTicTacToe;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import web.mapper.GameWebMapper;
import web.model.GameWeb;

import java.util.UUID;

@RestController
@RequestMapping("/game")
public class GameController {
    private final GameStorageService storageService;

    public GameController(GameStorageService storageService) {
        this.storageService=storageService;
    }

    @PostMapping("/{uuid}")
    public ResponseEntity<?> makeMove(
            @PathVariable UUID uuid,
            @RequestBody GameWeb game
    ) {
        Game gameUser = GameWebMapper.toDomain(game);
        GameInterface gameService = new GameTicTacToe(gameUser);

        if (!gameService.isValid()) {
            return ResponseEntity.badRequest().body("Неккоректное состояние игры");
        }

        if(gameService.endGame()) {
            return ResponseEntity.badRequest().body("Игра окончена");
        }

        gameService.nextMove();
        GameDataS updateGameData=GameDataMapper.toDataSource(gameUser);
        storageService.save(updateGameData);

        if (gameService.endGame()) {
            GameWeb responseWeb = GameWebMapper.toWeb(gameUser);
            return ResponseEntity.ok().header("X-Game-Status", "Complited").body(responseWeb);
        }

        GameWeb responseWeb = GameWebMapper.toWeb(gameUser);
        return ResponseEntity.ok(responseWeb);
    }

    @PostMapping("/new")
    public ResponseEntity<GameWeb> createNewGame() {
        Game newGame = new Game();

        GameDataS gameS = GameDataMapper.toDataSource(newGame);
        storageService.save(gameS);

        GameWeb gameW = GameWebMapper.toWeb(newGame);

        return ResponseEntity.ok(gameW);
    }
}
