#pragma once

#include "AnimConfig.hpp"
#include "PieceConfigManager.hpp"
#include "../game_engine/PieceStatus.hpp"
#include <string>


class AnimationConfigProvider
{
public:

    explicit AnimationConfigProvider();

    const AnimConfig& getConfig(
        const std::string& pieceCode,
        const PieceStatus& state
    );

private:

    PieceConfigManager configManager;
};