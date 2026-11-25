#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include "EnemyState.hpp"

enum class TypeEnemy: uint8_t {
    Striker = 0,
    Steamer = 1,
};

struct Enemy
{
    sf::FloatRect hitbox;
    sf::Vector2f position;
    EnemyState state;
    float health;
    TypeEnemy type;

    int currentFrame; 
    sf::Texture texture;       
    sf::Sprite sprite;

    sf::Vector2f velocity = {0.f, 0.f};
    float gravity = 0.f;

    bool isSeenPlayer;
    bool canStrike;
};
