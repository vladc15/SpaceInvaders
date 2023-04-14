#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
//#include <chrono>
//#include <thread>
#include "Point.h"
#include "Bullet.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int ENTITY_SIZE = 36;
const int BULLET_SIZE = 16;
const int ENEMY_POINTS = 20;
const int BOSS_POINTS = 90;

/*class Entity {
    Point position;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture bulletTexture;
    std::vector<Bullet> bulletVector;
    bool alive;
    float speed;

public:
    /// constructor + destructor
    Entity() : position(0, 0), alive(true), speed(0) { bulletVector.clear(); }
    Entity(float x_, float y_, sf::Texture& texture_, sf::Texture& bulletTexture_, bool alive_, float speed_) : position(x_, y_), sprite(texture_), bulletTexture(bulletTexture_), alive(alive_), speed(speed_) { bulletVector.clear(); sprite.setPosition(x_, y_);}
    ~Entity() { std::cout << "Entity destructor\n";}

    /// getters + setters
    Point getPosition() const { return position; }
    std::vector<Bullet>& getBulletVector() { return bulletVector; }
    sf::Sprite& getSprite() { return sprite; }
    bool getAlive() const { return alive; }
    float getSpeed() const { return speed; }

    void setPosition(const Point& position_) { this->position = position_; }
    void setAlive(bool alive_) { this->alive = alive_; }
    void setSpeed(float speed_) { this->speed = speed_; }

    /// cc
    Entity(const Entity& other) : position{other.position}, bulletVector{other.bulletVector}, alive{other.alive}, speed{other.speed} {}

    /// operator=
    Entity& operator=(const Entity& other) {
        position = other.position;
        bulletVector = other.bulletVector;
        alive = other.alive;
        speed = other.speed;
        std::cout << "Entity operator=\n";
        return *this;
    }

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Entity& entity){
        os << "x: " << entity.position.getX() << " y: " << entity.position.getY();
        return os;
    }


    void move(int direction) {
        position.setY(position.getY() + (float)direction * speed);
        sprite.setPosition(position.getX(), position.getY());
    }

    void shoot() {
        bulletVector.emplace_back(position.getX() + ENTITY_SIZE / 2.0f - BULLET_SIZE / 2.0f, position.getY() + ENTITY_SIZE / 2.0f - BULLET_SIZE / 2.0f, bulletTexture);
    }

    void moveBullets() {
        auto it1 = bulletVector.begin();
        for (auto it = bulletVector.begin(); it != bulletVector.end(); it++) {
            it->move(-1);
            if (it->getPosition().getY() < 0)
                it1 = it;
        }
        bulletVector.erase(bulletVector.begin(), it1);
    }

    int intersectsEntity(const Entity& other) {
        if (position.getX() + ENTITY_SIZE < other.position.getX() || position.getX() > other.position.getX() + ENTITY_SIZE) {
            return 0;
        }
        if (position.getY() + ENTITY_SIZE < other.position.getY() || position.getY() > other.position.getY() + ENTITY_SIZE) {
            return 0;
        }
        return 1;
    }

    int intersectsBullet(const Bullet& bullet) {
        return (position.getX() < bullet.getPosition().getX() + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > bullet.getPosition().getX())
               && (position.getY() < bullet.getPosition().getY() + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > bullet.getPosition().getY());
    }


};*/

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

    int intersectsBullet(const Bullet& bullet) {
        //return sprite.getGlobalBounds().intersects( bullet.getSprite().getGlobalBounds() );
        return (position.getX() < bullet.getPosition().getX() + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > bullet.getPosition().getX())
               && (position.getY() < bullet.getPosition().getY() + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > bullet.getPosition().getY());
    }

};

class Enemy {
    Point position;
    float direction = 1.0f;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<Bullet> bulletVector;
    sf::Texture bulletTexture;
    bool alive;
    float speed;
public:
    /// constructor + destructor
    Enemy() : position(0, 0), direction(1), alive(true), speed(0) { bulletVector.clear(); }
    Enemy(float x_, float y_, float direction_, sf::Texture& texture_, sf::Texture& bulletTexture_, bool alive_, float speed_) : position(x_, y_), direction(direction_), sprite(texture_), texture(texture_), bulletTexture(bulletTexture_), alive(alive_), speed(speed_) { bulletVector.clear(); sprite.setPosition(x_, y_);}
    ~Enemy() { std::cout << "Enemy destructor\n";}

