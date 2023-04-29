#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
//#include <chrono>
//#include <thread>
//#include <memory>
//#include <utility>

//#include "Point.h"
#include "Bullet.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

const int ENEMY_POINTS = 20;
const int BOSS_POINTS = 90;

/// window ca atribut
/// texturi ca atribut

/// exceptii in constructor si la dynamic_cast
class Game {
    //sf::RenderWindow window;
    std::shared_ptr<sf::RenderWindow> window;
    sf::Clock clock;

    std::shared_ptr<Entity> player;
    std::vector<std::shared_ptr<Entity>> enemyVector;
    std::shared_ptr<Entity> boss;

    //sf::Texture playerTexture, bulletTexture, enemyTexture, bossTexture;
    sf::Texture backgroundTexture, heartPTexture, heartBTexture;

    sf::Sprite background, heartP;
    std::vector<sf::Sprite> heartBVector;

    sf::Text textHeartPlayer, textScore, textHeartBoss, textName, textStart, textExit;

    sf::Font font;

    bool displayMenu = true;
    bool transition = false;
    int endGame = 0;

public:
    /// constructor + destructor
    Game(std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<Entity> player_,  std::vector<std::shared_ptr<Entity>> enemyVector_, std::shared_ptr<Entity> boss_) : window(std::move(window_)), player(std::move(player_)), enemyVector(std::move(enemyVector_)), boss(std::move(boss_)), displayMenu(true), transition(false), endGame(0) {
        /// sau creez pointerii in main si ii dau ca parametrii ai constructorului
        //window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");

        //playerTexture.loadFromFile("./player.png");
        //bulletTexture.loadFromFile("./bulletP.png");
        //enemyTexture.loadFromFile("./enemy.png");
        backgroundTexture.loadFromFile("./background.jpg");
        //bossTexture.loadFromFile("./boss.png");
        heartPTexture.loadFromFile("./heartP.png");
        heartBTexture.loadFromFile("./heartB.png");

        background.setTexture(backgroundTexture);
        background.setPosition(0, 0);

        heartP.setTexture(heartPTexture);
        heartP.setPosition(310, 0);

        sf::Sprite heartB1, heartB2, heartB3;
        heartB1.setTexture(heartBTexture);
        heartB1.setPosition(SCREEN_WIDTH - 50 - 100, 0);
        heartB2.setTexture(heartBTexture);
        heartB2.setPosition(SCREEN_WIDTH - 50 - 50, 0);
        heartB3.setTexture(heartBTexture);
        heartB3.setPosition(SCREEN_WIDTH - 50, 0);
        heartBVector.push_back(heartB1); heartBVector.push_back(heartB2); heartBVector.push_back(heartB3);


//        std::random_device rd;
//        std::mt19937 rng(rd());
//        rng.seed(rd());
//        std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH-ENTITY_SIZE);

        //enemy.setPosition(Point((float)dist(rng), 150)); /// facem random si poz
        /*Player player(350, 500, playerTexture, bulletTexture, 250);
        std::vector<Enemy> enemyVector;
        enemyVector.clear();
        for (int i = 0; i < 1; i++) {
            Enemy enemy((float)((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3))*1.0), 90, 1, enemyTexture, bulletTexture, true, 1.0f);
            enemyVector.emplace_back(enemy);
        }

        for (int i = 0; i < 1; i++) {
            Enemy enemy((float)((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3))*1.0), 200, 1, enemyTexture, bulletTexture, true, 1);
            enemyVector.emplace_back(enemy);
        }

        Boss boss(350, 100, 1, bossTexture, bulletTexture, false, 1.0f, 3, 7);*/

        font.loadFromFile("./retro.ttf");
        //textName("SPACE INVADERS", font, 50);
        textName.setString("SPACE INVADERS");
        textName.setFont(font);
        textName.setCharacterSize(50);
        textName.setFillColor(sf::Color::White);
        textName.setPosition((float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2 - 100);
        //sf::Text textStart("Press ENTER to start", font, 30);
        textStart.setString("Press ENTER to start");
        textStart.setFont(font);
        textStart.setCharacterSize(30);
        textStart.setFillColor(sf::Color::White);
        textStart.setPosition((float)SCREEN_WIDTH / 2 - 250, (float)SCREEN_HEIGHT / 2 + 100);
        //sf::Text textExit("Press ESC to exit", font, 20);
        textExit.setString("Press ESC to exit");
        textExit.setFont(font);
        textExit.setCharacterSize(20);
        textExit.setFillColor(sf::Color::White);

        //sf::Text textHeartPlayer("Player lives:", font, 30);
        textHeartPlayer.setString("Player lives:");
        textHeartPlayer.setFont(font);
        textHeartPlayer.setCharacterSize(30);
        textHeartPlayer.setFillColor(sf::Color::White);

        //sf::Text textHeartBoss("Boss lives:", font, 30);
        textHeartBoss.setString("Boss lives:");
        textHeartBoss.setFont(font);
        textHeartBoss.setCharacterSize(30);
        textHeartBoss.setFillColor(sf::Color::White);
        textHeartBoss.setPosition(SCREEN_WIDTH - 400, 0);

        //sf::Text textScore("Score:", font, 30);
        textScore.setString("Score:");
        textScore.setFont(font);
        textScore.setCharacterSize(30);
        textScore.setFillColor(sf::Color::White);
        textScore.setPosition(0, 50);

    }
    ~Game() {
        window->close();
    }


    /// getters + setters
    /// cc
    Game(const Game& other) : window(other.window), clock(other.clock),
    backgroundTexture(other.backgroundTexture), heartPTexture(other.heartPTexture),
    heartBTexture(other.heartBTexture), background(other.background), heartP(other.heartP), heartBVector(other.heartBVector),
    textHeartPlayer(other.textHeartPlayer), textScore(other.textScore), textHeartBoss(other.textHeartBoss), textName(other.textName),
    textStart(other.textStart), textExit(other.textExit), font(other.font), displayMenu(other.displayMenu),
    transition(other.transition),endGame(other.endGame) {
        //player = std::dynamic_pointer_cast<Player>(other.player->clone());
        player = other.player->clone();
        for (const auto& enemy : other.enemyVector)
            enemyVector.push_back(enemy->clone());
        boss = other.boss->clone();

    }


    friend void swap(Game &game1, Game &game2) {
        std::swap(game1.window, game2.window);
        std::swap(game1.clock, game2.clock);
        //std::swap(game1.playerTexture, game2.playerTexture);
        //std::swap(game1.bulletTexture, game2.bulletTexture);
        //std::swap(game1.enemyTexture, game2.enemyTexture);
        std::swap(game1.backgroundTexture, game2.backgroundTexture);
        //std::swap(game1.bossTexture, game2.bossTexture);
        std::swap(game1.heartPTexture, game2.heartPTexture);
        std::swap(game1.heartBTexture, game2.heartBTexture);
        std::swap(game1.background, game2.background);
        std::swap(game1.heartP, game2.heartP);
        std::swap(game1.heartBVector, game2.heartBVector);
        std::swap(game1.textHeartPlayer, game2.textHeartPlayer);
        std::swap(game1.textScore, game2.textScore);
        std::swap(game1.textHeartBoss, game2.textHeartBoss);
        std::swap(game1.textName, game2.textName);
        std::swap(game1.textStart, game2.textStart);
        std::swap(game1.textExit, game2.textExit);
        std::swap(game1.font, game2.font);
        std::swap(game1.displayMenu, game2.displayMenu);
        std::swap(game1.transition, game2.transition);
        std::swap(game1.endGame, game2.endGame);
        std::swap(game1.player, game2.player);
        std::swap(game1.enemyVector, game2.enemyVector);
        std::swap(game1.boss, game2.boss);
    }

    /// operator=
    Game &operator=(Game other) {
        swap(*this, other);
        return *this;
    }

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Game& game) {
        os << "Game:\n";
        os << game.player;
        for (const auto& enemy : game.enemyVector)
            os << *enemy;
        os << game.boss;
        return os;
    }

