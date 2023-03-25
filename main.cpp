#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
//#include <chrono>
//#include <thread>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int ENTITY_SIZE = 36;
const int BULLET_SIZE = 16;

class Point {
    float x;
    float y;

public:
    /// constructor + destructor
    Point() : x{0}, y{0} {}
    Point(float x, float y) : x{x}, y{y} {}
    ~Point() = default;

    /// getters + setters
    [[nodiscard]] float getX() const { return x; }
    [[nodiscard]] float getY() const { return y; }

    void setX(float x_) { this->x = x_; }
    void setY(float y_) { this->y = y_; }

    /// cc
    Point(const Point& other) = default;

    /// operator=
    Point& operator=(const Point& other) = default;

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }
};

class Bullet {
    Point position;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    /// constructor + destructor
    Bullet() : position(0, 0) {}
    Bullet(float x_, float y_, sf::Texture& texture_) : position(x_, y_), sprite(texture_) { sprite.setPosition(x_, y_); }
    ~Bullet() = default;

    /// getters + setters
    Point getPosition() const { return position; }
    sf::Sprite getSprite() const { return sprite; }

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
    friend std::ostream& operator<<(std::ostream& os, const Bullet& bullet) {
        os << "x: " << bullet.position.getX() << " y: " << bullet.position.getY();
        return os;
    }

    void move(int direction) {
        position.setY(position.getY() + (float)direction * 2.0f);
        sprite.setPosition(position.getX(), position.getY());
    }

};

class Player {
    Point position;
    std::vector<Bullet> bulletVector;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture bulletTexture;
    sf::Clock bulletCooldown;
    int bulletCooldownTime = 100;

public:
    /// constructor + destructor
    Player() : position(0, 0) { bulletVector.clear(); bulletCooldown.restart();}
    Player(float x_, float y_, sf::Texture& texture_, sf::Texture& bulletTexture_, int bulletCooldownTime_) : position(x_, y_), sprite(texture_), bulletTexture(bulletTexture_), bulletCooldownTime(bulletCooldownTime_) { bulletVector.clear(); bulletCooldown.restart(); sprite.setPosition(x_, y_);}
    ~Player() { std::cout << "Player destructor\n";}


    /// getters + setters
    Point getPosition() const { return position; }
    std::vector<Bullet>& getBulletVector() { return bulletVector; }
    sf::Sprite& getSprite() { return sprite; }

    void setPosition(const Point& position_) { this->position = position_; }
    //void setBulletVector(std::vector<Bullet> bulletVector) { this->bulletVector = bulletVector; }

    /// cc
    //Player(const Player& other) : position{other.position}, bulletVector{other.bulletVector}, bulletCooldownTime{other.bulletCooldownTime} {}
    Player(const Player& other) = default;

    /// operator=
    /*Player& operator=(const Player& other) {
        position = other.position;
        bulletVector = other.bulletVector;
        return *this;
    }*/
    /// warning pentru operator= de la clion
    Player& operator=(const Player& other) = default;

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "x: " << player.position.getX() << " y: " << player.position.getY();
        return os;
    }

    void move(int direction) {
        if (direction == 0 && position.getX() > 0)
            position.setX(position.getX() - 2);
        else if (direction == 1 && position.getX() < SCREEN_WIDTH-ENTITY_SIZE-2)
            position.setX(position.getX() + 2);
        sprite.setPosition(position.getX(), position.getY());
    }

    void shoot() {
        if (bulletCooldown.getElapsedTime().asMilliseconds() > bulletCooldownTime){
            bulletCooldown.restart();
            bulletVector.emplace_back(position.getX(), position.getY(), bulletTexture);
        }
    }

    void moveBullets() {
        std::vector<Bullet>& playerBullet = getBulletVector();
        auto it1 = playerBullet.begin();
        for (auto it = playerBullet.begin(); it != playerBullet.end(); it++) {
            it->move(-1);
            if (it->getPosition().getY() < 0)
                it1 = it;
        }
        playerBullet.erase(playerBullet.begin(), it1);
    }

    int intersects(const Bullet& bullet) {
        //return sprite.getGlobalBounds().intersects( bullet.getSprite().getGlobalBounds() );
        return (position.getX() < bullet.getPosition().getX() + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > bullet.getPosition().getX())
               && (position.getY() < bullet.getPosition().getY() + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > bullet.getPosition().getY());
    }

};

class Enemy {
    Point position;
    //float speed;
    float direction = 1.0f;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<Bullet> bulletVector;
    sf::Texture bulletTexture;
public:
    /// constructor + destructor
    Enemy() : position(0, 0), direction(1) { bulletVector.clear(); }
    Enemy(float x_, float y_, float direction_, sf::Texture& texture_, sf::Texture& bulletTexture_) : position(x_, y_), direction(direction_), sprite(texture_), bulletTexture(bulletTexture_) { bulletVector.clear(); sprite.setPosition(x_, y_);}
    ~Enemy() { std::cout << "Enemy destructor\n";}

    /// getters + setters
    Point getPosition() const { return position; }
    //float getDirection() const { return direction; }
    std::vector<Bullet>& getBulletVector() { return bulletVector; }
    sf::Sprite& getSprite() { return sprite; }

    void setPosition(const Point& position_) { this->position = position_; }
    //void setBulletVector(std::vector<Bullet> bulletVector) { this->bulletVector = bulletVector; }
    //void setDirection(float direction_) { this->direction = direction_; }

