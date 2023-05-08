#include "Enemy2.h"

void Enemy2::print(std::ostream &os) const {
    os << "Enemy2: " << direction;
}

void Enemy2::moveSingleBullet(Bullet &bullet) const {
    bullet.move(1);
}

Enemy2::Enemy2() : Entity() { bulletVector.clear(); sprite.setPosition(0, 0); }

Enemy2::Enemy2(float x_, float y_, float direction_, sf::Texture &texture_, sf::Texture &bulletTexture_, bool alive_,
               float speed_, int health_) : Entity(x_, y_, texture_, bulletTexture_, alive_, speed_, health_), direction(direction_)
{ bulletVector.clear(); sprite.setTexture(texture_); sprite.setPosition(x_, y_);
    if (std::abs(direction_) != 1) throw entityError("enemy direction must be 1 or -1");
}

[[maybe_unused]] std::shared_ptr<Entity> Enemy2::clone() const {
    return std::make_shared<Enemy2>(*this);
}

void Enemy2::move() {
    if (position.getX() > SCREEN_WIDTH-ENTITY_SIZE || position.getX() < 0) {
        direction *= -1;
        position.setY(position.getY() + 1.2f * ENTITY_SIZE);
    }
    position.setX(position.getX() + direction * 2.2f * speed);
    sprite.setPosition(position.getX(), position.getY());
}

void Enemy2::move(int direction_) {
    std::cout << "Wrong function for Enemy move with " << direction_ << "!\n";
    move();
}

void Enemy2::shoot() {
    bulletVector.emplace_back(position.getX() - 0.5 * BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
    bulletVector.emplace_back(position.getX() + 0.5 * BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
}
