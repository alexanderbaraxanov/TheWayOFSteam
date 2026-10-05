#pragma once 

#include <SFML/Graphics.hpp>

namespace CreateShape
{
    struct settingsShape {
        sf::Vector2f positionShape;
        sf::Color colorShape;
        sf::Color colorLine;
        float lineThinckness;
    };

    sf::RectangleShape createRect(const sf::Vector2f size, const settingsShape& parameters);
    sf::CircleShape createCirc(const float radius, const settingsShape& parameters);
    sf::ConvexShape createConvex(const settingsShape& parameters);
    
}
