#include "createShape.hpp"
#include <optional>
#include <SFML/Graphics.hpp>

namespace CreateShape
{
    void setShape(sf::Shape &shape, const parametersShape &parametersShape)
    {
        shape.setPosition(parametersShape.positionShape);
        shape.setFillColor(parametersShape.colorShape);
        shape.setOutlineColor(parametersShape.colorLine);
        shape.setOutlineThickness(parametersShape.lineThinckness);
    }

    sf::RectangleShape createRect(const parametersShape &parameters)
    {
        sf::RectangleShape rectang;
        rectang.setSize(parameters.sizeRect);
        setShape(rectang, parameters);

        return rectang;
    }

    void setRect(sf::RectangleShape& rectang, const parametersShape &parameters)
    {
        rectang.setSize(parameters.sizeRect);
        setShape(rectang, parameters);
    }

    sf::CircleShape createCirc(const parametersShape &parameters)
    {
        sf::CircleShape circle;
        circle.setRadius(parameters.radiusCircle);
        setShape(circle, parameters);

        return circle;
    }

    sf::ConvexShape createConvex(const parametersShape &parameters)
    {
        sf::ConvexShape convex;
        convex.setPointCount(4);

        convex.setPoint(0, {60, -3});
        convex.setPoint(1, {200, -3});
        convex.setPoint(2, {160, -50});
        convex.setPoint(3, {70, -50});

        setShape(convex, parameters);

        return convex;
    }
}