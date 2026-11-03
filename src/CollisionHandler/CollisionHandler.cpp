#include "./CollisonHandler.hpp"

bool CheckCollision(const sf::FloatRect& a, const sf::FloatRect& b) 
{
    return a.findIntersection(b).has_value();
}


void Collision::ResolveCollisionsY(const Map& map) {
   sf::FloatRect bounds = player.sprite.getGlobalBounds();
   player.isGround = false; 

    for (const auto& tileRect : map.GetNearbySolidTiles(bounds)) {
        if (CheckCollision(bounds, tileRect)) 
        {
            if (player.velocity.y > 0.0f || (player.velocity.y == 0.0f && player.sprite.getPosition().y < tileRect.position.y)) 
            { 
                player.sprite.setPosition({player.sprite.getPosition().x, tileRect.position.y - bounds.size.y / 2.0f});
                player.isGround = true;   
            } 
            else if (player.velocity.y < 0.0f) 
            { 
                player.sprite.setPosition({player.sprite.getPosition().x, tileRect.position.y + tileRect.size.y + bounds.size.y / 2.0f + EPSILON});
            }
            player.velocity.y = 0.0f;
            break;
        }
    }
}


void Collision::ResolveCollisionsX(const Map& map) {
   sf::FloatRect bounds = player.sprite.getGlobalBounds();
  
   for (const auto& tileRect : map.GetNearbySolidTiles(bounds)) {
        if (CheckCollision(bounds, tileRect)) 
        {
            float playerCenterX = player.sprite.getPosition().x;
            float tileCenterX = tileRect.position.x + tileRect.size.x / 2.0f;
            if (player.velocity.x > 0.0f || (player.velocity.x == 0.0f && playerCenterX < tileCenterX)) {
                player.sprite.setPosition({tileRect.position.x - bounds.size.x / 2.0f - EPSILON, player.sprite.getPosition().y});
            } 
            else if (player.velocity.x < 0.0f || (player.velocity.x == 0.0f && playerCenterX > tileCenterX)) 
            {
                player.sprite.setPosition({tileRect.position.x + tileRect.size.x + bounds.size.x / 2.0f + EPSILON, player.sprite.getPosition().y});
            }
            player.velocity.x = 0.0f; 
            break;
        }

   }
}
//отдельный класс коллизии
