#include "Enemy.h"

void Enemy::print(std::ostream &os) const {
    os << "Enemy: " << direction;
}

void Enemy::moveSingleBullet(Bullet &bullet) const {
    bullet.move(1);
}

Enemy::Enemy() : Entity() { bulletVector.clear(); sprite.setPosition(0, 0);}

Enemy::Enemy(float x_, float y_, float direction_, sf::Texture &texture_, sf::Texture &bulletTexture_, bool alive_,
             float speed_, int health_) : Entity(x_, y_, texture_, bulletTexture_, alive_, speed_, health_), direction(direction_)
             { bulletVector.clear(); sprite.setTexture(texture_); sprite.setPosition(x_, y_);
               if (std::abs(direction_) != 1) throw entityError("enemy direction must be 1 or -1");
             }

[[maybe_unused]] std::shared_ptr<Entity> Enemy::clone() const {
    return std::make_shared<Enemy>(*this);
}

void Enemy::move() {
    if (position.getX() > SCREEN_WIDTH-ENTITY_SIZE || position.getX() < 0) {
        direction *= -1;
        position.setY(position.getY() + 1.2f * ENTITY_SIZE);
    }
    position.setX(position.getX() + direction * 2.0f * speed);
    sprite.setPosition(position.getX(), position.getY());
}

void Enemy::move(int direction_) {
    std::cout << "Wrong function for Enemy move with " << direction_ << "!\n";
    move();
}

void Enemy::shoot() {
    bulletVector.emplace_back(position.getX() + BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
}

/*Enemy::~Enemy() {
    std::cout << "Enemy destructor\n";
}

Enemy::Enemy(const Enemy &other) : Entity(other), direction(other.direction) {
    sprite.setTexture(other.texture);
    sprite.setPosition(other.position.getX(), other.position.getY());
    std::cout << "Enemy copy constructor\n";
}

Enemy &Enemy::operator=(const Enemy &other) {
    if (this == &other) return *this;
    Entity::operator=(other);
    sprite.setTexture(other.texture);
    sprite.setPosition(other.position.getX(), other.position.getY());
    direction = other.direction;
    std::cout << "Enemy op=\n";
    return *this;
}*/
