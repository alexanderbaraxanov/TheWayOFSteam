#include <SFML/Graphics.hpp>
#include "../shapes/processShapes.hpp"

namespace Player
{
    struct Element {
        std::unique_ptr<sf::Shape> shape = nullptr;
        ProcessShape::parametersShape parameters;
    };

    struct Player {
        Element body;
        float speed = 0.f;
    };

    void playerInit(Player& player) ;
    void playerUpdate(Player& player, float dt, sf::RenderWindow &window);
}