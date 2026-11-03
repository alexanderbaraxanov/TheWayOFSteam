#pragma once 

#include <SFML/Graphics.hpp>
#include "../Player/Player.hpp"
#include "../Shape/Shape.hpp"
#include "../Map/Map.hpp"
#include <SFML/System/Vector2.hpp>

 
struct CameraController 
{
    sf::View camera;
    float smoothness = 0.f;
    float leadDistance = 0.f;

    void CreateWorldView(sf::Vector2f windowSize, sf::Vector2f playerWorldPos);
    void Update(Player& player, Map& map, float dt); 
    sf::Vector2f CalculateLookAhead(sf::Vector2f playerPos, sf::Vector2f velocity) const;
    sf::Vector2f  SmoothCameraFollow(sf::Vector2f currentCamPos, sf::Vector2f playerPos, float smoothness, float dt);
    sf::Vector2f ClampCameraCenter(sf::Vector2f rawCenter, sf::Vector2f mapSize, sf::Vector2f screenSize); 
};