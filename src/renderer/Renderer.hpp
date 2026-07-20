#pragma once
#include "./game_engine/GameSnapshot.hpp"
#include "../controllerClick/CellPos.hpp"

class Renderer {
public:
    virtual void render(const GameSnapshot& snap) {}
    virtual ~Renderer() = default;
};
