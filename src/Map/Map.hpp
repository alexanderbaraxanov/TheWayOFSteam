#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include "fstream"
#include "iostream"
#include "TileType.hpp"

class Game;

constexpr uint32_t TILE_SIZE = 50; 
constexpr uint32_t MAP_WIDTH = 51;
constexpr uint32_t MAP_HEIGHT = 20;

struct Map {
    std::vector<TileType> grid; 
    uint32_t width = 0;         
    uint32_t height = 0;
    sf::Sprite tileSprite;
    uint32_t atlasColumns;

    Map(const std::string &filepath, Game& game);
    void Draw(sf::RenderWindow& window);

    TileType GetTile(float worldX, float worldY) const;
    void SetTile(float worldX, float worldY, TileType tile, int type) const;
    bool IsSolid (float worldX, float worldY) const;
    bool IsSpike(float worldX, float worldY) const;
    bool IsDashCoin(float worldX, float worldY) const;
    bool IsExit(float worldX, float worldY) const;
    std::vector<sf::FloatRect> GetNearbySolidTiles(const sf::FloatRect& bounds) const;
};
