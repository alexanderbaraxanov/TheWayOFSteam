#pragma once 

#include <SFML/Audio.hpp>

struct SoundBank {
    public:
        sf::SoundBuffer deadBuffer;
        sf::SoundBuffer runBuffer;
        sf::SoundBuffer jumpBuffer;
        sf::SoundBuffer dashBuffer;
        sf::SoundBuffer coinBuffer;

        sf::Sound coinSound;
        sf::Sound deadSound;
        sf::Sound runSound;
        sf::Sound jumpSound;
        sf::Sound dashSound;

        sf::Music gMusic;

    SoundBank() 
        : deadSound(deadBuffer)
        , runSound(runBuffer)
        , jumpSound(jumpBuffer)
        , dashSound(dashBuffer)
        , coinSound(coinBuffer)
    {
        if (!deadBuffer.loadFromFile("../assets/sounds/dead.wav") ||
            !runBuffer.loadFromFile("../assets/sounds/run.wav") ||
            !jumpBuffer.loadFromFile("../assets/sounds/jump.wav") ||
            !dashBuffer.loadFromFile("../assets/sounds/dash.wav") ||
            !coinBuffer.loadFromFile("../assets/sounds/coin.wav"))
        {
            throw std::runtime_error("CRITICAL: audio");
        }
        deadSound.setVolume(75.f);
        runSound.setVolume(75.f);
        jumpSound.setVolume(75.f);
        dashSound.setVolume(75.f);
        coinSound.setVolume(75.f);


        if (gMusic.openFromFile("../assets/sounds/music.ogg")) 
        {
            gMusic.setLooping(true);
            gMusic.setVolume(25.0f); 
            gMusic.play();
        }
    }

    sf::SoundBuffer CheckAndLoadSound(const std::string& filepath)
    {
        sf::SoundBuffer soundBuffer;
        if (!soundBuffer.loadFromFile(filepath)) 
        {
            throw std::runtime_error("CRITICAL: audio. Не удалось загрузить: " + filepath);
        }
        return soundBuffer;
    }

    void setSound()
    {

    }
};