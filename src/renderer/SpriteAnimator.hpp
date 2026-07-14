#pragma once
#include "SpriteLoader.hpp"
#include <string>

// Manages animation state machine for a single piece
// States: idle, move, jump, short_rest, long_rest
class SpriteAnimator {
public:
    SpriteAnimator(const std::string& pieceCode, SpriteLoader& loader);

    void tick(int dt);                          // advance animation by dt ms
    void setState(const std::string& newState); // called by renderer from snapshot
    const std::string& getState() const;
    const Img& currentImg() const;

private:
    std::string   pieceCode;
    SpriteLoader& loader;
    std::string   state;
    int           currentFrame = 0;
    int           msAccum      = 0;

    void enterState(const std::string& newState);
};
