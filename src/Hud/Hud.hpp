#pragma once
#include <SFML/Graphics.hpp>

struct Hud {
    sf::Font font;              
    sf::Text healthPoint;
    sf::Text dashCount; 
    
    Hud();
    void UpdateHud(int HP, int DC);
    void Draw(sf::RenderWindow &window);
};