#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include "createShape.hpp"

void closeWindow(sf::RenderWindow &window)
{
    window.close();
    std::cout << "Close window" << std::endl;
}

void drawShapes(sf::RenderWindow &window)
{
    const float xPositionRectang = 200;
    const float yPositionRectang = 250;

    const float xSizeRectang = 300;
    const float ySizeRectang = 50;

    const float xPositionCircle = xPositionRectang + (xSizeRectang / 6);
    const float yPositionCircle = yPositionRectang + (ySizeRectang / 5) * 3.5;

    const CreateShape::settingsShape paramRectang = {
        {xPositionRectang, yPositionRectang},
        sf::Color::Yellow,
        sf::Color::White,
        3,
    };
    const sf::Vector2f sizeRectang = {xSizeRectang, ySizeRectang};

    const CreateShape::settingsShape paramConvex = {
        {xPositionRectang, yPositionRectang},
        sf::Color::Yellow,
        sf::Color::White,
        3,
    };

    const CreateShape::settingsShape paramCircle1 = {
        {xPositionCircle, yPositionCircle},
        sf::Color::White,
        sf::Color::Black,
        5,
    };
    const CreateShape::settingsShape paramCircle2 = {
        {yPositionRectang + (xSizeRectang / 6) * 3.5, yPositionCircle},
        sf::Color::White,
        sf::Color::Black,
        5,
    };
    const float radiusCircle = 18;


    sf::RectangleShape rectang = CreateShape::createRect(sizeRectang, paramRectang);
    sf::ConvexShape convex = CreateShape::createConvex(paramConvex);
    sf::CircleShape circle1 = CreateShape::createCirc(radiusCircle, paramCircle1);
    sf::CircleShape circle2 = CreateShape::createCirc(radiusCircle, paramCircle2);
   
    window.draw(rectang);
    window.draw(convex);
    window.draw(circle1);
    window.draw(circle2);
}


int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    window.setKeyRepeatEnabled(false);
 
    bool changeColor = false;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
            {
                closeWindow(window);
            }

            if (event->is<sf::Event::KeyPressed>())
            {
                const sf::Event::KeyPressed* pressedKey = event->getIf<sf::Event::KeyPressed>();
                if (pressedKey->code == sf::Keyboard::Key::Space)
                {
                    changeColor = !changeColor;
                    std::cout << "Change color: " << changeColor << std::endl;
                }

                if (pressedKey->code == sf::Keyboard::Key::Escape)
                {
                    closeWindow(window);
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

        drawShapes(window);

        window.display();
    }

    return 0;
}