    /// metode
    /// run

    void processEvents() {

        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();
        else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            displayMenu = false;
            transition = false;
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player->move(0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player->move(1);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                player->shoot();
        }

    }


    void render() {

        window->clear(sf::Color::Black);

        window->draw(background);

        //window.draw(sprite);
        window->draw(player->getSprite());
        window->draw(textHeartPlayer);
        window->draw(heartP);
        window->draw(textScore);
        if (auto* playerPtr = dynamic_cast<Player*>(player.get())) {
            sf::Text Score(std::to_string(playerPtr->getScore()), font, 30);
            Score.setFillColor(sf::Color::White);
            Score.setPosition(150, 50);
            window->draw(Score);
        }


        if (boss->getAlive()) {
            window->draw(boss->getSprite());
            window->draw(textHeartBoss);
            for (int i = 0; i < boss->getHealth(); i++)
                window->draw(heartBVector[i]);
        }

        for (auto& enemy : enemyVector) {
            if (!enemy->getAlive())
                continue;
            window->draw(enemy->getSprite());
        }
        //window.draw(enemy.getSprite());
        for (const Bullet& bullet : player->getBulletVector())
            window->draw(bullet.getSprite());

        if (boss->getAlive())
            for (const Bullet& bullet : boss->getBulletVector())
                window->draw(bullet.getSprite());

        if (!boss->getAlive())
            for (auto& enemy : enemyVector) {
                std::vector<Bullet>& enemyBullet = enemy->getBulletVector();
                for (const Bullet& bullet : enemyBullet)
                    window->draw(bullet.getSprite());
            }

        window->display();

        while (clock.getElapsedTime().asMilliseconds() < 10) {}
        clock.restart();
    }

