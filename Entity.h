#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Point.h"
#include "Bullet.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int ENTITY_SIZE = 36;
const int BULLET_SIZE = 16;

class Entity {

protected:
    Point position;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture bulletTexture;
    std::vector<Bullet> bulletVector;
    bool alive;
    float speed;
    int health; /// pentru enemy sa fie 1, pentru boss sa fie 3, iar pentru player sa fie 3 (hard mode: 1)


    Entity(const Entity& other) = default;
    Entity& operator=(const Entity& other) = default;

private:
    virtual void print(std::ostream& ) const;

    virtual void moveSingleBullet(Bullet& bullet) const = 0;

public:
    /// constructor + destructor

    /// cu std::move eventual
    explicit Entity();
    explicit Entity(float x_, float y_, sf::Texture& texture_, sf::Texture& bulletTexture_, bool alive_, float speed_, int health_);
    //virtual ~Entity() { std::cout << "Entity destructor\n"; }
    virtual ~Entity() = default;

    [[maybe_unused]] virtual std::shared_ptr<Entity> clone() const = 0;
    /// getters + setters

    Point getPosition() const;
    std::vector<Bullet>& getBulletVector();
    sf::Sprite& getSprite();
    bool getAlive() const;
    int getHealth() const;

    void setPosition(const Point& position_);
    void setAlive(bool alive_);
    void setHealth(int health_);

    /// cc
    /// operator=
    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity);

    virtual void move() = 0;
    virtual void move(int direction_) = 0;

    virtual void shoot() = 0;

    void moveBullets();

    int intersectsBullet(const Bullet& bullet);

    bool intersectsEntity(const Entity& entity);
};