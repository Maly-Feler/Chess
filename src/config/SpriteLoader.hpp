#pragma once
#include "../../cpp/src/img.hpp"
#include "../arbiter/Motion.hpp"
#include "../config/AnimConfig.hpp"
#include "../config/PieceConfigManager.hpp"
#include "../model/Piece.hpp"
#include <string>
#include <vector>
#include <map>

class SpriteLoader {
public:
    explicit SpriteLoader(const std::string& basePath) : basePath(basePath) {}

    PieceConfigManager configManager{"assets/pieces2"};

    const std::vector<Img>& getFrames(const std::string& pieceCode,
                                      const PieceStatus& state);

private:
    std::string basePath;

    struct Entry {
        std::vector<Img> frames;
        AnimConfig config;
    };

    std::map<std::string, Entry> cache;  // key: "PW/idle"

    Entry load(const std::string& pieceCode, const PieceStatus& state);
};
