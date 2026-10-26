#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TileType.hpp"

constexpr uint32_t TILE_SIZE = 50; 
constexpr uint32_t MAP_WIDTH = 30;
constexpr uint32_t MAP_HEIGHT = 20;

struct Map {
    std::vector<TileType> grid; 
    uint32_t width = 0;         
    uint32_t height = 0;        
    sf::Texture tilesetTexture; 

    Map(const std::vector<std::string>& tileMap);
    void Draw(sf::RenderWindow& window) const;

    TileType GetTile(float worldX, float worldY) const;
    bool IsSolid (float worldX, float worldY) const;
    bool IsSpike(float worldX, float worldY) const;
};