    void displayGameMenu() {

        window->clear(sf::Color::Black);
        window->draw(background);

        window->draw(textName);
        window->draw(textStart);
        window->draw(textExit);

        window->display();

        while (clock.getElapsedTime().asMilliseconds() < 100) {}
        clock.restart();

    }

    void displayGameTransition() {

        window->clear(sf::Color::Black);

        window->draw(background);

        sf::Text textClearedWave("GOOD JOB!", font, 50);
        textClearedWave.setFillColor(sf::Color::White);
        textClearedWave.setPosition((float)SCREEN_WIDTH / 2 - 200, (float)SCREEN_HEIGHT / 2 - 100);

        sf::Text textClearedWave1("Let's see if you can beat the final boss!", font, 30);
        textClearedWave1.setFillColor(sf::Color::White);
        textClearedWave1.setPosition((float)SCREEN_WIDTH / 2 - 450, (float)SCREEN_HEIGHT / 2 + 100);

        sf::Text textClearedWave2("Press ENTER to continue!", font, 30);
        textClearedWave2.setFillColor(sf::Color::White);
        textClearedWave2.setPosition((float)SCREEN_WIDTH / 2 - 300, (float)SCREEN_HEIGHT / 2 + 200);

        window->draw(textClearedWave);
        window->draw(textClearedWave1);
        window->draw(textClearedWave2);

        window->display();

        std::vector<Bullet>& playerBullet1 = player->getBulletVector();
        playerBullet1.clear();

        while (clock.getElapsedTime().asMilliseconds() < 10) {}
        clock.restart();

    }

    void displayGameEnd() {

        window->clear(sf::Color::Black);
        window->draw(background);


        if (endGame == 1) {

            sf::Text textWin("YOU WIN!", font, 50);
            textWin.setFillColor(sf::Color::White);
            textWin.setPosition((float)SCREEN_WIDTH / 2 - 200, (float)SCREEN_HEIGHT / 2 - 100);

            window->draw(textWin);
        }
        else {

            sf::Text textLose("Game Over:(", font, 50);
            textLose.setFillColor(sf::Color::White);
            textLose.setPosition((float)SCREEN_WIDTH / 2 - 250, (float)SCREEN_HEIGHT / 2 - 100);

            window->draw(textLose);
        }

        if (auto* playerPtr = dynamic_cast<Player*>(player.get())) {
            sf::Text textFinalScore("You have " + std::to_string(playerPtr->getScore()) + " points!", font, 30);
            textFinalScore.setFillColor(sf::Color::White);
            textFinalScore.setPosition((float)SCREEN_WIDTH / 2 - 250, (float)SCREEN_HEIGHT / 2 + 100);

            window->draw(textFinalScore);
        }

        window->display();

        while (clock.getElapsedTime().asMilliseconds() < 100) {}
        clock.restart();

    }

    void update() {

        std::random_device rd;
        std::mt19937 rng(rd());
        rng.seed(rd());
        std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH-ENTITY_SIZE);

        std::vector<Bullet>& playerBullet = player->getBulletVector();
        player->moveBullets();


        if (!boss->getAlive())
            for (auto& enemy : enemyVector) {
                if (enemy->getAlive()) {
                    enemy->move();
                    if (dist(rng) % 200 < 1)
                        enemy->shoot();
                }
                enemy->moveBullets();

            }

        if (boss->getAlive()) {
            transition = false;
            boss->move();
            if (dist(rng) % 200 < 3)
                boss->shoot();
            boss->moveBullets();

            if (boss->getHealth() < 3) {
                if (auto* bossPtr = dynamic_cast<Boss*>(boss.get()))
                    bossPtr->regenerate();
            }
                //boss.regenerate();
        }

