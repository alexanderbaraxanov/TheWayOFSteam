#pragma once
#include "../Player/Player.hpp"
#include "../Map/Map.hpp"


struct Collision {
    Player& player;
    Map& map;

    void ResolveCollisionsX(const Map& map);
    void ResolveCollisionsY(const Map& map);
};