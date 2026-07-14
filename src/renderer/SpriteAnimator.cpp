#include "SpriteAnimator.hpp"

SpriteAnimator::SpriteAnimator(const std::string& pieceCode, SpriteLoader& loader)
    : pieceCode(pieceCode), loader(loader) {
    enterState("idle");
}

void SpriteAnimator::tick(int dt) {
    const AnimConfig& cfg = loader.getConfig(pieceCode, state);
    msAccum += dt;
    int msPerFrame = (cfg.fps > 0) ? (1000 / cfg.fps) : 1000;

    while (msAccum >= msPerFrame) {
        msAccum -= msPerFrame;
        currentFrame++;
        int frameCount = (int)loader.getFrames(pieceCode, state).size();
        if (currentFrame >= frameCount) {
            if (cfg.isLoop) {
                currentFrame = 0;
            } else {
                currentFrame = frameCount - 1;
                enterState(cfg.nextState);
                return;
            }
        }
    }
}

void SpriteAnimator::setState(const std::string& newState) {
    // rest states finish on their own via config.nextState - don't interrupt
    if (state == "short_rest" || state == "long_rest") return;
    if (newState != state)
        enterState(newState);
}

const std::string& SpriteAnimator::getState() const { return state; }

const Img& SpriteAnimator::currentImg() const {
    return loader.getFrames(pieceCode, state)[currentFrame];
}

void SpriteAnimator::enterState(const std::string& newState) {
    state        = newState;
    currentFrame = 0;
    msAccum      = 0;
}
