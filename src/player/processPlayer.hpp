#pragma once 

#include <SFML/Graphics.hpp>

namespace Player
{
    struct Element {
        std::unique_ptr<sf::Shape> shape = nullptr;
        Shape::parametersShape parameters;
    };

    struct Player {
        std::vector<Element> body;
        sf::Vector2f speed = {0.f, 0.f};
        sf::Vector2f direction = {0.f, 0.f};
        float maxSpeed = 0.f;
        int countJerk = 2;
        float jerkTimer = 0.f;
        bool altPressed = false;
        bool isGround = true;
        float acceleration = 0.f;
        float friction = 0.f;
        float gravity = 0.f;
    };

    void playerInit(Player& player) ;
    void playerUpdate(Player& player, const float dt, const sf::RenderWindow &window);
    void playerJump(Player& player, const sf::Event::KeyPressed* pressedKey);
    void playerJerk(Player& player, const sf::Event::KeyPressed* pressedKey, const float dt);
}