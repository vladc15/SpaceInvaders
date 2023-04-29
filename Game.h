#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include "Point.h"
#include "Bullet.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

const int ENEMY_POINTS = 20;
const int BOSS_POINTS = 90;

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
    Game(std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<Entity> player_,  std::vector<std::shared_ptr<Entity>> enemyVector_, std::shared_ptr<Entity> boss_);
    ~Game();


    /// getters + setters
    /// cc
    Game(const Game& other);


    friend void swap(Game &game1, Game &game2);

    /// operator=
    Game &operator=(Game other);

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Game& game);

    /// metode
    /// run

    void processEvents();


    void render();

    void displayGameMenu();

    void displayGameTransition();

    void displayGameEnd();

    void update();

    /// de facut initializarea in constructor, cu try catch
    void run();
};

