#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Point.h"
#include "Bullet.h"
#include "Entity.h"
#include "Exceptions.h"

class Player : public Entity {
    sf::Clock bulletCooldown;
    int bulletCooldownTime = 100;
    int score = 0;

    void print(std::ostream& os) const override;

    void moveSingleBullet(Bullet& bullet) const override;

    explicit Player();
    explicit Player(float x_, float y_, sf::Texture& texture_, sf::Texture& bulletTexture_, int bulletCooldownTime_, bool alive_ = true, float speed_ = 1, int health_ = 1, int score_ = 0);

public:
    /// constructor + destructor

    //~Player() { std::cout << "Player destructor\n";}
    [[maybe_unused]] std::shared_ptr<Entity> clone() const override;
//    Player() : position(0, 0) { bulletVector.clear(); bulletCooldown.restart();}
//    Player(float x_, float y_, sf::Texture& texture_, sf::Texture& bulletTexture_, int bulletCooldownTime_) : position(x_, y_), sprite(texture_), bulletTexture(bulletTexture_), bulletCooldownTime(bulletCooldownTime_) { bulletVector.clear(); bulletCooldown.restart(); sprite.setPosition(x_, y_);}
//    ~Player() { std::cout << "Player destructor\n";}
    //~Player() override;

    static Player& getInstance(float x_, float y_, sf::Texture& texture_, sf::Texture& bulletTexture_, int bulletCooldownTime_, bool alive_ = true, float speed_ = 1, int health_ = 1, int score_ = 0);

    /// getters + setters
    int getScore() const;

    void setScore(int score_);
    /// cc
    Player (const Player& other) = delete;
    /// operator=
    Player& operator=(const Player& other) = delete;
    /// warning pentru operator= de la clion

    void move(int direction_) override;

    void move() override;

    void shoot() override;

};