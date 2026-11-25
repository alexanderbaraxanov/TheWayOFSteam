#include "./Player.hpp"
#include "../CollisionHandler/CollisonHandler.hpp"

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
    if (player.dashTimer <= 0.f)
    {
        player.velocity.x = std::clamp(player.velocity.x, -MAX_SPEED, MAX_SPEED);
    }
}

void Player::PlayerMoving(const Map& map, float dt)
{
    bool isMoving = false;
    AccelerationPlayer(*this, dt, isMoving);
    FrictionPlayer(*this, isMoving);
    CheckMaxVelocity(*this);
    sprite.move({velocity.x * dt, 0.0f});
    Collison::ResolveCollisionsX(map, *this);
    if(isGround && isMoving && sounds.runSound.getStatus() != sf::Sound::Status::Playing)
    {
        sounds.runSound.play();
    }
}

void GravityPlayer(Player& player, const float dt) 
{
    player.gravity = (player.velocity.y < 0.f) ? GRAVITY_UP : GRAVITY_DOWN;
    player.velocity.y += player.gravity * dt;
}

void Player::PlayerJumping(const Map& map, const float dt)
{
    GravityPlayer(*this, dt);
    sprite.move({0.0f, velocity.y * dt});
    Collison::ResolveCollisionsY(map, *this);
}

void Player::Jump(const sf::Event::KeyPressed* pressedKey)
{
    if (pressedKey->code == sf::Keyboard::Key::Space)
    {
        if (isGround)
        {
            sounds.jumpSound.play();
            velocity.y = POWER_JUMP;
            isGround = false;
        }
    }
}

void Player::Dash(const sf::Event::KeyPressed* pressedKey)
{
    if (countDash > 0)
    {
        if (velocity.x != 0 && pressedKey->code == sf::Keyboard::Key::LAlt )
        {
            sounds.dashSound.play();
            float sign = (velocity.x < 0.f) ? -1.f : 1.f;
            velocity.x += sign * MAX_SPEED * 1.5f;
            countDash -= 1;
            dashTimer = 0.1f;
        }
    }
}

void Player::Atack(const sf::Event::MouseButtonPressed* pressedKey)
{
    if (pressedKey->button == sf::Mouse::Button::Left)
    {
        countDash += 1;
        //sounds.atackSound.play();
        state == PlayerState::Hitting;
        
    }
}