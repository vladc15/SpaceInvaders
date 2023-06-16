#include "Entity.h"

void Entity::print(std::ostream &) const {}

Entity::Entity() : position(0, 0), alive(true), speed(0), health(0) { bulletVector.clear(); }

Entity::Entity(float x_, float y_, sf::Texture &texture_, sf::Texture &bulletTexture_, bool alive_, float speed_,
               int health_) : position(x_, y_), sprite(texture_), texture(texture_), bulletTexture(bulletTexture_), alive(alive_), speed(speed_), health(health_)
               { bulletVector.clear(); sprite.setTexture(texture_); sprite.setPosition(x_, y_);
                 if (health_ < 0) throw entityError("health must be positive");
                 if (!(x_ >= 0 && x_ <= SCREEN_WIDTH - ENTITY_SIZE && y_ >= 0 && y_ <= SCREEN_HEIGHT - ENTITY_SIZE))
                     throw entityError("position must be in the screen limits");
               }

Point<float> Entity::getPosition() const { return position; }
std::vector<Bullet> &Entity::getBulletVector() { return bulletVector; }
sf::Sprite &Entity::getSprite() { return sprite; }
int Entity::getHealth() const { return health; }
bool Entity::getAlive() const { return alive; }

void Entity::setPosition(const Point<float> &position_) { this->position = position_; }
void Entity::setHealth(int health_) { this->health = health_; }
void Entity::setAlive(bool alive_) { this->alive = alive_; }

std::ostream &operator<<(std::ostream &os, const Entity &entity) {
    os << "Entity: " << entity.position.getX() << " y: " << entity.position.getY() << "health: " << entity.health;
    entity.print(os);
    os << "\n";
    return os;
}

void Entity::moveBullets() {
    auto it1 = bulletVector.begin();
    for (auto it = bulletVector.begin(); it != bulletVector.end(); it++) {
        //it->move(-1);
        moveSingleBullet(*it);
        if (it->getPosition().getY() < 0 || it->getPosition().getY() > SCREEN_HEIGHT)
            it1 = it;
    }
    bulletVector.erase(bulletVector.begin(), it1);
}

int Entity::intersectsBullet(const Bullet &bullet) {
    return (position.getX() < ((float)bullet.getPosition().getX()) + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > ((float)bullet.getPosition().getX()))
           && (position.getY() < ((float)bullet.getPosition().getY()) + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > ((float)bullet.getPosition().getY()));
}

bool Entity::intersectsEntity(const Entity &entity) {
    return (position.getX() < entity.position.getX() + ENTITY_SIZE) && (position.getX() + ENTITY_SIZE > entity.position.getX())
           && (position.getY() < entity.position.getY() + ENTITY_SIZE) && (position.getY() + ENTITY_SIZE > entity.position.getY());
}

/*Entity::Entity(const Entity &other) : position(other.position), texture(other.texture), bulletTexture(other.bulletTexture),
                                      bulletVector(other.bulletVector), alive(other.alive), speed(other.speed), health(other.health) {
    sprite.setTexture(other.texture);
    sprite.setPosition(other.position.getX(), other.position.getY());
}

Entity &Entity::operator=(const Entity &other) {
    position = other.position;
    texture = other.texture;
    sprite.setTexture(other.texture);
    sprite.setPosition(other.position.getX(), other.position.getY());
    bulletTexture = other.bulletTexture;
    bulletVector = other.bulletVector;
    alive = other.alive;
    speed = other.speed;
    health = other.health;
    return *this;
}

Entity::~Entity() {
    std::cout << "Entity destructor\n";
}*/


