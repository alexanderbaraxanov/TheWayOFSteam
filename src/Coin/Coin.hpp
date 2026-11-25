#pragma once

#include "SFML/Graphics.hpp"

constexpr int COIN_VALUE = 1;
constexpr int FRAME_COIN_WIDTH = 36;
constexpr int FRAME_COIN_HEIGHT = 36;

struct Player;

struct Coins {
  struct Coin {
      sf::Vector2f position;          
      sf::FloatRect bounds;           
      int currentFrame{0};          
      float animationTimer{0.0f};     
      bool isCollected{false}; 
   };
   sf::Texture coinTexture;
   sf::Sprite coinSprite;

   std::vector<Coin> coins;

   Coins();

   void UpdateAnimation(float dt);
   void Update(Player &player, float dt);
   void Render(sf::RenderWindow &window);
};

