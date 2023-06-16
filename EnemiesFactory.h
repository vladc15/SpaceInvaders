#pragma once

#include "Entity.h"
#include "Enemy.h"
#include "Enemy2.h"
#include <vector>
#include <memory>
#include <random>

class EnemiesFactory {
public:
    virtual std::vector<std::shared_ptr<Entity>> createEnemies(sf::Texture& enemyTexture_, sf::Texture& bulletTexture_) = 0;
};

class EnemyFactory : public EnemiesFactory {
public:
    std::vector<std::shared_ptr<Entity>> createEnemies(sf::Texture& enemyTexture_, sf::Texture& bulletTexture_) override;
};

class Enemy2Factory : public EnemiesFactory {
public:
    std::vector<std::shared_ptr<Entity>> createEnemies(sf::Texture& enemyTexture_, sf::Texture& bulletTexture_) override;
};