    /// cc
    Enemy(const Enemy& other) : position{other.position}, direction(other.direction), bulletVector{other.bulletVector} {}

    /// operator=
    Enemy& operator=(const Enemy& other) {
        position = other.position;
        bulletVector = other.bulletVector;
        direction = other.direction;
        return *this;
    }

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
        os << "x: " << enemy.position.getX() << " y: " << enemy.position.getY() << " direction: " << enemy.direction << "\n";
        return os;
    }

    void move() {
        if (position.getX() > SCREEN_WIDTH-ENTITY_SIZE || position.getX() < 0) {
            direction *= -1;
            position.setY(position.getY() + 5.0f);
        }
        position.setX(position.getX() + direction * 2.0f);
        sprite.setPosition(position.getX(), position.getY());
    }

    void shoot() {
        bulletVector.emplace_back(position.getX() + BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
    }

    void moveBullets() {
        std::vector<Bullet>& enemyBullet = getBulletVector();
        auto it1 = enemyBullet.begin();
        for (auto it = enemyBullet.begin(); it != enemyBullet.end(); it++) {
            it->move(1);
            if (it->getPosition().getY() > SCREEN_HEIGHT)
                it1 = it;
        }
        enemyBullet.erase(enemyBullet.begin(), it1);
    }

    bool intersects(const Bullet& bullet) {
        /*
         position.getX() == sprite.getGlobalBounds().left
         position.getY() == sprite.getGlobalBounds().top
         sprite.getGlobalBounds().height = 36
         sprite.getGlobalBounds().width = 36
         bullet.getSprite().getGlobalBounds().height = 16
         bullet.getSprite().getGlobalBounds().width = 16
         bullet.getSprite().getGlobalBounds().left == bullet.getPosition().getX()
         bullet.getSprite().getGlobalBounds().top == bullet.getPosition().getY()
         */
        //return sprite.getGlobalBounds().intersects( bullet.getSprite().getGlobalBounds() );

        return (position.getX() < bullet.getPosition().getX() + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > bullet.getPosition().getX())
                && (position.getY() < bullet.getPosition().getY() + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > bullet.getPosition().getY());
    }
};


int main() {
#ifdef __linux__
    XInitThreads();
#endif

    /// testarea obiectelor Point
    Point p1, p2(1, 2);
    p1 = p2;
    std::cout << p1 << p2 << "\n";


    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");

    sf::Texture playerTexture, bulletTexture, enemyTexture;
    playerTexture.loadFromFile("C:/Users/vciup/Desktop/C++/OOP/player.png");
    bulletTexture.loadFromFile("C:/Users/vciup/Desktop/C++/OOP/bulletP.png");
    enemyTexture.loadFromFile("C:/Users/vciup/Desktop/C++/OOP/enemy.png");
    Player player(350, 500, playerTexture, bulletTexture, 150);
    Enemy enemy(350, 100, 1, enemyTexture, bulletTexture);

    /// testarea obiectelor Bullet, Player, Enemy
    Bullet b1(0, 0, bulletTexture), b2;
    b2 = b1;
    std::cout << b1 << b2 << "\n";
    Player player2, player1(1, 1, playerTexture, bulletTexture, 20);
    player2 = player1;
    std::cout << player1 << "\n" << player2 << "\n";
    Enemy e1;
    e1 = enemy;
    std::cout << e1 << "\n";


    //srand(time(nullptr));
    /// warning pentru randomness
    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(rd());
    std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH-ENTITY_SIZE);

    enemy.setPosition(Point((float)dist(rng), 150)); /// facem random si poz

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(0);
        else
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player.move(1);
            else
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    player.shoot();

        std::vector<Bullet>& playerBullet = player.getBulletVector();
        player.moveBullets();

        enemy.move();
        if (dist(rng) % 100 < 2)
            enemy.shoot();
        std::vector<Bullet>& enemyBullet = enemy.getBulletVector();
        enemy.moveBullets();

        for (auto& bullet : playerBullet) {
            if (enemy.intersects(bullet)) {
                playerBullet.pop_back();
                std::cout << "You Win!\n";
                window.close();
                return 0;
            }
        }

        for (auto& bullet : enemyBullet) {
            if (player.intersects(bullet)) {
                //enemyBullet.pop_back();
                std::cout << "Game Over:(\n";
                window.close();
                return 0;
            }
        }

        window.clear(sf::Color::Black);

        //window.draw(sprite);
        window.draw(player.getSprite());
        window.draw(enemy.getSprite());
        for (const Bullet& bullet : playerBullet)
            window.draw(bullet.getSprite());
        for (const Bullet& bullet : enemyBullet)
            window.draw(bullet.getSprite());

        window.display();

        /// cat sa astepte intre frame uri
        while (clock.getElapsedTime().asMilliseconds() < 10) {}
        clock.restart();
        //std::this_thread::sleep_for(std::chrono::microseconds (990));
        //std::this_thread::sleep_for(std::chrono::duration<double, std::milli> (0.9));
        //std::this_thread::sleep_for(std::chrono::milliseconds (10));
        // prea incet??
        //std::this_thread::sleep_for(std::chrono::microseconds (900)); // diferenta prea mare intre 990 si 1000?

        /// mesajele de la cc, constructor si destructor pentru point si bullet dau delay
    }

    return 0;
}