        for (auto& enemy : enemyVector) {
            if (!enemy->getAlive())
                continue;
            for (auto itBullet=playerBullet.begin(); itBullet != playerBullet.end(); ) {
                if (enemy->intersectsBullet(*itBullet)) {
                    itBullet = playerBullet.erase(itBullet);
                    enemy->setAlive(false);
                    Enemy::downEnemyCount();
                    if (auto* playerPtr = dynamic_cast<Player*>(player.get()))
                        playerPtr->setScore(playerPtr->getScore() + ENEMY_POINTS);
                    //player.setScore(player.getScore() + ENEMY_POINTS);
                    //score += ENEMY_POINTS;
                }
                else
                    itBullet++;
            }
        }

        if (boss->getAlive())
            for (auto itBullet=playerBullet.begin(); itBullet != playerBullet.end(); ) {
                if (boss->intersectsBullet(*itBullet)) {
                    itBullet = playerBullet.erase(itBullet);
                    boss->setHealth(boss->getHealth() - 1);
                    if (auto* playerPtr = dynamic_cast<Player*>(player.get()))
                        playerPtr->setScore(playerPtr->getScore() + BOSS_POINTS / 3);
                    //player.setScore(player.getScore() + BOSS_POINTS / 3);
                    //score += BOSS_POINTS / 3;
                    if (boss->getHealth() <= 0) {
                        boss->setAlive(false);
                        if (auto* playerPtr = dynamic_cast<Player*>(player.get()))
                            playerPtr->setScore(playerPtr->getScore() + BOSS_POINTS);
                        //player.setScore(player.getScore() + BOSS_POINTS);
                        //score += BOSS_POINTS;

                        endGame = 1;
                        transition = false;

                    }
                } else
                    itBullet++;
            }
        //enemyVector.erase(std::remove_if(enemyVector.begin(), enemyVector.end(), [](const Enemy& enemy) { return !enemy.getAlive(); }), enemyVector.end());

        if (!Enemy::getEnemyCount() && !boss->getAlive()){
            transition = true;

            boss->setAlive(true);
        }

        for (auto& enemy : enemyVector) {
            if (!enemy->getAlive())
                continue;
            if (enemy->intersectsEntity(*player)) {
                endGame = -1;
                transition = false;
                break;
            }
            std::vector<Bullet>& enemyBullet = enemy->getBulletVector();
            for (auto& bullet : enemyBullet) {
                if (player->intersectsBullet(bullet)) {
                    endGame = -1;
                    transition = false;
                    break;
                }
            }
        }

        if (boss->getAlive()) {
            if (boss->intersectsEntity(*player)) {
                endGame = -1;
                transition = false;
            }
            for (auto &bullet: boss->getBulletVector())
                if (player->intersectsBullet(bullet)) {
                    endGame = -1;
                    transition = false;
                    break;
                }
        }

    }

    /// de facut initializarea in constructor, cu try catch
    void run() {

        while (window->isOpen()) {
            processEvents();

            if (displayMenu)
                displayGameMenu();
            if (transition && !endGame)
                displayGameTransition();
            if (endGame != 0)
                displayGameEnd();

            if (displayMenu)
                continue;
            if (transition && !endGame)
                continue;
            if (endGame != 0)
                continue;

            update();

            render();
        }

    }

};


