#pragma once
#include <string>

struct AnimConfig {
    int fps = 6;
    bool isLoop = true;
    std::string nextState = "idle";
};
