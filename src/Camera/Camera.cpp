#include "Camera.hpp"

constexpr sf::Vector2f WINDOW_SIZE = {800, 600};

void CameraController::CreateWorldView(sf::Vector2f windowSize, sf::Vector2f playerWorldPos) 
{
    camera = sf::View(sf::FloatRect({0.0f, 0.0f}, windowSize));
    camera.setCenter(playerWorldPos);   
    camera.setSize(windowSize); 
    smoothness = 1.3f;
    leadDistance = 80.f;
}

sf::Vector2f CameraController::CalculateLookAhead(sf::Vector2f playerPos, sf::Vector2f velocity) const 
{
    if (velocity.x > 10.0f) return {playerPos.x + leadDistance, playerPos.y};
    if (velocity.x < -10.0f) return {playerPos.x - leadDistance, playerPos.y};
    return playerPos;
}

sf::Vector2f  CameraController::SmoothCameraFollow(sf::Vector2f currentCamPos, sf::Vector2f playerPos, float smoothness, float dt) 
{
    const sf::Vector2f delta = playerPos - currentCamPos;
    return currentCamPos + delta * std::clamp(smoothness * dt, 0.0f, 1.0f);
}

sf::Vector2f CameraController::ClampCameraCenter(sf::Vector2f newCenter, sf::Vector2f mapSize, sf::Vector2f screenSize) 
{
    const float halfScreenX = screenSize.x / 2.0f;
    const float halfScreenY = screenSize.y / 2.0f;
        
    const float minX = halfScreenX;
    const float maxX = mapSize.x - halfScreenX;
    const float minY = halfScreenY;
    const float maxY = mapSize.y - halfScreenY;

    return {
        std::clamp(newCenter.x, minX, maxX),
        std::clamp(newCenter.y, minY, maxY)
    };
}

void CameraController::Update(Player& player, Map& map, float dt) 
{
    sf::Vector2f currCamPos = camera.getCenter();
    sf::Vector2f mapSize = {static_cast<float>(map.width) * TILE_SIZE, static_cast<float>(map.height) * TILE_SIZE}; 

    sf::Vector2f currPlayerPos = CalculateLookAhead(player.sprite.getPosition(), player.velocity);
    sf::Vector2f newCamPos = SmoothCameraFollow(currCamPos, currPlayerPos, smoothness, dt);
    sf::Vector2f camPos = ClampCameraCenter(newCamPos, mapSize, WINDOW_SIZE);
    
    camera.setCenter(camPos);
}