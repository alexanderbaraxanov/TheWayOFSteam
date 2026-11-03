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
    , hudText(font, "Health", 30)
{
    hudText.setCharacterSize(24);
    hudText.setFillColor(sf::Color::Red);
    hudText.setStyle(sf::Text::Bold);
    hudText.setPosition({20.0f, 15.0f});
}

void Hud::UpdateHud(int health) 
{
    hudText.setString("Health " + std::to_string(health));
}

void Hud::Draw(sf::RenderWindow &window) 
{
    window.draw(hudText);
}
