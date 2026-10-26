#include "Player.hpp"

constexpr float ACCELERATION = 1800.0f;
constexpr float MAX_SPEED = 300.0f;
constexpr float FRICTION = 0.2f;

constexpr float GROUND_LEVEL = 251.f;
constexpr float POWER_JUMP = -600.f;
constexpr float GRAVITY_UP = 2000.f;
constexpr float GRAVITY_DOWN = 1500.f;


bool CheckPosX(const float x, const Player& player, const sf::RenderWindow &window)
{
    float offsetX = player.hitbox.size.x / 2.f;
    return (x - offsetX > 0 && x + offsetX < static_cast<float>(window.getSize().x));
}

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

void CheckXBoundaries(Player& player, const sf::RenderWindow &window, float dt)
{
    float offsetX = player.sprite.getPosition().x + player.velocity.x * dt;

    if (CheckPosX(offsetX, player, window))
    {
        player.sprite.move({offsetX - player.sprite.getPosition().x, 0.f});
    }
    else
    {
        player.velocity.x = 0.f;
    }
}

void PlayerMoving(Player& player, const sf::RenderWindow &window, float dt)
{
    bool isMoving = false;
    AccelerationPlayer(player, dt, isMoving);
    FrictionPlayer(player, isMoving);
    CheckMaxVelocity(player);
    CheckXBoundaries(player, window, dt);
}

void GravityPlayer(Player& player, const float dt) 
{
    player.gravity = (player.velocity.y < 0.f) ? GRAVITY_UP : GRAVITY_DOWN;
    if (!player.isGround)
    {
        player.velocity.y += player.gravity * dt;
    }
}

void CheckYBoundaries(Player& player, float dt)
{
    float offsetY = 0.f;
    if (player.velocity.y >= 0.f && player.hitbox.position.y >=  GROUND_LEVEL) 
    {
        offsetY = GROUND_LEVEL - player.hitbox.position.y;
        player.velocity.y = 0.0f;
        player.isGround = true;
    } else {
        player.isGround = false;
        offsetY = player.velocity.y * dt;
    }
    player.sprite.move({0.f, offsetY});
}

void PlayerJumping(Player& player, const float dt)
{
    GravityPlayer(player, dt);
    CheckYBoundaries(player, dt);
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
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.0f, sprite.getLocalBounds().size.y / 2.0f});
    hitbox.size = static_cast<sf::Vector2f>(texture.getSize());
    float offsetHeight = hitbox.size.y / 2.f;
    float offsetWidth = hitbox.size.x / 2.f;

    sprite.setPosition({offsetWidth, GROUND_LEVEL + offsetHeight});
    UpdateHitbox();
}    

void Player::Update(sf::RenderWindow &window, const float dt)
{
    PlayerMoving(*this, window, dt);
    PlayerJumping(*this, dt);
    SpriteFlipping(*this);
    UpdateJerkTimer(jerkTimer, dt);
    UpdateHitbox();
}

void Player::UpdateHitbox()
{
    sf::Vector2f spritePos = sprite.getPosition();
    hitbox.position = {spritePos.x - hitbox.size.x / 2.f, spritePos.y - hitbox.size.y / 2.f,};
}

void Player::Draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
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