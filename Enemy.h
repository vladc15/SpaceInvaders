#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Point.h"
#include "Bullet.h"
#include "Entity.h"

class Enemy : public Entity {
    float direction = 1.0f;

    static int enemyCount;

    void print(std::ostream& os) const override;

    void moveSingleBullet(Bullet& bullet) const override;

public:
    /// constructor + destructor
    //Enemy() : position(0, 0), direction(1), alive(true), speed(0) { bulletVector.clear(); }
    explicit Enemy();
    explicit Enemy(float x_, float y_, float direction_, sf::Texture& texture_, sf::Texture& bulletTexture_, bool alive_ = true, float speed_ = 1, int health_ = 1);
    //~Enemy() { std::cout << "Enemy destructor\n";}
    [[maybe_unused]] std::shared_ptr<Entity> clone() const override;

    /// getters + setters
    Point getPosition() const;
    //float getDirection() const { return direction; }
    std::vector<Bullet>& getBulletVector();
    sf::Sprite& getSprite();
    bool getAlive() const;
    //float getSpeed() const { return speed; }
    static int getEnemyCount();

    void setPosition(const Point& position_);
    //void setBulletVector(std::vector<Bullet> bulletVector) { this->bulletVector = bulletVector; }
    //void setDirection(float direction_) { this->direction = direction_; }
    void setAlive(bool alive_);
    //void setSpeed(float speed_) { this->speed = speed_; }
    //static void upEnemyCount() { enemyCount++; }
    static void downEnemyCount();

    /// cc
    /// operator=
    /// operator<<

    void move() override;

    void move(int direction_) override;

    void shoot() override;
};