#pragma once

#include <SFML/Graphics.hpp>
#include "Point.h"

class Bullet {
    Point position;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    /// constructor + destructor
    Bullet();
    Bullet(float x_, float y_, sf::Texture& texture_);
    ~Bullet() = default;

    /// getters + setters
    Point getPosition() const;
    sf::Sprite getSprite() const;

    /// cc
    Bullet(const Bullet& other) = default;

    /// operator=
    /*Bullet& operator=(const Bullet& other) {
        position = other.position;
        texture = other.texture;
        sprite = other.sprite;
        std::cout << "Bullet operator=\n";
        return *this;
    }*/
    Bullet& operator=(const Bullet& other) = default;

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Bullet& bullet);

    void move(int direction);

};