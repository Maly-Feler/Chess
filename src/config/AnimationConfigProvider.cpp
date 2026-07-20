#include "AnimationConfigProvider.hpp"


AnimationConfigProvider::AnimationConfigProvider() : configManager("assets/pieces2")
{
}


const AnimConfig& AnimationConfigProvider::getConfig(
    const std::string& pieceCode,
    const PieceStatus& state)
{
    return configManager.getConfig(pieceCode, state);
}