#include <SFML/Graphics.hpp>
#include "../Game/Game.hpp"

constexpr int IDLE_FRAMES = 1;
constexpr int RUN_FRAMES = 7;
constexpr int JUMP_FRAMES = 1;
constexpr int FALLING_FRAMES = 1;
constexpr int DASHING_FRAMES = 1;
constexpr int DEAD_FRAMES = 0;

sf::IntRect CalculateFrameRect(int frameIndex, int row, int frameWidth, int frameHeight) {
   const int left = frameIndex * frameWidth;
   const int top  = row * frameHeight;
   return sf::IntRect({left, top}, {frameWidth, frameHeight});
}

void Player::UpdateAnimation(float dt) {
    int row = 0;          
    int totalFrames = 1;  

    switch (state) {
        case PlayerState::Idle:
            row = 0;          
            totalFrames = IDLE_FRAMES;  
            break;
        case PlayerState::Running:
            row = 1;          
            totalFrames = RUN_FRAMES; 
            break;
        case PlayerState::Jumping:
            row = 2;          
            totalFrames = JUMP_FRAMES;  
            break;
        case PlayerState::Falling:
            row = 3;          
            totalFrames = FALLING_FRAMES;  
            break;
        case PlayerState::Dashing:
            row = 4;          
            totalFrames = DASHING_FRAMES;  
            break;
        // case PlayerState::Dead:
        //     row = 4;          
        //     totalFrames = DEAD_FRAMES;
        //     break;
    }

    static PlayerState previousState = state;
    if (state != previousState) {
        currentFrame = 0;
        animationTimer = 0.0f;
        previousState = state;
    }

    animationTimer += dt;
    if (animationTimer >= FRAME_TIME) 
    {
        animationTimer -= FRAME_TIME; 
        currentFrame = (currentFrame + 1) % totalFrames; //вынести как общую
    }

    sf::IntRect frameRect = CalculateFrameRect(currentFrame, row, FRAME_PLAYER_WIDTH, FRAME_PLAYER_HEIGHT);
    sprite.setTextureRect(frameRect);
}

void Player::InitGraphics(int frameWidth, int frameHeight) 
{
    sprite.setOrigin({frameWidth / 2.0f, frameHeight / 2.0f});
}