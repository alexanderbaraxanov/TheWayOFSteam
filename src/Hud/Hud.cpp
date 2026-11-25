#include "./Hud.hpp"

static sf::Font CheckAndLoadFont(const std::string& filepath)
{
    sf::Font font;
    if (!font.openFromFile(filepath)) 
    {
        throw std::runtime_error("CRITICAL: Не удалось загрузить: " + filepath);
    }
    return font;
}
      

Hud::Hud() 
    :font(CheckAndLoadFont("../fonts/Pencils.ttf"))
    , healthPoint(font, "Health", 30)
    , dashCount(font, "Dash", 30)
{
    healthPoint.setCharacterSize(24);
    healthPoint.setFillColor(sf::Color::Red);
    healthPoint.setStyle(sf::Text::Bold);
    healthPoint.setPosition({20.0f, 15.0f});

    dashCount.setCharacterSize(24);
    dashCount.setFillColor(sf::Color::White);
    dashCount.setStyle(sf::Text::Bold);
    dashCount.setPosition({20.0f, 40.0f});
}

void Hud::UpdateHud(int HP, int DC) 
{
    healthPoint.setString("Health " + std::to_string(HP));
    dashCount.setString("Dash " + std::to_string(DC));
}

void Hud::Draw(sf::RenderWindow &window) 
{
    window.draw(healthPoint);
    window.draw(dashCount);
}
