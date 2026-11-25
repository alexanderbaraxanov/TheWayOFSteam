#include "./CollisonHandler.hpp"
#include "../Player/Player.hpp"

constexpr float EPSILON = 0.001f;

bool CheckCollision(const sf::FloatRect& a, const sf::FloatRect& b) 
{
    return a.findIntersection(b).has_value();
}

namespace Collison 
{
    void ResolveCollisionsY(const Map& map, Player& player) 
    {
        player.isGround = false; 
        for (const auto& tileRect : map.GetNearbySolidTiles(player.hitbox)) {
            if (CheckCollision(player.hitbox, tileRect)) 
            {
                if (player.velocity.y > 0.0f || (player.velocity.y == 0.0f && player.hitbox.position.y < tileRect.position.y)) 
                { 
                    player.sprite.setPosition({player.hitbox.position.x, tileRect.position.y - player.hitbox.size.y / 2.0f});
                    player.isGround = true;   
                } 
                else if (player.velocity.y < 0.0f) 
                { 
                    player.sprite.setPosition({player.hitbox.position.x, tileRect.position.y + tileRect.size.y + player.hitbox.size.y / 2.0f + EPSILON});
                }
                player.velocity.y = 0.0f;
                break;
            }
        }
    }


    void ResolveCollisionsX(const Map& map, Player& player) 
    {
        sf::FloatRect bounds = player.sprite.getGlobalBounds();
        for (const auto& tileRect : map.GetNearbySolidTiles(player.hitbox)) 
        {
            if (CheckCollision(player.hitbox, tileRect)) 
            {
                float playerCenterX = player.sprite.getPosition().x;
                float tileCenterX = tileRect.position.x + tileRect.size.x / 2.0f;
                if (player.velocity.x > 0.0f || (player.velocity.x == 0.0f && playerCenterX < tileCenterX)) {
                    player.sprite.setPosition({tileRect.position.x - player.hitbox.size.x / 2.0f - EPSILON, player.hitbox.position.y});
                } 
                else if (player.velocity.x < 0.0f || (player.velocity.x == 0.0f && playerCenterX > tileCenterX)) 
                {
                    player.sprite.setPosition({tileRect.position.x + tileRect.size.x + player.hitbox.size.x / 2.0f + EPSILON, player.hitbox.position.y});
                }
                player.velocity.x = 0.0f; 
                break;
            }
        }
    }
}