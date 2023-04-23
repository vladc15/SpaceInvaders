#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Point.h"
#include "Bullet.h"
#include "Entity.h"

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

    /// getters + setters
    Point getPosition() const;
    //float getDirection() const { return direction; }
    std::vector<Bullet>& getBulletVector();
    sf::Sprite& getSprite();
    bool getAlive() const;
    //float getSpeed() const { return speed; }
    int getHealth() const;
    //int getRegenerationTime() const { return regenerationTime; }

    void setPosition(const Point& position_);
    //void setBulletVector(std::vector<Bullet> bulletVector) { this->bulletVector = bulletVector; }
    //void setDirection(float direction_) { this->direction = direction_; }
    void setAlive(bool alive_);
    //void setSpeed(float speed_) { this->speed = speed_; }
    void setHealth(int health_);
    //void setRegenerationTime(int regenerationTime_) { this->regenerationTime = regenerationTime_; }
    /// cc
    /// operator=
    /// operator<<

    void move() override;

    void move(int direction_) override;

    void shoot() override;

    void regenerate();
};
