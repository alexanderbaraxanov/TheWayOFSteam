#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <memory>
#include "createShape.hpp"

void closeWindow(sf::RenderWindow &window)
{
    window.close();
    std::cout << "Close window" << std::endl;
}

std::vector<std::unique_ptr<sf::Drawable>> createShapes()
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
        {xPositionRectang + (xSizeRectang / 6) * 4, yPositionCircle},
        sf::Color::White,
        sf::Color::Black,
        5,
    };
    const float radiusCircle = 18;

    std::unique_ptr<sf::RectangleShape> rectang = std::make_unique<sf::RectangleShape>(CreateShape::createRect(sizeRectang, paramRectang));
    std::unique_ptr<sf::ConvexShape> convex = std::make_unique<sf::ConvexShape>(CreateShape::createConvex(paramConvex));
    std::unique_ptr<sf::CircleShape> circle1 = std::make_unique<sf::CircleShape>(CreateShape::createCirc(radiusCircle, paramCircle1));
    std::unique_ptr<sf::CircleShape> circle2 = std::make_unique<sf::CircleShape>(CreateShape::createCirc(radiusCircle, paramCircle2));
    
    std::vector<std::unique_ptr<sf::Drawable>> shapes;

    shapes.push_back(std::move(rectang));
    shapes.push_back(std::move(convex));
    shapes.push_back(std::move(circle1));
    shapes.push_back(std::move(circle2));

    return shapes;
}

void drawShapes(sf::RenderWindow& window, std::vector<std::unique_ptr<sf::Drawable>>& activeShapes)
{
    for(const std::unique_ptr<sf::Drawable>& shape : activeShapes)
    {
        window.draw(*shape);
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    window.setKeyRepeatEnabled(false);
 
    bool changeColor = false;
    float xPositionPlayer = 10;
    float yPositionPlayer = 10;
    float currXPlayer = 10;
    float currYPlayer = 10;
    float speed = 200.f;
    sf::Clock clock;

    std::vector<std::unique_ptr<sf::Drawable>> activeShapes = createShapes();

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            yPositionPlayer -= speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            xPositionPlayer -= speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            yPositionPlayer += speed * dt;     
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            xPositionPlayer += speed * dt;  
        }

        const sf::Vector2f sizePlayer = {30, 80};

        if(yPositionPlayer >= 0 && yPositionPlayer + sizePlayer.y <= 600)
        {
            currYPlayer = yPositionPlayer;
            std::cout << currYPlayer << std::endl;
        }
        else 
        {
            yPositionPlayer = currYPlayer;
        }
        if(xPositionPlayer >= 0 && xPositionPlayer + sizePlayer.x <= 800)
        {
            currXPlayer = xPositionPlayer;
            std::cout << currXPlayer << std::endl;
        }
        else 
        {
            xPositionPlayer = currXPlayer;
        }

        if(changeColor)
        {
            window.clear(sf::Color::Blue);
        }
        else
        {
            window.clear(sf::Color::Green);
        }

        const CreateShape::settingsShape paramPlayer = {
            {currXPlayer, currYPlayer},
            sf::Color::Black,
            sf::Color::White,
            3,
        };  
        sf::RectangleShape player = CreateShape::createRect(sizePlayer, paramPlayer);

        window.draw(player);

        drawShapes(window, activeShapes);

        window.display();
    }

    return 0;
}