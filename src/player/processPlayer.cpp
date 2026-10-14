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

    bool CheckPosX(const float positionX, const Player& player, const sf::RenderWindow &window)
    {
        return (positionX > 0 && positionX + player.body[0].parameters.sizeRect.x < window.getSize().x) ;  
    }

    void ListenKeyMoving(float &direction)
    {
        direction = 0.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            direction -= 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            direction += 1.f;  
        }
    }

    void FrictionPlayer(Player& player, float dt)
    {
        if (player.speed.x != 0.f)
        {
            float sign = (player.speed.x < 0.f) ? -1.f : 1.f;
            if (std::abs(player.speed.x) <= player.friction * dt)
            {
                player.speed.x = 0.f;
            }
            else
            {
                player.speed.x -= sign * player.friction * dt;
            }
        }
    }

    void UpdatePlayerSpeed(Player& player, float dt)
    {
        if (player.direction.x != 0.f)
        {
            player.speed.x += player.direction.x * player.acceleration * dt;
        }
        else
        {
            FrictionPlayer(player, dt);   
        }
    }

    void CheckMaxSpeed(Player& player)
    {
        if (std::abs(player.speed.x) > player.maxSpeed && player.jerkTimer <= 0.f)
        { 
            float sign = (player.speed.x < 0.f) ? -1.f : 1.f;
            player.speed.x = sign * player.maxSpeed;
        }
    }

    void PlayerMoving(Player& player, const float dt) 
    {
        ListenKeyMoving(player.direction.x);
        UpdatePlayerSpeed(player, dt);        
        CheckMaxSpeed(player);  
    }

    void PlayerJumping(Player& player, const float dt)
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

    void UpdateJerkTimer(float &timer, float dt) 
    {
        if (timer > 0.f)
        {
            timer -= dt;
        }
    }

    void CheckCorrectPosition(Player& player, const sf::RenderWindow &window, const float dt)
    {
        sf::Vector2f nextPos = player.body[0].parameters.positionShape;
        nextPos.x += player.speed.x * dt;
        if (CheckPosX(nextPos.x, player, window))
        {
            player.body[0].parameters.positionShape = nextPos;
        }
        else
        {
            player.speed.x = 0.f;
        }
    }

    void PlayerUpdatePosition(Player& player, const sf::RenderWindow &window, float dt)
    {
        auto& head = player.body[1];
        auto& body = player.body[0];

        CheckCorrectPosition(player, window, dt);
        
        head.parameters.positionShape.y = body.parameters.positionShape.y - 10.f;
        if (player.speed.x > 0)
        {
            head.parameters.positionShape.x = body.parameters.positionShape.x + 12.f;
        }
        else if (player.speed.x < 0)
        {
            head.parameters.positionShape.x = body.parameters.positionShape.x + 4.f;
        }

        body.shape->setPosition(body.parameters.positionShape);
        head.shape->setPosition(head.parameters.positionShape);
    }


    void PlayerInit(Player& player) 
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
        Shape::SetRect(*body, playerBody.parameters);
        playerBody.shape = std::move(body);
        player.body.push_back(std::move(playerBody));

        playerHead.parameters = {
            .positionShape = {playerBody.parameters.positionShape.x + 8.f, playerBody.parameters.positionShape.y - 10.f},
            .colorShape = sf::Color::Black,
            .sizeRect = {10.f, 15.f},
        };
        Shape::SetRect(*head, playerHead.parameters);
        playerHead.shape = std::move(head);
        player.body.push_back(std::move(playerHead));

        player.maxSpeed = 300.f;
        player.acceleration = 1800.f;
        player.friction = 1500.f;
    }

    void PlayerUpdate(Player& player, const float dt, const sf::RenderWindow &window)
    {
        PlayerMoving(player, dt);
        PlayerJumping(player, dt);
        UpdateJerkTimer(player.jerkTimer, dt);
        PlayerUpdatePosition(player, window, dt);
    }

    void PlayerJump(Player& player, const sf::Event::KeyPressed* pressedKey) 
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

    void PlayerJerk(Player& player, const sf::Event::KeyPressed* pressedKey, const float dt)
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
        }
    }


}
