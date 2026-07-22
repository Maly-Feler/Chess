#include "AnimationConfigProvider.hpp"


AnimationConfigProvider::AnimationConfigProvider() : configManager("assets/image")
{
}


const AnimConfig& AnimationConfigProvider::getConfig(
    const std::string& pieceCode,
    const PieceStatus& state)
{
    return configManager.getConfig(pieceCode, state);
}