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
    Player::playerInit(player);

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

                Player::playerJump(player, pressedKey);
                Player::playerJerk(player, pressedKey, dt);

                if (pressedKey->code == sf::Keyboard::Key::Escape)
                {
                    closeWindow(window);
                }
            }
        }
        
        window.clear(sf::Color::White);

        Player::playerUpdate(player, dt, window);
        const Shape::parametersShape paramFloar = {
            .positionShape = {0.f, 250.f + player.body.parameters.sizeRect.y},
            .colorShape = sf::Color::Green,
            .sizeRect = {SETTINGS_GAME.WINDOW_SIZE.x, SETTINGS_GAME.WINDOW_SIZE.y - 250  - player.body.parameters.sizeRect.y},
        };
        const sf::RectangleShape floar = Shape::createRect(paramFloar);

        window.draw(floar);
        window.draw(*player.body.shape);
        window.display();
    }

    return 0;
}