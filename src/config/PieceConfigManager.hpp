#pragma once

#include "PieceConfig.hpp"
#include <string>
#include <map>

class PieceConfigManager {
public:
    explicit PieceConfigManager(const std::string& basePath);

    const AnimConfig& getConfig(const std::string& pieceCode,
                                const std::string& state);

private:
    std::string basePath;

    std::map<std::string, AnimConfig> cache;

    AnimConfig loadConfig(const std::string& pieceCode,
                          const std::string& state);

    AnimConfig parseConfig(const std::string& configPath);
};