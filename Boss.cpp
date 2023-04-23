#include "Boss.h"

void Boss::print(std::ostream &os) const {
    os << "Boss: " << regenerationTime;
}

void Boss::moveSingleBullet(Bullet &bullet) const {
    bullet.move(1);
}

Boss::Boss(float x_, float y_, float direction_, sf::Texture &texture_, sf::Texture &bulletTexture_, bool alive_,
           float speed_, int health_, int regenerationTime_) : Entity(x_, y_, texture_, bulletTexture_, alive_, speed_, health_), direction(direction_), regenerationTime(regenerationTime_) { bulletVector.clear(); sprite.setPosition(x_, y_);}

std::shared_ptr<Entity> Boss::clone() const {
    return std::make_shared<Boss>(*this);
}

Point Boss::getPosition() const { return position; }

std::vector<Bullet> &Boss::getBulletVector() { return bulletVector; }

sf::Sprite &Boss::getSprite() { return sprite; }

bool Boss::getAlive() const { return alive; }

int Boss::getHealth() const { return health; }

void Boss::setPosition(const Point &position_) { this->position = position_; }

void Boss::setAlive(bool alive_) { this->alive = alive_; }

void Boss::setHealth(int health_) { this->health = health_; }

void Boss::move() {
    if (position.getX() > SCREEN_WIDTH-ENTITY_SIZE || position.getX() < 0) {
        direction *= -1;
        position.setY(position.getY() + 1.2f * ENTITY_SIZE);
    }
    position.setX(position.getX() + direction * 2.0f);
    sprite.setPosition(position.getX(), position.getY());
}

void Boss::move(int direction_) {
    std::cout << "Wrong function for Boss move with " << direction_ << "!\n";
    move();
}

void Boss::shoot() {
    bulletVector.emplace_back(position.getX() - BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
    bulletVector.emplace_back(position.getX() + BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
    bulletVector.emplace_back(position.getX() + 3*BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
}

void Boss::regenerate() {
    if (regenerationClock.getElapsedTime().asSeconds() > float(regenerationTime)) {
        health = std::min(3, health+1);
        regenerationClock.restart();
    }
}
