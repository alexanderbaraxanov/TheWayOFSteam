#include "../shapes/processShapes.hpp"
#include "processPlayer.hpp"
#include <optional>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Player
{
    const float GROUND_LEVEL = 250;
    const float POWER_JUMP = -600;
    const float GRAVITY_UP = 2000.f;
    const float GRAVITY_DOWN = 1500.f;

    void playerInit(Player& player) 
    {
        std::unique_ptr<sf::RectangleShape> body = std::make_unique<sf::RectangleShape>();
        player.body.parameters = {
            .positionShape = {10.f, 250.f},
            .colorShape = sf::Color::Black,
            .sizeRect = {25.f, 30.f},
        };
        Shape::setRect(*body, player.body.parameters);
        player.body.shape = std::move(body);
        player.maxSpeed = 300.f;
        player.acceleration = 1800.f;
        player.friction = 1500.f;
    }

    bool checkPosX(const float nextPosX, const Player& player, const sf::RenderWindow &window)
    {
        return (nextPosX > 0 && nextPosX + player.body.parameters.sizeRect.x < window.getSize().x) ;  
    }

    bool checkPosY(const float nextPosY, const Player& player, const sf::RenderWindow &window)
    {
        return (nextPosY > 0 && nextPosY + player.body.parameters.sizeRect.y < window.getSize().y) ;  
    }

    void playerMoving(Player& player, const sf::RenderWindow &window, const float dt) 
    {
        float dirMoving = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            dirMoving -= 1.f;    
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            dirMoving += 1.f;  
        }

        if (dirMoving != 0.f)
        {
            player.speed.x += dirMoving * player.acceleration * dt;
        }
        else
        {
            if (player.speed.x != 0.f)
            {
                float sign = (player.speed.x < 0.f) ? -1.f : 1.f;

                if (std::abs(player.speed.x) <= player.friction * dt)
                    player.speed.x = 0.f;
                else
                    player.speed.x -= sign * player.friction * dt;
            }
        }

        if (std::abs(player.speed.x) > player.maxSpeed && player.jerkTimer <= 0.f)
        { 
            float sign = (player.speed.x < 0.f) ? -1.f : 1.f;
            player.speed.x = sign * player.maxSpeed;
        }
    }

    void playerJumping(Player& player, const float dt)
    {
        player.gravity = (player.speed.y < 0.f) ? GRAVITY_UP : GRAVITY_DOWN;

        if (!player.isGround)
        {
            player.speed.y += player.gravity * dt;
            player.body.parameters.positionShape.y += player.speed.y * dt;
        
            if (player.body.parameters.positionShape.y >= GROUND_LEVEL)
            {
                player.body.parameters.positionShape.y = GROUND_LEVEL; 
                player.isGround = true;
                player.speed.y = 0.f;
            }
        }
    }

    void playerJerk(Player& player, const sf::Event::KeyPressed* pressedKey, const float dt)
    {
        if (player.countJerk > 0)
        {
            if (pressedKey->code == sf::Keyboard::Key::LAlt)
            {
                float sign = (player.speed.x < 0.f) ? -1.f : 1.f;
                player.speed.x += sign * player.maxSpeed * 1.5f;  
                player.countJerk -= 1; 
                player.jerkTimer = 0.1f;
            }
            std::cout << player.countJerk << std::endl;
        }
    }

    void playerJump(Player& player, const sf::Event::KeyPressed* pressedKey) 
    {
        if (pressedKey->code == sf::Keyboard::Key::Space)
        {
            if (player.isGround) 
                {
                    player.isGround = false;
                    player.speed.y = POWER_JUMP;
                }
        }
    }

    void playerUpdate(Player& player, const float dt, const sf::RenderWindow &window)
    {
        playerMoving(player, window, dt);
        playerJumping(player, dt);

        sf::Vector2f nextPos = player.body.parameters.positionShape;
        nextPos.x += player.speed.x * dt;

        if (checkPosX(nextPos.x, player, window))
        {
            player.body.parameters.positionShape = nextPos;
        }
        else
        {
            player.speed.x = 0.f;
        }

        if (player.jerkTimer > 0.f)
        {
            player.jerkTimer -= dt;
        }
        
        player.body.shape->setPosition(player.body.parameters.positionShape);
    }
}
