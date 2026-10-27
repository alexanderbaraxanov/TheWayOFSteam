#include "Player.hpp"
#include <iostream>

constexpr float ACCELERATION = 1800.0f;
constexpr float MAX_SPEED = 400.0f;
constexpr float FRICTION = 0.2f;

constexpr float GROUND_LEVEL = 251.f;
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

void PlayerMoving(Player& player, const sf::RenderWindow &window, float dt)
{
    bool isMoving = false;
    AccelerationPlayer(player, dt, isMoving);
    FrictionPlayer(player, isMoving);
    CheckMaxVelocity(player);
}

void GravityPlayer(Player& player, const float dt) 
{
    player.gravity = (player.velocity.y < 0.f) ? GRAVITY_UP : GRAVITY_DOWN;
    player.velocity.y += player.gravity * dt;
}

void PlayerJumping(Player& player, const float dt)
{
    GravityPlayer(player, dt);
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

void UpdateJerkTimer(float &timer, float dt)
{
    if (timer > 0.f)
    {
        timer -= dt;
    }
}

void UpdateHealth(float &health, float dt)
{
    health -= 50 * dt; 
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

bool CheckCollision(const sf::FloatRect& a, const sf::FloatRect& b) {
   return a.findIntersection(b).has_value();
}

void Player::ResolveCollisionsX(const Map& map) {
   sf::FloatRect bounds = sprite.getGlobalBounds();
  
   for (const auto& tileRect : map.GetNearbySolidTiles(bounds)) {
        if (CheckCollision(bounds, tileRect)) 
        {
            float playerCenterX = sprite.getPosition().x;
            float tileCenterX = tileRect.position.x + tileRect.size.x / 2.0f;
            if (velocity.x > 0.0f || (velocity.x == 0.0f && playerCenterX < tileCenterX)) {
                sprite.setPosition({tileRect.position.x - bounds.size.x / 2.0f - EPSILON, sprite.getPosition().y});
            } 
            else if (velocity.x < 0.0f || (velocity.x == 0.0f && playerCenterX > tileCenterX)) 
            {
                sprite.setPosition({tileRect.position.x + tileRect.size.x + bounds.size.x / 2.0f + EPSILON, sprite.getPosition().y});
            }
            velocity.x = 0.0f; 
            break;
        }

   }
}

void Player::ResolveCollisionsY(const Map& map) {
   sf::FloatRect bounds = sprite.getGlobalBounds();
   isGround = false; 

    for (const auto& tileRect : map.GetNearbySolidTiles(bounds)) {
        if (CheckCollision(bounds, tileRect)) 
        {
            if (velocity.y > 0.0f || (velocity.y == 0.0f && sprite.getPosition().y < tileRect.position.y)) 
            { 
                sprite.setPosition({sprite.getPosition().x, tileRect.position.y - bounds.size.y / 2.0f});
                isGround = true;   
            } 
            else if (velocity.y < 0.0f) 
            { 
                sprite.setPosition({sprite.getPosition().x, tileRect.position.y + tileRect.size.y + bounds.size.y / 2.0f + EPSILON});
            }
            velocity.y = 0.0f;
            break;
        }
    }
}

void CheckOneWayPlatform(Player& player, sf::FloatRect tileRect, float prevBottom) {
   sf::FloatRect bounds = player.sprite.getGlobalBounds();

    if (player.velocity.y > 0.0f) {
        if (prevBottom <= tileRect.position.y + EPSILON) {
            if (CheckCollision(bounds, tileRect)) {
                player.sprite.setPosition({player.sprite.getPosition().x, tileRect.position.y - bounds.size.y / 2.0f});
                player.velocity.y = 0.0f;
                player.isGround = true;
            }
        }
    }
}


void Player::UpdateState() {
    if (health < 0)
    {
        state = State::Dead;
    }
    else
    {   
        if (!isGround) 
        {
            state = (velocity.y < 0.0f) ? State::Jumping : State::Falling;
        } 
        else 
        {
            state = (std::abs(velocity.x) > 10.0f) ? State::Running : State::Idle;
        }
    }
}

void Player::Update(const Map& map, const float dt)
{
    bool isMoving = false;
    AccelerationPlayer(*this, dt, isMoving);
    FrictionPlayer(*this, isMoving);
    CheckMaxVelocity(*this);
    sprite.move({velocity.x * dt, 0.0f});
    ResolveCollisionsX(map);

    GravityPlayer(*this, dt);
    sprite.move({0.0f, velocity.y * dt});
    ResolveCollisionsY(map);

    SpriteFlipping(*this);
    UpdateJerkTimer(jerkTimer, dt);
    if(map.IsSpike(sprite.getPosition().x, sprite.getPosition().y) && state != State::Dead)
    {
        UpdateHealth(health, dt);
        std::cout << health << std::endl;
    }
    UpdateState();
}

void Player::Draw(sf::RenderWindow &window) const
{
    if(health > 0)
    { 
        window.draw(sprite);
    }
}