#pragma once
#include <string>
#include "../arbiter/Motion.hpp"

struct AnimConfig {
    int fps = 0;
    bool isLoop = true;
    PieceStatus nextState;
    double speed_m_per_sec = 0;
};