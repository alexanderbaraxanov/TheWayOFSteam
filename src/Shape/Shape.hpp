#pragma once 

#include <SFML/Graphics.hpp>

namespace Shape
{
    struct ParametersShape {
        sf::Vector2f positionShape = {0.f, 0.f};
        sf::Color colorShape = sf::Color::Transparent; 
        sf::Texture textureShape;
        sf::Color colorLine = sf::Color::Transparent;
        float lineThinckness = 0.f;
        float radiusCircle = 0.f;
        sf::Vector2f sizeRect = {0.f, 0.f};
    };

    void SetRect(sf::RectangleShape& rectang, const ParametersShape &parameters);
    sf::RectangleShape CreateRect(const ParametersShape& parameters);
    sf::CircleShape CreateCirc(const ParametersShape& parameters);
    void DrawShapes(sf::RenderWindow& window, std::vector<std::unique_ptr<sf::Drawable>>& activeShapes);
}
