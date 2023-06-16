#pragma once

#include "Entity.h"
#include "Enemy.h"
#include "Enemy2.h"
#include <vector>
#include <memory>
#include <random>

class EnemiesFactory {
public:
    EnemiesFactory() = default;
    virtual ~EnemiesFactory() = default;
    virtual std::vector<std::shared_ptr<Entity>> createEnemies(sf::Texture& enemyTexture_, sf::Texture& bulletTexture_) = 0;
};

class EnemyFactory : public EnemiesFactory {
public:
    explicit EnemyFactory() = default;
    std::vector<std::shared_ptr<Entity>> createEnemies(sf::Texture& enemyTexture_, sf::Texture& bulletTexture_) override;
};

class Enemy2Factory : public EnemiesFactory {
public:
    explicit Enemy2Factory() = default;
    std::vector<std::shared_ptr<Entity>> createEnemies(sf::Texture& enemyTexture_, sf::Texture& bulletTexture_) override;
};