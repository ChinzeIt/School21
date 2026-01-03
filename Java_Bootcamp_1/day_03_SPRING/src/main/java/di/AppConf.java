package di;

import datasource.repository.GameRepository;
import datasource.service.GameStorageService;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class AppConf {
    @Bean
    public GameRepository gameRepository() {
        return new GameRepository();
    }
    @Bean
    public GameStorageService gameStorageService(GameRepository gameRepository) {
        return new GameStorageService(gameRepository);
    }
}