int main() {
#ifdef __linux__
    XInitThreads();
#endif

    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(rd());
    std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH-ENTITY_SIZE);

    //sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");

    sf::Texture playerTexture, enemyTexture, bossTexture, bulletTexture;
    playerTexture.loadFromFile("player.png");
    enemyTexture.loadFromFile("enemy.png");
    bossTexture.loadFromFile("boss.png");
    bulletTexture.loadFromFile("bulletP.png");

    std::vector<std::shared_ptr<Entity>> enemyVector;
    for (int i = 0; i < 1; i++)
        enemyVector.emplace_back(Enemy{(float)((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3))*1.0), 90, 1, enemyTexture, bulletTexture, true, 1.0f}.clone());

    for (int i = 0; i < 1; i++)
        enemyVector.emplace_back(Enemy{(float)((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3))*1.0), 200, 1, enemyTexture, bulletTexture, true, 1}.clone());

    std::shared_ptr<Entity> player = Player{350, 500, playerTexture, bulletTexture, 250}.clone();
    std::shared_ptr<Entity> boss = Boss{350, 100, 1, bossTexture, bulletTexture, false, 1.0f, 3, 7}.clone();

    Game game(window, player, enemyVector, boss);

    game.run();

    /// cc, op=, destr definite manual
    /// inainte = default, puse protected

    /*sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");

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


    std::random_device rd;
    std::mt19937 rng(rd());
    rng.seed(rd());
    std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH-ENTITY_SIZE);

    //enemy.setPosition(Point((float)dist(rng), 150)); /// facem random si poz
    std::vector<Enemy> enemyVector;
    enemyVector.clear();
    for (int i = 0; i < 1; i++) {
        Enemy enemy((float)((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3))*1.0), 90, 1, enemyTexture, bulletTexture, true, 1.0f);
        enemyVector.emplace_back(enemy);
    }

    for (int i = 0; i < 1; i++) {
        Enemy enemy((float)((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3))*1.0), 200, 1, enemyTexture, bulletTexture, true, 1);
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

    int endGame = 0;
    bool transition = false;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        else
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                displayMenu = false;
                transition = false;
            }
            else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    player.move(0);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    player.move(1);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    player.shoot();
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

        if (transition && !endGame) {

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

                sf::Text textWinScore("You have " + std::to_string(player.getScore()) + " points!", font, 30);
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

                sf::Text textLoseScore("You have " + std::to_string(player.getScore()) + " points!", font, 30);
                textLoseScore.setFillColor(sf::Color::White);
                textLoseScore.setPosition((float)SCREEN_WIDTH / 2 - 250, (float)SCREEN_HEIGHT / 2 + 100);

                window.draw(textLose);
                window.draw(textLoseScore);

                window.display();

                while (clock.getElapsedTime().asMilliseconds() < 100) {}
                clock.restart();

            }

        }

        if (displayMenu)
            continue;

        if (transition && !endGame)
            continue;

        if (endGame != 0)
            continue;


        std::vector<Bullet>& playerBullet = player.getBulletVector();
        player.moveBullets();


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

            if (boss.getHealth() < 3)
                boss.regenerate();
        }

        for (auto& enemy : enemyVector) {
            if (!enemy.getAlive())
                continue;
            for (auto itBullet=playerBullet.begin(); itBullet != playerBullet.end(); ) {
                if (enemy.intersectsBullet(*itBullet)) {
                    itBullet = playerBullet.erase(itBullet);
                    enemy.setAlive(false);
                    Enemy::downEnemyCount();
                    player.setScore(player.getScore() + ENEMY_POINTS);
                    //score += ENEMY_POINTS;
                }
                else
                    itBullet++;
            }
        }

        if (boss.getAlive())
            for (auto itBullet=playerBullet.begin(); itBullet != playerBullet.end(); ) {
                if (boss.intersectsBullet(*itBullet)) {
                    itBullet = playerBullet.erase(itBullet);
                    boss.setHealth(boss.getHealth() - 1);
                    player.setScore(player.getScore() + BOSS_POINTS / 3);
                    //score += BOSS_POINTS / 3;
                    if (boss.getHealth() <= 0) {
                        boss.setAlive(false);
                        player.setScore(player.getScore() + BOSS_POINTS);
                        //score += BOSS_POINTS;

                        endGame = 1;
                        transition = false;

                    }
                } else
                    itBullet++;
            }
        //enemyVector.erase(std::remove_if(enemyVector.begin(), enemyVector.end(), [](const Enemy& enemy) { return !enemy.getAlive(); }), enemyVector.end());

        if (!Enemy::getEnemyCount() && !boss.getAlive()){
            transition = true;

            boss.setAlive(true);
        }

        for (auto& enemy : enemyVector) {
            if (!enemy.getAlive())
                continue;
            if (enemy.intersectsEntity(player)) {
                endGame = -1;
                transition = false;
                break;
            }
            std::vector<Bullet>& enemyBullet = enemy.getBulletVector();
            for (auto& bullet : enemyBullet) {
                if (player.intersectsBullet(bullet)) {
                    endGame = -1;
                    transition = false;
                    break;
                }
            }
        }

        if (boss.getAlive()) {
            if (boss.intersectsEntity(player)) {
                endGame = -1;
                transition = false;
            }
            for (auto &bullet: boss.getBulletVector())
                if (player.intersectsBullet(bullet)) {
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
        sf::Text Score(std::to_string(player.getScore()), font, 30);
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
        //window.draw(enemy1.getSprite());
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
        //std::this_thread::sleep_for(std::chrono::microseconds (990));
        //std::this_thread::sleep_for(std::chrono::duration<double, std::milli> (0.9));
        //std::this_thread::sleep_for(std::chrono::milliseconds (10));
        //std::this_thread::sleep_for(std::chrono::microseconds (900));
    }*/

    return 0;
}