#include "../shapes/processShapes.hpp"
#include "processPlayer.hpp"
#include <optional>
#include <SFML/Graphics.hpp>

namespace Player
{
    void playerInit(Player& player) 
    {
        std::unique_ptr<sf::RectangleShape> body = std::make_unique<sf::RectangleShape>();
        player.body.parameters = {
            .positionShape = {0.f, 0.f},
            .colorShape = sf::Color::Black,
            .colorLine = sf::Color::White,
            .lineThinckness = 1,
            .sizeRect = {50.f, 100.f},
        };
        ProcessShape::setRect(*body, player.body.parameters);
        player.body.shape = std::move(body);
        player.speed = 300.f;
    }

    void playerMoving(sf::Vector2f& nextPos , Player& player, float dt) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            nextPos.x -= player.speed * dt;    
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            nextPos.x += player.speed * dt;  
        }
    }

    bool checkPosX(sf::Vector2f& nextPos , Player& player, sf::RenderWindow &window)
    {
        return (nextPos.x >= 0 && nextPos.x + player.body.parameters.sizeRect.x <= window.getSize().x);
    }

    bool checkPosY(sf::Vector2f& nextPos , Player& player, sf::RenderWindow &window)
    {
        return (nextPos.y >= 0 && nextPos.y + player.body.parameters.sizeRect.y <= window.getSize().y) ;  
    }

    void checkPosOnWindow (sf::Vector2f& nextPos , Player& player, sf::RenderWindow &window)
    {
        if(checkPosX(nextPos, player, window) && checkPosY(nextPos, player, window))
        {
            player.body.parameters.positionShape = nextPos;
        }
        else 
        {
            nextPos = player.body.parameters.positionShape ;
        }
    }

    void playerUpdate(Player& player, float dt, sf::RenderWindow &window)
    {
        sf::Vector2f nextPosPlayer = player.body.parameters.positionShape;

        playerMoving(nextPosPlayer, player, dt);

        checkPosOnWindow(nextPosPlayer, player, window);
        
        player.body.shape->setPosition(player.body.parameters.positionShape);
    }
}
