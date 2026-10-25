#include "Map.hpp"

bool CheckPos(float worldPos, float boundMap)
{
    return (worldPos < 0 || worldPos > boundMap);
}

void MapInit(Map& map)
{

}

bool MapIsSolid (const Map& map, float worldX, float worldY)
{

}

TileType MapGetTile(const Map& map, float worldX, float worldY)
{
    if (CheckPos(worldX, map.width) && CheckPos(worldY, map.height))
    {
        return TileType::Empty;
    }

    const auto row = static_cast<u_int32_t>(worldX) / TILE_SIZE;
    const auto col = static_cast<u_int32_t>(worldY) / TILE_SIZE;
    size_t index = (row * map.width) + col;

    return map.grid[index];
}