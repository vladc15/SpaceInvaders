#include "Entity.h"

void Entity::print(std::ostream &) const {}

Entity::Entity() : position(0, 0), alive(true), speed(0), health(0) { bulletVector.clear(); }

Entity::Entity(float x_, float y_, sf::Texture &texture_, sf::Texture &bulletTexture_, bool alive_, float speed_,
               int health_) : position(x_, y_), sprite(texture_), bulletTexture(bulletTexture_), alive(alive_), speed(speed_), health(health_) { bulletVector.clear(); sprite.setPosition(x_, y_);}

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
    return (position.getX() < bullet.getPosition().getX() + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > bullet.getPosition().getX())
           && (position.getY() < bullet.getPosition().getY() + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > bullet.getPosition().getY());
}

bool Entity::intersectsEntity(const Entity &entity) {
    return (position.getX() < entity.position.getX() + ENTITY_SIZE) && (position.getX() + ENTITY_SIZE > entity.position.getX())
           && (position.getY() < entity.position.getY() + ENTITY_SIZE) && (position.getY() + ENTITY_SIZE > entity.position.getY());
}


