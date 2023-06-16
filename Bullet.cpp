#include "Bullet.h"

Bullet::Bullet() : position(0, 0) {}

Bullet::Bullet(int x_, int y_, sf::Texture &texture_) : position(x_, y_), sprite(texture_) { sprite.setPosition((float)x_, (float)y_); }

Point<int> Bullet::getPosition() const { return position; }

sf::Sprite Bullet::getSprite() const { return sprite; }

std::ostream &operator<<(std::ostream &os, const Bullet &bullet) {
    os << "x: " << bullet.position.getX() << " y: " << bullet.position.getY();
    return os;
}

void Bullet::move(int direction) {
    position.setY(position.getY() + direction * 2);
    sprite.setPosition((float)position.getX(), (float)position.getY());
}
