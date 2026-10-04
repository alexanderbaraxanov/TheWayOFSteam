#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    
    bool changeColor = false;

    while (window.isOpen()) {
        std::string color = "Green";
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>())
            {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)
                {
                    changeColor = !changeColor;
                    std::cout << "Change color: " << changeColor << std::endl;
                }
            }
        }

        if(changeColor)
        {
            window.clear(sf::Color::Blue);
        }
        else
        {
            window.clear(sf::Color::Green);
        }
        window.setKeyRepeatEnabled(false);

        window.display();
    }

    return 0;
}