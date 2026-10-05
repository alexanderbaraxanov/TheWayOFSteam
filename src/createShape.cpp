#include "createShape.hpp"

#include <SFML/Graphics.hpp>
#include <optional>

namespace CreateShape
{  
    void setShape(sf::Shape& shape, const settingsShape& parametersShape) 
    {
        shape.setPosition(parametersShape.positionShape);
        shape.setFillColor(parametersShape.colorShape);
        shape.setOutlineColor(parametersShape.colorLine);
        shape.setOutlineThickness(parametersShape.lineThinckness);
    }

    sf::RectangleShape createRect(const sf::Vector2f size, const settingsShape& parameters) 
    {
        sf::RectangleShape rectang;
        rectang.setSize(size);  
        setShape(rectang, parameters);

        return rectang;
    }

    sf::CircleShape createCirc(const float radius, const settingsShape& parameters) 
    {
        sf::CircleShape circle;
        circle.setRadius(radius); 
        setShape(circle, parameters);

        return circle;
    }

    sf::ConvexShape createConvex(const settingsShape& parameters)
    {
        sf::ConvexShape convex;
        convex.setPointCount(4);
        const float x = parameters.positionShape.x;
        const float y = parameters.positionShape.y;

        convex.setPoint(0, {60, -3});
        convex.setPoint(1, {200, -3});
        convex.setPoint(2, {160, -50});
        convex.setPoint(3, {70, -50});

        setShape(convex, parameters);

        return convex;
    }
}