#include "Player.h"

void Player::print(std::ostream &os) const {
    os << "Player:" << bulletCooldownTime;
}

void Player::moveSingleBullet(Bullet &bullet) const {
    bullet.move(-1);
}

Player::Player() : Entity() { bulletVector.clear(); bulletCooldown.restart();}

Player::Player(float x_, float y_, sf::Texture &texture_, sf::Texture &bulletTexture_, int bulletCooldownTime_,
               bool alive_, float speed_, int health_) : Entity(x_, y_, texture_, bulletTexture_, alive_, speed_, health_), bulletCooldownTime(bulletCooldownTime_) { bulletVector.clear(); bulletCooldown.restart(); sprite.setPosition(x_, y_);}

[[maybe_unused]] std::shared_ptr<Entity> Player::clone() const {
    return std::make_shared<Player>(*this);
}

Point Player::getPosition() const { return position; }

std::vector<Bullet> &Player::getBulletVector() { return bulletVector; }

sf::Sprite &Player::getSprite() { return sprite; }

void Player::setPosition(const Point &position_) { this->position = position_; }

void Player::move(int direction_) {
    if (direction_ == 0 && position.getX() > 0)
        position.setX(position.getX() - 2);
    else if (direction_ == 1 && position.getX() < SCREEN_WIDTH-ENTITY_SIZE-2)
        position.setX(position.getX() + 2);
    sprite.setPosition(position.getX(), position.getY());
}

void Player::move() {}

void Player::shoot() {
    if (bulletCooldown.getElapsedTime().asMilliseconds() > bulletCooldownTime){
        bulletCooldown.restart();
        bulletVector.emplace_back(position.getX(), position.getY(), bulletTexture);
    }
}
