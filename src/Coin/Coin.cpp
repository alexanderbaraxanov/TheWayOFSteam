#include "Coin.hpp"
#include "../Player/Player.hpp"

static sf::Texture CheckAndLoadTexture(const std::string& filepath)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filepath)) 
    {
        throw std::runtime_error("CRITICAL: Не удалось загрузить: " + filepath);
    }
    return texture;
}

Coins::Coins () 
: coinSprite(coinTexture) 
{
    coinTexture = CheckAndLoadTexture("../assets/coin.png");
    coins.clear();
    Coins::Coin coin;
    coin.position = {200.f, 200.f};
    coin.bounds = sf::FloatRect(coin.position, {static_cast<float>(FRAME_COIN_WIDTH), static_cast<float>(FRAME_COIN_HEIGHT)});
    coins.push_back(coin);
}

void CheckCoinCollisions(Player& player, std::vector<Coins::Coin> &coins) {
    const sf::FloatRect playerBounds = player.sprite.getGlobalBounds();

    for (Coins::Coin& coin : coins) {
        if (coin.isCollected) continue;

        if (playerBounds.findIntersection(coin.bounds).has_value()) 
        {
            coin.isCollected = true;
            player.countDash += COIN_VALUE;
        }
    }
}

void Delete(std::vector<Coins::Coin> &coins) 
{
    coins.erase(std::remove_if(coins.begin(), coins.end(), [](const Coins::Coin& c) { return c.isCollected; }),coins.end());
}

void Coins::Update(Player &player, float dt)
{
    CheckCoinCollisions(player, coins);
    Delete(coins);
    UpdateAnimation(dt);
}

void Coins::Render(sf::RenderWindow& window) 
{
    for (const Coin& coin : coins) {
        if (coin.isCollected) continue;

        coinSprite.setPosition(coin.position);
        window.draw(coinSprite);
    }
}