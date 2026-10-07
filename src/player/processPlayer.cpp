#include "../shapes/processShapes.hpp"
#include <optional>
#include <SFML/Graphics.hpp>

namespace Player
{
    struct Element {
        std::unique_ptr<sf::Shape> shape = nullptr;
        ProcessShape::parametersShape parameters;
    };

    struct Player {
        Element body;
        float speed = 0.f;
    };

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

    void playerUpdate(Player& player, float dt, sf::RenderWindow &window)
    {
        sf::Vector2f nextPositionPlayer = player.body.parameters.positionShape;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                nextPositionPlayer.y -= player.speed * dt;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                nextPositionPlayer.x -= player.speed * dt;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                nextPositionPlayer.y += player.speed * dt;     
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                nextPositionPlayer.x += player.speed * dt;  
            }

            if((nextPositionPlayer.y >= 0 && nextPositionPlayer.y + player.body.parameters.sizeRect.y <= window.getSize().y) && (nextPositionPlayer.x >= 0 && nextPositionPlayer.x + player.body.parameters.sizeRect.x <= window.getSize().x))
            {
            player.body.parameters.positionShape = nextPositionPlayer;
            }
            else 
            {
                nextPositionPlayer = player.body.parameters.positionShape ;
            }
            player.body.shape->setPosition(player.body.parameters.positionShape);
    }
}
