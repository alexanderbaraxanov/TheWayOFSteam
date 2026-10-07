#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <memory>
#include "shapes/processShapes.hpp"
#include "player/processPlayer.hpp"

void closeWindow(sf::RenderWindow &window)
{
    window.close();
    std::cout << "Close window" << std::endl;
}

std::vector<std::unique_ptr<sf::Drawable>> createShapes()
{
    const ProcessShape::parametersShape paramRectang = {
        {200, 250},
        sf::Color::Yellow,
        sf::Color::White,
        3,
        sizeRect: {300, 50}
    };

    const float xPositionCircle = paramRectang.positionShape.x + (paramRectang.sizeRect.x / 6);
    const float yPositionCircle = paramRectang.positionShape.y + (paramRectang.sizeRect.y / 5) * 3.5;

    const ProcessShape::parametersShape paramConvex = {
        {paramRectang.positionShape.x, paramRectang.positionShape.y},
        sf::Color::Yellow,
        sf::Color::White,
        3,
    };

    const ProcessShape::parametersShape paramCircle1 = {
        {xPositionCircle, yPositionCircle},
        sf::Color::White,
        sf::Color::Black,
        5,
        radiusCircle: 18,
    };
    const ProcessShape::parametersShape paramCircle2 = {
        {paramRectang.positionShape.x + (paramRectang.sizeRect.x / 6) * 4, yPositionCircle},
        sf::Color::White,
        sf::Color::Black,
        5,
        radiusCircle: 18,
    };

    std::unique_ptr<sf::RectangleShape> rectang = std::make_unique<sf::RectangleShape>(ProcessShape::createRect(paramRectang));
    std::unique_ptr<sf::ConvexShape> convex = std::make_unique<sf::ConvexShape>(ProcessShape::createConvex(paramConvex));
    std::unique_ptr<sf::CircleShape> circle1 = std::make_unique<sf::CircleShape>(ProcessShape::createCirc(paramCircle1));
    std::unique_ptr<sf::CircleShape> circle2 = std::make_unique<sf::CircleShape>(ProcessShape::createCirc(paramCircle2));
    
    std::vector<std::unique_ptr<sf::Drawable>> shapes;

    shapes.push_back(std::move(rectang));
    shapes.push_back(std::move(convex));
    shapes.push_back(std::move(circle1));
    shapes.push_back(std::move(circle2));

    return shapes;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    window.setKeyRepeatEnabled(false);
 
    bool changeColor = false; 

    Player::Player player;
    Player::playerInit(player);

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

        Player::playerUpdate(player, dt, window);
        
        if(changeColor)
        {
            window.clear(sf::Color::Blue);
        }
        else
        {
            window.clear(sf::Color::Green);
        }
        
        window.draw(*player.body.shape);

        ProcessShape::drawShapes(window, activeShapes);

        window.display();
    }

    return 0;
}