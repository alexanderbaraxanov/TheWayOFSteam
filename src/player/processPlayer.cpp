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
        Element playerBody; 
        Element playerHead;

        std::unique_ptr<sf::RectangleShape> body = std::make_unique<sf::RectangleShape>();
        std::unique_ptr<sf::RectangleShape> head = std::make_unique<sf::RectangleShape>();

        playerBody.parameters = {
            .positionShape = {10.f, 250.f},
            .colorShape = sf::Color::Black,
            .sizeRect = {26.f, 30.f},
        };
        Shape::setRect(*body, playerBody.parameters);
        playerBody.shape = std::move(body);
        player.body.push_back(std::move(playerBody));

        playerHead.parameters = {
            .positionShape = {playerBody.parameters.positionShape.x + 8.f, playerBody.parameters.positionShape.y - 10.f},
            .colorShape = sf::Color::Black,
            .sizeRect = {10.f, 15.f},
        };
        Shape::setRect(*head, playerHead.parameters);
        playerHead.shape = std::move(head);
        player.body.push_back(std::move(playerHead));

        player.maxSpeed = 300.f;
        player.acceleration = 1800.f;
        player.friction = 1500.f;
    }

    bool checkPosX(const float nextPosX, const Player& player, const sf::RenderWindow &window)
    {
        return (nextPosX > 0 && nextPosX + player.body[0].parameters.sizeRect.x < window.getSize().x) ;  
    }

    void playerMoving(Player& player, const sf::RenderWindow &window, const float dt) 
    {
        player.direction.x = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.direction.x -= 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.direction.x += 1.f;  
        }

        if (player.direction.x != 0.f)
        {
            player.speed.x += player.direction.x * player.acceleration * dt;
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
            player.body[0].parameters.positionShape.y += player.speed.y * dt;
        
            if (player.body[0].parameters.positionShape.y >= GROUND_LEVEL)
            {
                player.body[0].parameters.positionShape.y = GROUND_LEVEL; 
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

        sf::Vector2f nextPos = player.body[0].parameters.positionShape;
        nextPos.x += player.speed.x * dt;

        if (checkPosX(nextPos.x, player, window))
        {
            player.body[0].parameters.positionShape = nextPos;
        }
        else
        {
            player.speed.x = 0.f;
        }

        if (player.jerkTimer > 0.f)
        {
            player.jerkTimer -= dt;
        }
        
        player.body[1].parameters.positionShape.y = player.body[0].parameters.positionShape.y - 10.f;
        if (player.speed.x > 0)
        {
            player.body[1].parameters.positionShape.x = player.body[0].parameters.positionShape.x + 12.f;
        }
        else if (player.speed.x < 0)
        {
            player.body[1].parameters.positionShape.x = player.body[0].parameters.positionShape.x + 4.f;
        }

        player.body[0].shape->setPosition(player.body[0].parameters.positionShape);
        player.body[1].shape->setPosition(player.body[1].parameters.positionShape);
    }
}
