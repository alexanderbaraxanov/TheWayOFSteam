#include "Player.hpp"

void UpdateDashTimer(float &timer, float dt)
{
    if (timer > 0.f)
    {
        timer -= dt;
    }
}

void DicrementHealth(float &health, float dHP)
{
    health -= dHP; 
}

void IncrementHealth(float &health, float dHP)
{
    health += dHP; 
}

void IncrementDashCounter(int &counter) 
{
    counter += 1; 
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

void Player::Update(const Map& map, const float dt)
{
    PlayerMoving(map, dt);
    PlayerJumping(map, dt);

    SpriteFlipping(*this);
    if(map.IsSpike(sprite.getPosition().x, sprite.getPosition().y) && state != PlayerState::Dead)
    {
        velocity.y = POWER_JUMP;
        isGround = false;
        DicrementHealth(health, 30);
    }
    if(map.IsDashCoin(sprite.getPosition().x, sprite.getPosition().y) && state != PlayerState::Dead)
    {
        IncrementDashCounter(countDash);
    }
    
    UpdateState();
    UpdateAnimation(dt);

    UpdateDashTimer(dashTimer, dt);
}

void Player::ResetPhysics()
{
    health = 100.f;
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.0f, sprite.getLocalBounds().size.y / 2.0f});
    sprite.setPosition({100.f, 800.f});
    hitbox.position = sprite.getPosition();
    isGround = false;
    velocity = {0.f, 0.f};
    countDash = 10;
}
