#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <memory>
#include "shapes/processShapes.hpp"
#include "player/processPlayer.hpp"

struct Settings {
    const sf::Vector2u WINDOW_SIZE = {0, 0};
    const std::string NAME_WINDOW = "SFML window";
};

const Settings SETTINGS_GAME = {
    {800,600},
    "The Way of Steam",
};

void closeWindow(sf::RenderWindow &window)
{
    window.close();
    std::cout << "Close window" << std::endl;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SETTINGS_GAME.WINDOW_SIZE), SETTINGS_GAME.NAME_WINDOW);
    window.setKeyRepeatEnabled(false);

    Player::Player player;
    Player::PlayerInit(player);

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>())
            {
                closeWindow(window);
            }

            if (event->is<sf::Event::KeyPressed>())
            {
                const sf::Event::KeyPressed* pressedKey = event->getIf<sf::Event::KeyPressed>();

                Player::PlayerJump(player, pressedKey);
                Player::PlayerJerk(player, pressedKey, dt);

                if (pressedKey->code == sf::Keyboard::Key::Escape)
                {
                    closeWindow(window);
                }
            }
        }
        
        window.clear(sf::Color::White);

        Player::PlayerUpdate(player, dt, window);
        const Shape::ParametersShape paramFloar = {
            .positionShape = {
                0.f,
                250.f + player.body[0].parameters.sizeRect.y,
            },
            .colorShape = sf::Color::Green,
            .sizeRect = {
                static_cast<float>(SETTINGS_GAME.WINDOW_SIZE.x), 
                static_cast<float>(SETTINGS_GAME.WINDOW_SIZE.y) - 250  - player.body[0].parameters.sizeRect.y
            },
        };
        const sf::RectangleShape floar = Shape::CreateRect(paramFloar);

        window.draw(floar);
        window.draw(*player.body[0].shape);
        window.draw(*player.body[1].shape);
        window.display();
    }

    return 0;
}