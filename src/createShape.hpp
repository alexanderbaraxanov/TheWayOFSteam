#pragma once 

#include <SFML/Graphics.hpp>

namespace CreateShape
{
    struct parametersShape {
        sf::Vector2f positionShape = {0.f, 0.f};
        sf::Color colorShape = sf::Color::Transparent; 
        sf::Color colorLine = sf::Color::Transparent;
        float lineThinckness = 0.f;
        float radiusCircle = 0.f;
        sf::Vector2f sizeRect = {0.f, 0.f};
    };

    void setRect(sf::RectangleShape& rectang, const parametersShape &parameters);
    sf::RectangleShape createRect(const parametersShape& parameters);
    sf::CircleShape createCirc(const parametersShape& parameters);
    sf::ConvexShape createConvex(const parametersShape& parameters);
    
}
