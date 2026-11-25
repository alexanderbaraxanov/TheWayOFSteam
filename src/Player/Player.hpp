#pragma once 

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <algorithm>
#include "../Map/Map.hpp"
#include "./PlayerState.hpp"
#include "../SoundManager/Sounds.hpp"

class Game;

constexpr int FRAME_PLAYER_WIDTH = 80;
constexpr int FRAME_PLAYER_HEIGHT = 112;

constexpr float ACCELERATION = 2000.f;
constexpr float MAX_SPEED = 600.f;
constexpr float FRICTION = 0.5f;

constexpr float POWER_JUMP = -600.f;
constexpr float GRAVITY_UP = 1200.f;
constexpr float GRAVITY_DOWN = 1000.f;

struct Player {
    sf::FloatRect hitbox;
    PlayerState state;
    float health = 0.f;

    int currentFrame;       
    sf::Sprite sprite;

    SoundBank sounds;

    sf::Vector2f velocity = {0.f, 0.f};
    float gravity = 0.f;

    bool isGround = true;
    int countDash = 10;

    float dashTimer = 0.f;
    float animationTimer = 0.f;

    Player(Game& game);
    void Update(const Map& map, const float dt);
    void UpdateAnimation(float dt);
    void InitGraphics(int frameWidth, int frameHeight);
    //void UpdateHitbox();
    void Draw(sf::RenderWindow &window) const;
    void Jump(const sf::Event::KeyPressed* pressedKey);
    void Dash(const sf::Event::KeyPressed* pressedKey);
    void Atack(const sf::Event::MouseButtonPressed* pressedKey);

    void PlayerJumping(const Map& map, const float dt);
    void PlayerMoving(const Map& map, float dt);

    void UpdateState();

    void ResetPhysics();
};
