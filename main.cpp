#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
#include <vector>
#include <random>

#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Game.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif


int main() {
#ifdef __linux__
    XInitThreads();
#endif

    try {
        std::random_device rd;
        std::mt19937 rng(rd());
        rng.seed(rd());
        std::uniform_int_distribution<int> dist(0, SCREEN_WIDTH - ENTITY_SIZE);

        //sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");
        std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
                sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders");

        sf::Texture playerTexture, enemyTexture, bossTexture, bulletTexture;
        playerTexture.loadFromFile("player.png");
        enemyTexture.loadFromFile("enemy.png");
        bossTexture.loadFromFile("boss.png");
        bulletTexture.loadFromFile("bulletP.png");

        std::vector<std::shared_ptr<Entity>> enemyVector;
        for (int i = 0; i < 1; i++)
            enemyVector.emplace_back(
                    Enemy{(float) ((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3)) * 1.0), 90, 1,
                          enemyTexture, bulletTexture, true, 1.0f}.clone());

        for (int i = 0; i < 1; i++)
            enemyVector.emplace_back(
                    Enemy{(float) ((i * 1.0 * SCREEN_WIDTH) / 3.0 + (dist(rng) % (SCREEN_WIDTH / 3)) * 1.0), 200, 1,
                          enemyTexture, bulletTexture, true, 1}.clone());

        std::shared_ptr<Entity> player = Player{350, 500, playerTexture, bulletTexture, 250}.clone();
        std::shared_ptr<Entity> boss = Boss{350, 100, 1, bossTexture, bulletTexture, false, 1.0f, 3, 7}.clone();

        Game game(window, player, enemyVector, boss);
        Game game2(game);

        game.run();
    }
    catch (const entityError &err) {
        std::cout << "Entity error: " << err.what() << "\n";
    }
    catch (const textureError &err) {
        std::cout << "Texture error: " << err.what() << "\n";
    }
    catch (const fontError &err) {
        std::cout << "Font error: " << err.what() << "\n";
    }
    catch (const appError &err) {
        std::cout << err.what() << "\n";
    }

    return 0;
}