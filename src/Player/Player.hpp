#pragma once 

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <algorithm>

struct Player {
    sf::FloatRect hitbox;
    sf::Texture texture;        
    sf::Sprite sprite;
    sf::Vector2f velocity = {0.f, 0.f};
    float gravity = 0.f;
    bool isGround = true;
    int countJerk = 2;
    float jerkTimer = 0.f;

    float health = 0.f;

    Player();
    void Update(sf::RenderWindow &window, const float dt);
    void UpdateHitbox();
    void Draw(sf::RenderWindow &window) const;
    void Jump(const sf::Event::KeyPressed* pressedKey);
    void Jerk(const sf::Event::KeyPressed* pressedKey);
};
