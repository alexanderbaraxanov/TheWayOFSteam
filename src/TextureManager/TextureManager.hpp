#pragma once

#include "SFML/Graphics.hpp"

struct TextureBank {
    public:
        sf::Texture tilesetTexture; 
        sf::Texture playerTexture;
        sf::Texture strikerTexture;
        sf::Texture steamerTexture;
        sf::Texture coinTexture;

        TextureBank() 
        : tilesetTexture(CheckAndLoadTexture("../assets/tileset.png"))
        , playerTexture(CheckAndLoadTexture("../assets/player.png"))
        , strikerTexture(CheckAndLoadTexture("../assets/enemyStriker.png"))
        , steamerTexture(CheckAndLoadTexture("../assets/enemySteamer.png"))
        , coinTexture(CheckAndLoadTexture("../assets/coin.png"))
        {}
    private:
        sf::Texture CheckAndLoadTexture(const std::string& filepath)
        {
            sf::Texture texture;
            if (!texture.loadFromFile(filepath)) 
            {
                throw std::runtime_error("CRITICAL: Не удалось загрузить: " + filepath);
            }
            return texture;
        }
};