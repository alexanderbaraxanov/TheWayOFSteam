#include "processShapes.hpp"
#include <optional>
#include <SFML/Graphics.hpp>

namespace Shape
{
    void setShape(sf::Shape &shape, const parametersShape &parametersShape)
    {
        shape.setPosition(parametersShape.positionShape);
        shape.setFillColor(parametersShape.colorShape);
        shape.setOutlineColor(parametersShape.colorLine);
        shape.setOutlineThickness(parametersShape.lineThinckness);
    }

    void setRect(sf::RectangleShape& rectang, const parametersShape &parameters)
    {
        rectang.setSize(parameters.sizeRect);
        setShape(rectang, parameters);
    }

    void setCircle(sf::CircleShape& circle, const parametersShape &parameters)
    {
        circle.setRadius(parameters.radiusCircle);
        setShape(circle, parameters);
    }


    sf::RectangleShape createRect(const parametersShape &parameters)
    {
        sf::RectangleShape rectang;
        setRect(rectang, parameters);

        return rectang;
    }

    sf::CircleShape createCirc(const parametersShape &parameters)
    {
        sf::CircleShape circle;
        setCircle(circle, parameters);

        return circle;
    }

    void drawShapes(sf::RenderWindow& window, std::vector<std::unique_ptr<sf::Drawable>>& activeShapes)
    {
        for(const std::unique_ptr<sf::Drawable>& shape : activeShapes)
        {
            window.draw(*shape);
        }
    }
}