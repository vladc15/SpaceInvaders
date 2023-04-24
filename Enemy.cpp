#include "Enemy.h"

int Enemy::enemyCount = 0;

void Enemy::print(std::ostream &os) const {
    os << "Enemy: " << direction;
}

void Enemy::moveSingleBullet(Bullet &bullet) const {
    bullet.move(1);
}

Enemy::Enemy() : Entity() { bulletVector.clear(); sprite.setPosition(0, 0); enemyCount++;}

Enemy::Enemy(float x_, float y_, float direction_, sf::Texture &texture_, sf::Texture &bulletTexture_, bool alive_,
             float speed_, int health_) : Entity(x_, y_, texture_, bulletTexture_, alive_, speed_, health_), direction(direction_)
             { bulletVector.clear(); sprite.setPosition(x_, y_); enemyCount++;}

[[maybe_unused]] std::shared_ptr<Entity> Enemy::clone() const {
    return std::make_shared<Enemy>(*this);
}

Point Enemy::getPosition() const { return position; }

std::vector<Bullet> &Enemy::getBulletVector() { return bulletVector; }

sf::Sprite &Enemy::getSprite() { return sprite; }

bool Enemy::getAlive() const { return alive; }

void Enemy::setPosition(const Point &position_) { this->position = position_; }

void Enemy::setAlive(bool alive_) { this->alive = alive_; }

void Enemy::move() {
    if (position.getX() > SCREEN_WIDTH-ENTITY_SIZE || position.getX() < 0) {
        direction *= -1;
        position.setY(position.getY() + 1.2f * ENTITY_SIZE);
    }
    position.setX(position.getX() + direction * 2.0f);
    sprite.setPosition(position.getX(), position.getY());
}

void Enemy::move(int direction_) {
    std::cout << "Wrong function for Enemy move with " << direction_ << "!\n";
    move();
}

void Enemy::shoot() {
    bulletVector.emplace_back(position.getX() + BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
}

int Enemy::getEnemyCount() { return enemyCount; }

void Enemy::downEnemyCount() { enemyCount--; }
