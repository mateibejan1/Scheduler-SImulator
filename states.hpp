#pragma once

#include <cstdint>

enum class State : uint8_t
{
    E_READY = 0,
    E_RESPONDED,
    E_WAITING_FOR_IO,
    E_TERMINATED
};
