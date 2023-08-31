#include "../include/Boss.h"

void Boss::print(std::ostream &os) const {
    os << "Boss: " << regenerationTime;
}

void Boss::moveSingleBullet(Bullet &bullet) const {
    bullet.move(1);
}

Boss::Boss(float x_, float y_, float direction_, sf::Texture &texture_, sf::Texture &bulletTexture_, bool alive_,
           float speed_, int health_, int regenerationTime_) : Entity(x_, y_, texture_, bulletTexture_, alive_, speed_, health_), direction(direction_), regenerationTime(regenerationTime_)
           { bulletVector.clear(); sprite.setPosition(x_, y_);
             if (std::abs(direction_) != 1) throw entityError("boss direction must be 1 or -1");
             if (regenerationTime_ < 0) throw entityError("regeneration time must be positive");
           }

[[maybe_unused]] std::shared_ptr<Entity> Boss::clone() const {
    return std::make_shared<Boss>(*this);
}

void Boss::move() {
    if (position.getX() > SCREEN_WIDTH-ENTITY_SIZE || position.getX() < 0) {
        direction *= -1;
        position.setY(position.getY() + 1.2f * ENTITY_SIZE);
    }
    position.setX(position.getX() + direction * 2.0f * speed);
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

void Boss::restartClock() {
    regenerationClock.restart();
}

/*Boss::~Boss() {
    std::cout << "Boss destructor\n";
}

Boss::Boss(const Boss &other) : Entity(other), direction(other.direction), regenerationClock(other.regenerationClock), regenerationTime(other.regenerationTime) {
    std::cout << "Boss copy constructor\n";
}

Boss &Boss::operator=(const Boss &other) {
    Entity::operator=(other);
    direction = other.direction;
    regenerationClock = other.regenerationClock;
    regenerationTime = other.regenerationTime;
    std::cout << "Boss op=\n";
    return *this;
}*/
