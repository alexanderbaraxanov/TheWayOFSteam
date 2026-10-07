#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <memory>
#include "createShape.hpp"

struct Element {
    std::unique_ptr<sf::Shape> shape = nullptr;
    CreateShape::parametersShape parameters;
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
    CreateShape::setRect(*body, player.body.parameters);
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

void closeWindow(sf::RenderWindow &window)
{
    window.close();
    std::cout << "Close window" << std::endl;
}

std::vector<std::unique_ptr<sf::Drawable>> createShapes()
{
    const CreateShape::parametersShape paramRectang = {
        {200, 250},
        sf::Color::Yellow,
        sf::Color::White,
        3,
        sizeRect: {300, 50}
    };

    const float xPositionCircle = paramRectang.positionShape.x + (paramRectang.sizeRect.x / 6);
    const float yPositionCircle = paramRectang.positionShape.y + (paramRectang.sizeRect.y / 5) * 3.5;

    const CreateShape::parametersShape paramConvex = {
        {paramRectang.positionShape.x, paramRectang.positionShape.y},
        sf::Color::Yellow,
        sf::Color::White,
        3,
    };

    const CreateShape::parametersShape paramCircle1 = {
        {xPositionCircle, yPositionCircle},
        sf::Color::White,
        sf::Color::Black,
        5,
        radiusCircle: 18,
    };
    const CreateShape::parametersShape paramCircle2 = {
        {paramRectang.positionShape.x + (paramRectang.sizeRect.x / 6) * 4, yPositionCircle},
        sf::Color::White,
        sf::Color::Black,
        5,
        radiusCircle: 18,
    };

    std::unique_ptr<sf::RectangleShape> rectang = std::make_unique<sf::RectangleShape>(CreateShape::createRect(paramRectang));
    std::unique_ptr<sf::ConvexShape> convex = std::make_unique<sf::ConvexShape>(CreateShape::createConvex(paramConvex));
    std::unique_ptr<sf::CircleShape> circle1 = std::make_unique<sf::CircleShape>(CreateShape::createCirc(paramCircle1));
    std::unique_ptr<sf::CircleShape> circle2 = std::make_unique<sf::CircleShape>(CreateShape::createCirc(paramCircle2));
    
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

    Player player;
    playerInit(player);
    Player* ptrPlayer = &player;

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

        playerUpdate(player, dt, window);
        
        if(changeColor)
        {
            window.clear(sf::Color::Blue);
        }
        else
        {
            window.clear(sf::Color::Green);
        }

        
        
        window.draw(*player.body.shape);

        drawShapes(window, activeShapes);

        window.display();
    }

    return 0;
}