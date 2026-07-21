#pragma once

#include "../src/game_engine/GameEngine.hpp"

#include <thread>
#include <chrono>

class GameLoop
{
public:

    GameLoop(GameEngine& engine);

    void start();


private:

    GameEngine& engine;
};