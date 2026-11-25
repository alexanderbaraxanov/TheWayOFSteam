#pragma once

#include <SFML/Graphics.hpp>
#include "../Map/Map.hpp"

struct Player;

namespace Collison 
{
    void ResolveCollisionsX(const Map& map, Player& player);
    void ResolveCollisionsY(const Map& map, Player& player);
}