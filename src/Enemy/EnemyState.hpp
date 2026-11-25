#pragma once

#include <cstdint>

enum class EnemyState : uint8_t 
{
    Idle = 0,
    Dead = 1,
    Running = 2,
    Falling = 3,
    Hitting = 4,
};