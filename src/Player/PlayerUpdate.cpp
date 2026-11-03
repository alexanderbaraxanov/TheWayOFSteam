void UpdateJerkTimer(float &timer, float dt)
{
    if (timer > 0.f)
    {
        timer -= dt;
    }
}

void UpdateHealth(float &health, float dt)
{
    health -= 50 * dt; //переписать функцию для урона
}

void UpdateJerkCounter(int &counter) //dash перименовать 
{
    counter += 1; 
}

void Player::Update(const Map& map, const float dt)
{
    PlayerMoving(*this, map, dt);
    PlayerJumping(*this, map, dt);

    SpriteFlipping(*this);
    if(map.IsSpike(sprite.getPosition().x, sprite.getPosition().y) && state != PlayerState::Dead)
    {
        UpdateHealth(health, dt);
    }
    if(map.IsJerkCoin(sprite.getPosition().x, sprite.getPosition().y) && state != PlayerState::Dead)
    {
        UpdateJerkCounter(countJerk);
    }

    UpdateJerkTimer(jerkTimer, dt);
    UpdateState();
}
