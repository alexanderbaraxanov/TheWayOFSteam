#pragma once
#include <SFML/Graphics.hpp>

struct Hud {
    sf::Font font;              
    sf::Text hudText; 
    
    Hud();
    void UpdateHud(int health);
    void Draw(sf::RenderWindow &window);
};