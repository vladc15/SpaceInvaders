#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Point.h"
#include "Bullet.h"
#include "Entity.h"
#include "Exceptions.h"

class Enemy2 : public Entity {
    float direction = 1.0f;

    void print(std::ostream& os) const override;

    void moveSingleBullet(Bullet& bullet) const override;

public:
    /// constructor + destructor
    explicit Enemy2();
    explicit Enemy2(float x_, float y_, float direction_, sf::Texture& texture_, sf::Texture& bulletTexture_, bool alive_ = true, float speed_ = 1, int health_ = 1);
    [[maybe_unused]] std::shared_ptr<Entity> clone() const override;

    /// getters + setters

    void move() override;

    void move(int direction_) override;

    void shoot() override;
};