#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include "Point.h"
#include "Bullet.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Exceptions.h"

const int ENEMY_POINTS = 20;
const int BOSS_POINTS = 90;

class Game {
    //sf::RenderWindow window;
    std::shared_ptr<sf::RenderWindow> window;
    sf::Clock clock;

    static std::random_device rd;
    static std::mt19937 rng;
    static std::uniform_int_distribution<int> dist;

    Player player;
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

    Game(std::shared_ptr<sf::RenderWindow> window_, Player player_,  std::vector<std::shared_ptr<Entity>> enemyVector_, std::shared_ptr<Entity> boss_);

public:
    /// constructor + destructor
    ~Game();

    static Game &getInstance(std::shared_ptr<sf::RenderWindow> window_, Player player_,  std::vector<std::shared_ptr<Entity>> enemyVector_, std::shared_ptr<Entity> boss_);


    /// getters + setters
    /// cc
    Game(const Game& other) = delete;


    friend void swap(Game &game1, Game &game2);

    /// operator=
    Game &operator=(Game other) = delete;

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Game& game);

    /// metode
    /// run

    static void initRandom();

    void processEvents();


    void render();

    void displayGameMenu();

    void displayGameTransition();

    void displayGameEnd();

    void update();

    /// de facut initializarea in constructor, cu try catch
    void run();
};

