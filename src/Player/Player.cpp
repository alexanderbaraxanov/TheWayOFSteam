#include "Player.hpp"
#include <iostream>

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
    : texture(CheckAndLoadTexture("../assets/player.png"))
    , sprite(texture)
{
    health = 100.f;
    currentFrame = 0;
    sprite.setOrigin({sprite.getLocalBounds().size.x / 2.0f, sprite.getLocalBounds().size.y / 2.0f});
    InitGraphics(48, 98);
    sprite.setPosition({100.f, 800.f}); 
}    

void Player::UpdateState() {
    if (health < 0)
    {
        sounds.deadSound.play();
        state = PlayerState::Dead;
    }
    else
    {   
        if (!isGround) 
        {
            if (velocity.y < 0.0f) 
            {
                state = PlayerState::Jumping;
            } 
            else 
            {
                state = PlayerState::Falling;
            }
        } 
        else 
        {
            if (std::abs(velocity.x) > 10.0f) 
            {
                state = PlayerState::Running;
            } 
            else 
            {
                state = PlayerState::Idle;
            }
        }
        if (dashTimer > 0) 
        {
            state = PlayerState::Dashing;
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