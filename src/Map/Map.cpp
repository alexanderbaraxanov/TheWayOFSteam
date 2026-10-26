#include "Map.hpp"

bool CheckPos(float worldPos, float boundMap)
{
    return (worldPos < 0 || worldPos > boundMap * TILE_SIZE);
}

sf::Texture CheckAndLoadTexture(const std::string& filepath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filepath)) 
    {
        throw std::runtime_error("CRITICAL: Не удалось загрузить: " + filepath);
    }
    return texture;
}

Map::Map(const std::vector<std::string>& tileMap)
    : height(MAP_HEIGHT)
    , width(MAP_WIDTH)
    , tilesetTexture(CheckAndLoadTexture("../assets/tileset.png"))
{
    grid.resize(width * height, TileType::Empty);
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            size_t i = y * width + x;
            if (y < tileMap.size() && x < tileMap[y].size())
            {
                switch (tileMap[y][x])
                {
                case '0':
                    grid[i] = TileType::Empty;
                    break;

                case '1':
                    grid[i] = TileType::Solid;
                    break;

                case '2':
                    grid[i] = TileType::Platform;
                    break;

                case '3':
                    grid[i] = TileType::Spike;
                    break;
                
                }
            }
        }
    }    
}

bool Map::IsSolid (float worldX, float worldY) const
{
    return GetTile(worldX, worldY) == TileType::Solid;
}

bool Map::IsSpike(float worldX, float worldY) const
{
    return GetTile(worldX, worldY) == TileType::Spike;
}

TileType Map::GetTile(float worldX, float worldY) const
{
    if (CheckPos(worldX, width) || CheckPos(worldY, height))
    {
        return TileType::Empty;
    }

    const auto row = static_cast<uint32_t>(worldY) / TILE_SIZE;
    const auto col = static_cast<uint32_t>(worldX) / TILE_SIZE;
    size_t index = (row * width) + col;

    return grid[index];
}

sf::IntRect CalculateTileRect(uint32_t tileId, uint32_t tileSize, uint32_t atlasColumns) {
   const int left = static_cast<int>((tileId % atlasColumns) * tileSize);
   const int top  = static_cast<int>((tileId / atlasColumns) * tileSize);
  
   return sf::IntRect({left, top}, {static_cast<int>(tileSize), static_cast<int>(tileSize)});
}


void Map::Draw(sf::RenderWindow& window) const 
{
    sf::Sprite tileSprite(tilesetTexture);

    const uint32_t atlasColumns = 2; 

    for (size_t i = 0; i < grid.size(); ++i) {
        if (grid[i] == TileType::Empty) continue;

        const float x = static_cast<float>((i % width) * TILE_SIZE);
        const float y = static_cast<float>((i / width) * TILE_SIZE);

        uint32_t tileId = static_cast<uint32_t>(grid[i]);

        tileSprite.setTextureRect(CalculateTileRect(tileId, TILE_SIZE, atlasColumns));
        
        tileSprite.setPosition({x, y});
        window.draw(tileSprite);
    }
}