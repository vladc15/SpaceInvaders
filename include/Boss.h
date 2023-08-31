#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Point.h"
#include "Bullet.h"
#include "Entity.h"
#include "Exceptions.h"

class Boss : public Entity {
    float direction = 1.0f;

    sf::Clock regenerationClock;
    int regenerationTime = 10;

    void print(std::ostream& os) const override;

    void moveSingleBullet(Bullet& bullet) const override;

public:
    /// constructor + destructor
    //Boss() : position(0, 0), direction(1), alive(true), speed(0), health(3) { bulletVector.clear(); regenerationClock.restart(); }
    explicit Boss(float x_, float y_, float direction_, sf::Texture& texture_, sf::Texture& bulletTexture_, bool alive_, float speed_, int health_, int regenerationTime_);
    //~Boss() { std::cout << "Boss destructor\n";}
    [[maybe_unused]] std::shared_ptr<Entity> clone() const override;
    //~Boss() override;

    /// getters + setters

    /// cc
    //Boss (const Boss& other);
    /// operator=
    //Boss& operator=(const Boss& other);
    /// operator<<

    void move() override;

    void move(int direction_) override;

    void shoot() override;

    void regenerate();

    void restartClock();
};
