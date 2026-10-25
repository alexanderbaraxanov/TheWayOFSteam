#include "Shape.hpp"
#include <optional>
#include <SFML/Graphics.hpp>

namespace Shape
{
    void SetShape(sf::Shape &shape, const ParametersShape &parametersShape)
    {
        shape.setPosition(parametersShape.positionShape);
        shape.setFillColor(parametersShape.colorShape);
        shape.setOutlineColor(parametersShape.colorLine);
        shape.setOutlineThickness(parametersShape.lineThinckness);
    }

    void SetRect(sf::RectangleShape& rectang, const ParametersShape &parameters)
    {
        rectang.setSize(parameters.sizeRect);
        SetShape(rectang, parameters);
    }

    void SetCircle(sf::CircleShape& circle, const ParametersShape &parameters)
    {
        circle.setRadius(parameters.radiusCircle);
        SetShape(circle, parameters);
    }


    sf::RectangleShape CreateRect(const ParametersShape &parameters)
    {
        sf::RectangleShape rectang;
        SetRect(rectang, parameters);

        return rectang;
    }

    sf::CircleShape CreateCirc(const ParametersShape &parameters)
    {
        sf::CircleShape circle;
        SetCircle(circle, parameters);

        return circle;
    }

    void DrawShapes(sf::RenderWindow& window, std::vector<std::unique_ptr<sf::Drawable>>& activeShapes)
    {
        for(const std::unique_ptr<sf::Drawable>& shape : activeShapes)
        {
            window.draw(*shape);
        }
    }
}