#include "../include/EnemiesFactory.h"

std::vector<std::shared_ptr<Entity>> EnemyFactory::createEnemies(sf::Texture& enemyTexture_, sf::Texture& bulletTexture_) {
    std::vector<std::shared_ptr<Entity>> enemy1Vector;
    enemy1Vector.reserve(2);
//    sf::Texture enemyTexture, bulletTexture;
//    enemyTexture.loadFromFile("enemy.png");
//    bulletTexture.loadFromFile("bulletP.png");

    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(rd());
    std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH - ENTITY_SIZE);
    for (int i = 0; i < 2; i++)
        enemy1Vector.emplace_back(
                Enemy{(float) ((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3)) * 1.0), 200, 1,
                      enemyTexture_, bulletTexture_, true, 1.0f}.clone());
    return enemy1Vector;
}


std::vector<std::shared_ptr<Entity>> Enemy2Factory::createEnemies(sf::Texture& enemyTexture_, sf::Texture& bulletTexture_) {
    std::vector<std::shared_ptr<Entity>> enemy2Vector;
    enemy2Vector.reserve(1);
//    sf::Texture enemyTexture, bulletTexture;
//    enemyTexture.loadFromFile("enemy.png");
//    bulletTexture.loadFromFile("bulletP.png");

    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(rd());
    std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH - ENTITY_SIZE);
    for (int i = 0; i < 1; i++)
        enemy2Vector.emplace_back(
                Enemy2{(float) ((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3)) * 1.0), 90, 1,
                       enemyTexture_, bulletTexture_, true, 1}.clone());
    return enemy2Vector;
}



