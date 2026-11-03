#include "Player.hpp"
#include <iostream>

constexpr float ACCELERATION = 1800.0f;
constexpr float MAX_SPEED = 400.0f;
constexpr float FRICTION = 0.2f;

constexpr float POWER_JUMP = -600.f;
constexpr float GRAVITY_UP = 1200.f;
constexpr float GRAVITY_DOWN = 1000.f;

void AccelerationPlayer(Player& player, float dt, bool& isMoving)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
    {
        player.velocity.x += ACCELERATION * dt;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
    {
        player.velocity.x -= ACCELERATION * dt;
        isMoving = true;
    }
}

void FrictionPlayer(Player& player, bool isMoving)
{
    if (!isMoving) 
    {
        player.velocity.x *= FRICTION;
    }
}

void CheckMaxVelocity(Player& player)
{
    if (player.jerkTimer <= 0.f)
    {
        player.velocity.x = std::clamp(player.velocity.x, -MAX_SPEED, MAX_SPEED);
    }
}

void PlayerMoving(Player& player, Map map, float dt)
{
    bool isMoving = false;
    AccelerationPlayer(player, dt, isMoving);
    FrictionPlayer(player, isMoving);
    CheckMaxVelocity(player);
    player.sprite.move({player.velocity.x * dt, 0.0f});
    player.ResolveCollisionsX(map);
}

void GravityPlayer(Player& player, const float dt) 
{
    player.gravity = (player.velocity.y < 0.f) ? GRAVITY_UP : GRAVITY_DOWN;
    player.velocity.y += player.gravity * dt;
}

void PlayerJumping(Player& player, Map map, const float dt)
{
    GravityPlayer(player, dt);
    player.sprite.move({0.0f, player.velocity.y * dt});
    player.ResolveCollisionsY(map);
}

void SpriteFlipping(Player& player)
{
    if (player.velocity.x > 10.0f)
    {
        player.sprite.setScale({1.0f, 1.0f});
    }
    else if (player.velocity.x < -10.0f)
    {
        player.sprite.setScale({-1.0f, 1.0f});
    }
}

void Player::ResetPhysics()
{
    health = 100.f;
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.0f, sprite.getLocalBounds().size.y / 2.0f});
    sprite.setPosition({100.f, 800.f});
    isGround = false;
    velocity = {0.f, 0.f};
    countJerk = 2;
}

static sf::Texture CheckAndLoadTexture(const std::string& filepath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filepath)) 
    {
        throw std::runtime_error("CRITICAL: Не удалось загрузить: " + filepath);
    }
    return texture;
}

Player::Player()
    : texture(CheckAndLoadTexture("../assets/enemy_1_2.png"))
    , sprite(texture)
{
    health = 100.f;
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.0f, sprite.getLocalBounds().size.y / 2.0f});
    sprite.setPosition({100.f, 800.f}); 
}    

void Player::Jump(const sf::Event::KeyPressed* pressedKey)
{
    if (pressedKey->code == sf::Keyboard::Key::Space)
    {
        if (isGround)
        {
            velocity.y = POWER_JUMP;
            isGround = false;
        }
    }
}

void Player::Jerk(const sf::Event::KeyPressed* pressedKey)
{
    if (countJerk > 0)
    {
        if (velocity.x != 0 && pressedKey->code == sf::Keyboard::Key::LAlt )
        {
            float sign = (velocity.x < 0.f) ? -1.f : 1.f;
            velocity.x += sign * MAX_SPEED * 1.5f;
            countJerk -= 1;
            jerkTimer = 0.1f;
        }
    }
}

void Player::UpdateState() {
    if (health < 0)
    {
        state = PlayerState::Dead;
    }
    else
    {   
        if (!isGround) 
        {
            state = (velocity.y < 0.0f) ? PlayerState::Jumping : PlayerState::Falling;
        } 
        else 
        {
            state = (std::abs(velocity.x) > 10.0f) ? PlayerState::Running : PlayerState::Idle;
        }
    }
}

void Player::Draw(sf::RenderWindow &window) const
{
    if(health > 0)
    { 
        window.draw(sprite);
    }
}