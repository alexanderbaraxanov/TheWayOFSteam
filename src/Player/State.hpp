#pragma once
#include <cstdint>

enum class State : uint8_t {
    Dead = 0,
    Idle  = 1,
    Running = 2,
    Jumping = 3,
    Falling = 4,
};