    /// getters + setters
    Point getPosition() const { return position; }
    //float getDirection() const { return direction; }
    std::vector<Bullet>& getBulletVector() { return bulletVector; }
    sf::Sprite& getSprite() { return sprite; }
    bool getAlive() const { return alive; }
    //float getSpeed() const { return speed; }

    void setPosition(const Point& position_) { this->position = position_; }
    //void setBulletVector(std::vector<Bullet> bulletVector) { this->bulletVector = bulletVector; }
    //void setDirection(float direction_) { this->direction = direction_; }
    void setAlive(bool alive_) { this->alive = alive_; }
    //void setSpeed(float speed_) { this->speed = speed_; }

    /// cc
    Enemy(const Enemy& other) : position{other.position}, direction{other.direction}, texture{other.texture}, bulletVector{other.bulletVector}, bulletTexture{other.bulletTexture}, alive{other.alive}, speed{other.speed} {sprite.setTexture(texture); sprite.setPosition(position.getX(), position.getY());}

    /// operator=
    Enemy& operator=(const Enemy& other) {
        position = other.position;
        bulletVector = other.bulletVector;
        direction = other.direction;
        alive = other.alive;
        speed = other.speed;

        texture = other.texture;
        sprite.setTexture(other.texture);
        sprite.setPosition(other.position.getX(), other.position.getY());
        bulletTexture = other.bulletTexture;
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
            position.setY(position.getY() + 1.2f * ENTITY_SIZE);
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

    bool intersectsBullet(const Bullet& bullet) {
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

    bool intersectsPlayer(const Player& player) {
        return (position.getX() < player.getPosition().getX() + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > player.getPosition().getX())
               && (position.getY() < player.getPosition().getY() + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > player.getPosition().getY());
    }
};

class Boss {
    Point position;
    float direction = 1.0f;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<Bullet> bulletVector;
    sf::Texture bulletTexture;
    bool alive = false; /// activez daca au disparut toti enemy
    float speed;
    int health;

    sf::Clock regenerationClock;
    int regenerationTime = 10;

public:
    /// constructor + destructor
    Boss() : position(0, 0), direction(1), alive(true), speed(0), health(3) { bulletVector.clear(); regenerationClock.restart(); }
    Boss(float x_, float y_, float direction_, sf::Texture& texture_, sf::Texture& bulletTexture_, bool alive_, float speed_, int health_, int regenerationTime_) : position(x_, y_), direction(direction_), sprite(texture_), texture(texture_), bulletTexture(bulletTexture_), alive(alive_), speed(speed_), health(health_), regenerationTime(regenerationTime_) { bulletVector.clear(); sprite.setPosition(x_, y_);}
    ~Boss() { std::cout << "Boss destructor\n";}

    /// getters + setters
    Point getPosition() const { return position; }
    //float getDirection() const { return direction; }
    std::vector<Bullet>& getBulletVector() { return bulletVector; }
    sf::Sprite& getSprite() { return sprite; }
    bool getAlive() const { return alive; }
    //float getSpeed() const { return speed; }
    int getHealth() const { return health; }
    //int getRegenerationTime() const { return regenerationTime; }

    void setPosition(const Point& position_) { this->position = position_; }
    //void setBulletVector(std::vector<Bullet> bulletVector) { this->bulletVector = bulletVector; }
    //void setDirection(float direction_) { this->direction = direction_; }
    void setAlive(bool alive_) { this->alive = alive_; }
    //void setSpeed(float speed_) { this->speed = speed_; }
    void setHealth(int health_) { this->health = health_; }
    //void setRegenerationTime(int regenerationTime_) { this->regenerationTime = regenerationTime_; }

    /// cc
    Boss(const Boss& other) : position{other.position}, direction{other.direction}, texture{other.texture}, bulletVector{other.bulletVector}, bulletTexture{other.bulletTexture}, alive{other.alive}, speed{other.speed}, health(other.health), regenerationTime(other.regenerationTime) {sprite.setTexture(texture); sprite.setPosition(position.getX(), position.getY());}

    /// operator=
    Boss& operator=(const Boss& other) {
        position = other.position;
        bulletVector = other.bulletVector;
        direction = other.direction;
        alive = other.alive;
        speed = other.speed;
        health = other.health;
        regenerationTime = other.regenerationTime;

        texture = other.texture;
        sprite.setTexture(other.texture);
        sprite.setPosition(other.position.getX(), other.position.getY());
        bulletTexture = other.bulletTexture;
        return *this;
    }

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Boss& boss) {
        os << "x: " << boss.position.getX() << " y: " << boss.position.getY() << " direction: " << boss.direction << "\n";
        return os;
    }

    void move() {
        if (position.getX() > SCREEN_WIDTH-ENTITY_SIZE || position.getX() < 0) {
            direction *= -1;
            position.setY(position.getY() + 1.2f * ENTITY_SIZE);
        }
        position.setX(position.getX() + direction * 2.0f);
        sprite.setPosition(position.getX(), position.getY());
    }

    void shoot() {
        bulletVector.emplace_back(position.getX() - BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
        bulletVector.emplace_back(position.getX() + BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
        bulletVector.emplace_back(position.getX() + 3*BULLET_SIZE, position.getY() + 2*BULLET_SIZE, bulletTexture);
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

    bool intersectsBullet(const Bullet& bullet) {
        return (position.getX() < bullet.getPosition().getX() + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > bullet.getPosition().getX())
               && (position.getY() < bullet.getPosition().getY() + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > bullet.getPosition().getY());
    }

    bool intersectsPlayer(const Player& player) {
        return (position.getX() < player.getPosition().getX() + BULLET_SIZE) && (position.getX() + ENTITY_SIZE > player.getPosition().getX())
               && (position.getY() < player.getPosition().getY() + BULLET_SIZE) && (position.getY() + ENTITY_SIZE > player.getPosition().getY());
    }

    void regenerate() {
        if (regenerationClock.getElapsedTime().asSeconds() > float(regenerationTime)) {
            health = std::min(3, health+1);
            regenerationClock.restart();
        }
    }
};


/*class Game {
    sf::RenderWindow window;
    Player player;
    std::vector<Enemy> enemyVector;
    sf::Clock clock;

public:
    /// constructor + destructor
    Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders") {
        sf::Texture playerTexture, bulletTexture;
        playerTexture.loadFromFile("./player.png");
        bulletTexture.loadFromFile("./bulletP.png");
        player(350, 500, playerTexture, bulletTexture, 150);
        enemyVector.clear();
        clock.restart();
    }
    Game(sf::RenderWindow window_, Player player_, std::vector<Enemy> enemyVector_) : enemyVector(enemyVector_) { window = window_; player = player_; clock.restart(); }

};*/



int main() {
#ifdef __linux__
    XInitThreads();
#endif

    /// testarea obiectelor Point
    Point p1, p2(1, 2);
    p1 = p2;
    std::cout << p1 << p2 << "\n";


    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");

    sf::Texture playerTexture, bulletTexture, enemyTexture, backgroundTexture, bossTexture, heartPTexture, heartBTexture;
    playerTexture.loadFromFile("./player.png");
    bulletTexture.loadFromFile("./bulletP.png");
    enemyTexture.loadFromFile("./enemy.png");
    backgroundTexture.loadFromFile("./background.jpg");
    bossTexture.loadFromFile("./boss.png");
    heartPTexture.loadFromFile("./heartP.png");
    heartBTexture.loadFromFile("./heartB.png");

    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);

    sf::Sprite heartP;
    heartP.setTexture(heartPTexture);
    heartP.setPosition(310, 0);

    sf::Sprite heartB1, heartB2, heartB3;
    heartB1.setTexture(heartBTexture);
    heartB1.setPosition(SCREEN_WIDTH - 50 - 100, 0);
    heartB2.setTexture(heartBTexture);
    heartB2.setPosition(SCREEN_WIDTH - 50 - 50, 0);
    heartB3.setTexture(heartBTexture);
    heartB3.setPosition(SCREEN_WIDTH - 50, 0);
    std::vector<sf::Sprite> heartBVector;
    heartBVector.push_back(heartB1); heartBVector.push_back(heartB2); heartBVector.push_back(heartB3);


    Player player(350, 500, playerTexture, bulletTexture, 250);
    Enemy first_enemy(350, 100, 1, enemyTexture, bulletTexture, true, 1);

    /// testarea obiectelor Bullet, Player, Enemy
    Bullet b1(0, 0, bulletTexture), b2;
    b2 = b1;
    std::cout << b1 << b2 << "\n";
    Player player2, player1(1, 1, playerTexture, bulletTexture, 20);
    player2 = player1;
    std::cout << player1 << "\n" << player2 << "\n";
    Enemy e1;
    e1 = first_enemy;
    std::cout << e1 << "\n";




    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(rd());
    std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH-ENTITY_SIZE);

    //enemy.setPosition(Point((float)dist(rng), 150)); /// facem random si poz
    std::vector<Enemy> enemyVector;
    enemyVector.clear();
    for (int i = 0; i < 1; i++) {
        Enemy enemy((float)((i * 1.0 * SCREEN_WIDTH) / 5.0 + (dist(rng) % (SCREEN_WIDTH / 5))*1.0), 90, 1, enemyTexture, bulletTexture, true, 1.0f);
        enemyVector.emplace_back(enemy);
    }

    for (int i = 0; i < 1; i++) {
        Enemy enemy((float)((i * 1.0 * SCREEN_WIDTH) / 5.0 + (dist(rng) % (SCREEN_WIDTH / 5))*1.0), 200, 1, enemyTexture, bulletTexture, true, 1);
        //std::cout << enemy.getPosition().getX() << " " << enemy.getPosition().getY() << "\n";
        enemyVector.emplace_back(enemy);
    }

    Boss boss(350, 100, 1, bossTexture, bulletTexture, false, 1.0f, 3, 7);

    sf::Clock clock;

    bool displayMenu = true;
    sf::Font font;
    font.loadFromFile("./retro.ttf");
    sf::Text textName("SPACE INVADERS", font, 50);
    textName.setFillColor(sf::Color::White);
    textName.setPosition((float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2 - 100);
    sf::Text textStart("Press ENTER to start", font, 30);
    textStart.setFillColor(sf::Color::White);
    textStart.setPosition((float)SCREEN_WIDTH / 2 - 250, (float)SCREEN_HEIGHT / 2 + 100);
    sf::Text textExit("Press ESC to exit", font, 20);
    textExit.setFillColor(sf::Color::White);

    sf::Text textHeartPlayer("Player lives:", font, 30);
    textHeartPlayer.setFillColor(sf::Color::White);

    sf::Text textHeartBoss("Boss lives:", font, 30);
    textHeartBoss.setFillColor(sf::Color::White);
    textHeartBoss.setPosition(SCREEN_WIDTH - 400, 0);

    sf::Text textScore("Score:", font, 30);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(0, 50);

//    sf::Text Score("0", font, 30);
//    Score.setFillColor(sf::Color::White);
//    Score.setPosition(150, 50);

    int score = 0; /// eventual variabila in Player
    int endGame = 0;
    bool transition = false;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (displayMenu) {
            window.clear(sf::Color::Black);
            window.draw(background);

            window.draw(textName);
            window.draw(textStart);
            window.draw(textExit);

            window.display();

            while (clock.getElapsedTime().asMilliseconds() < 100) {}
            clock.restart();
        }

        if (transition && !displayMenu && !endGame) {

            window.clear(sf::Color::Black);

            window.draw(background);

            sf::Text textClearedWave("GOOD JOB!", font, 50);
            textClearedWave.setFillColor(sf::Color::White);
            textClearedWave.setPosition((float)SCREEN_WIDTH / 2 - 200, (float)SCREEN_HEIGHT / 2 - 100);

            sf::Text textClearedWave1("Let's see if you can beat the final boss!", font, 30);
            textClearedWave1.setFillColor(sf::Color::White);
            textClearedWave1.setPosition((float)SCREEN_WIDTH / 2 - 450, (float)SCREEN_HEIGHT / 2 + 100);

            sf::Text textClearedWave2("Press ENTER to continue!", font, 30);
            textClearedWave2.setFillColor(sf::Color::White);
            textClearedWave2.setPosition((float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2 + 200);

            window.draw(textClearedWave);
            window.draw(textClearedWave1);
            window.draw(textClearedWave2);

            window.display();

            std::vector<Bullet>& playerBullet1 = player.getBulletVector();
            playerBullet1.clear();

            while (clock.getElapsedTime().asMilliseconds() < 10) {}
            clock.restart();

            //transition = false;
        }

        if (endGame != 0) {
            if (endGame == 1) {
                window.clear(sf::Color::Black);
                window.draw(background);

                sf::Text textWin("YOU WIN!", font, 50);
                textWin.setFillColor(sf::Color::White);
                textWin.setPosition((float)SCREEN_WIDTH / 2 - 200, (float)SCREEN_HEIGHT / 2 - 100);

                sf::Text textWinScore("You have " + std::to_string(score) + " points!", font, 30);
                textWinScore.setFillColor(sf::Color::White);
                textWinScore.setPosition((float)SCREEN_WIDTH / 2 - 250, (float)SCREEN_HEIGHT / 2 + 100);

                window.draw(textWin);
                window.draw(textWinScore);

                window.display();

                while (clock.getElapsedTime().asMilliseconds() < 100) {}
                clock.restart();

            }
            else {
                window.clear(sf::Color::Black);
                window.draw(background);

                sf::Text textLose("Game Over:(", font, 50);
                textLose.setFillColor(sf::Color::White);
                textLose.setPosition((float)SCREEN_WIDTH / 2 - 250, (float)SCREEN_HEIGHT / 2 - 100);

                sf::Text textLoseScore("You have " + std::to_string(score) + " points!", font, 30);
                textLoseScore.setFillColor(sf::Color::White);
                textLoseScore.setPosition((float)SCREEN_WIDTH / 2 - 250, (float)SCREEN_HEIGHT / 2 + 100);

                window.draw(textLose);
                window.draw(textLoseScore);

                window.display();

                while (clock.getElapsedTime().asMilliseconds() < 100) {}
                clock.restart();

            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        else
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                displayMenu = false;
                transition = false;
            }
            else
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    player.move(0);
                else
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        player.move(1);
                    else
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                            player.shoot();


        if (displayMenu)
            continue;

        if (transition && !displayMenu && !endGame)
            continue;

        if (endGame != 0)
            continue;


        std::vector<Bullet>& playerBullet = player.getBulletVector();
        player.moveBullets();


        /// de facut pentru mai multi inamici

        if (!boss.getAlive())
            for (auto& enemy : enemyVector) {
                if (enemy.getAlive()) {
                    enemy.move();
                    if (dist(rng) % 200 < 1)
                        enemy.shoot();
                }
                enemy.moveBullets();

            }

        if (boss.getAlive()) {
            transition = false;
            boss.move();
            if (dist(rng) % 200 < 3)
                boss.shoot();
            boss.moveBullets();

            boss.regenerate();
        }

        for (auto itBullet=playerBullet.begin(); itBullet != playerBullet.end(); itBullet++) {
            for (auto& enemy : enemyVector) {
                if (!enemy.getAlive())
                    continue;
                if (enemy.intersectsBullet(*itBullet)) {
                    playerBullet.erase(itBullet);
                    enemy.setAlive(false);
                    score += ENEMY_POINTS;
                    //std::cout << enemy << "\n";
                }
            }
        }

        if (boss.getAlive())
            for (auto itBullet=playerBullet.begin(); itBullet != playerBullet.end(); itBullet++)
                if (boss.intersectsBullet(*itBullet)) {
                    playerBullet.erase(itBullet);
                    boss.setHealth(boss.getHealth() - 1);
                    score += BOSS_POINTS/3;
                    if (boss.getHealth() <= 0) {
                        boss.setAlive(false);
                        score += BOSS_POINTS;

                        endGame = 1;
                        transition = false;


                        //std::cout << "You Win!\n";
                        //window.close();
                        //return 0;
                    }
                }

        //enemyVector.erase(std::remove_if(enemyVector.begin(), enemyVector.end(), [](const Enemy& enemy) { return !enemy.getAlive(); }), enemyVector.end());

        int areEnemies = 0;
        for (auto& enemy : enemyVector)
            if (enemy.getAlive())
                areEnemies = 1;

        if (!areEnemies && !boss.getAlive()){
            //std::cout << "Good job!\n";
            //std::cout << "Let's see if you can beat the final boss!\n";

            transition = true;

            boss.setAlive(true);
        }

        for (auto& enemy : enemyVector) {
            if (!enemy.getAlive())
                continue;
            if (enemy.intersectsPlayer(player)) {
                //std::cout << "Game Over:(\n";
                //window.close();
                //return 0;

                endGame = -1;
                transition = false;
                break;
            }
            std::vector<Bullet>& enemyBullet = enemy.getBulletVector();
            for (auto& bullet : enemyBullet) {
                if (player.intersectsBullet(bullet)) {
                    //enemyBullet.pop_back();
                    //std::cout << "Game Over:(\n";
                    //window.close();
                    //return 0;

                    endGame = -1;
                    transition = false;
                    break;
                }
            }
        }

        if (boss.getAlive()) {
            if (boss.intersectsPlayer(player)) {
                //std::cout << "Game Over:(\n";
                //window.close();
                //return 0;

                endGame = -1;
                transition = false;
            }
            for (auto &bullet: boss.getBulletVector())
                if (player.intersectsBullet(bullet)) {
                    //enemyBullet.pop_back();
                    //std::cout << "Game Over:(\n";
                    //window.close();
                    //return 0;

                    endGame = -1;
                    transition = false;
                    break;
                }
        }

        window.clear(sf::Color::Black);

        window.draw(background);

        //window.draw(sprite);
        window.draw(player.getSprite());
        window.draw(textHeartPlayer);
        window.draw(heartP);
        window.draw(textScore);
        sf::Text Score(std::to_string(score), font, 30);
        Score.setFillColor(sf::Color::White);
        Score.setPosition(150, 50);
        window.draw(Score);


        if (boss.getAlive()) {
            window.draw(boss.getSprite());
            window.draw(textHeartBoss);
            for (int i = 0; i < boss.getHealth(); i++)
                window.draw(heartBVector[i]);
        }

        for (auto& enemy : enemyVector) {
            if (!enemy.getAlive())
                continue;
            window.draw(enemy.getSprite());
        }
        //window.draw(enemy.getSprite());
        for (const Bullet& bullet : playerBullet)
            window.draw(bullet.getSprite());

        if (boss.getAlive())
            for (const Bullet& bullet : boss.getBulletVector())
                window.draw(bullet.getSprite());

        if (!boss.getAlive())
            for (auto& enemy : enemyVector) {
                std::vector<Bullet>& enemyBullet = enemy.getBulletVector();
                for (const Bullet& bullet : enemyBullet)
                    window.draw(bullet.getSprite());
            }

        window.display();

        while (clock.getElapsedTime().asMilliseconds() < 10) {}
        clock.restart();
    }

    /*while (window.isOpen()) {
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


        /// de facut pentru mai multi inamici

        for (auto& enemy : enemyVector) {
            if (enemy.getAlive()) {
                enemy.move();
                if (dist(rng) % 200 < 1)
                    enemy.shoot();
            }
            enemy.moveBullets();

        }

        for (auto& bullet : playerBullet) {
            for (auto& enemy : enemyVector) {
                if (!enemy.getAlive())
                    continue;
                if (enemy.intersects(bullet)) {
                    playerBullet.pop_back();
                    enemy.setAlive(false);
                    //std::cout << enemy << "\n";
                }
            }
        }
        //enemyVector.erase(std::remove_if(enemyVector.begin(), enemyVector.end(), [](const Enemy& enemy) { return !enemy.getAlive(); }), enemyVector.end());

        int areEnemies = 0;
        for (auto& enemy : enemyVector) {
            if (enemy.getAlive()) {
                areEnemies = 1;
            }
        }

        if (!areEnemies){
            std::cout << enemyVector.begin()->getPosition() << "\n";
            std::cout << "You Win!\n";
            window.close();
            return 0;
        }

        for (auto& enemy : enemyVector) {
            std::vector<Bullet>& enemyBullet = enemy.getBulletVector();
            for (auto& bullet : enemyBullet) {
                if (player.intersects(bullet)) {
                    //enemyBullet.pop_back();
                    std::cout << "Game Over:(\n";
                    window.close();
                    return 0;
                }
            }
        }


        window.clear(sf::Color::Black);

        //window.draw(sprite);
        window.draw(player.getSprite());

        for (auto& enemy : enemyVector) {
            if (!enemy.getAlive())
                continue;
            window.draw(enemy.getSprite());
        }
        //window.draw(enemy.getSprite());
        for (const Bullet& bullet : playerBullet)
            window.draw(bullet.getSprite());

        for (auto& enemy : enemyVector) {
            std::vector<Bullet>& enemyBullet = enemy.getBulletVector();
            for (const Bullet& bullet : enemyBullet)
                window.draw(bullet.getSprite());
        }

        window.display();

        while (clock.getElapsedTime().asMilliseconds() < 10) {}
        clock.restart();
        //std::this_thread::sleep_for(std::chrono::microseconds (990));
        //std::this_thread::sleep_for(std::chrono::duration<double, std::milli> (0.9));
        //std::this_thread::sleep_for(std::chrono::milliseconds (10));
        //std::this_thread::sleep_for(std::chrono::microseconds (900));
    }*/

    return 0;
}