#pragma once
#include <cstdint>

enum class State : uint8_t {
    Idle  = 1,
    Running = 2,
    Jumping = 3,
    Falling = 4,
};