#include "PieceConfigManager.hpp"

PieceConfigManager::PieceConfigManager(const std::string& basePath)
    : basePath(basePath)
{
}


const AnimConfig& PieceConfigManager::getConfig(const std::string& pieceCode,
    const PieceStatus& state)
{
    std::string key = pieceCode + "/" + std::to_string(static_cast<int>(state));

    if (cache.find(key) == cache.end())
        cache[key] = loadConfig(pieceCode, state);

    return cache[key];
}


AnimConfig PieceConfigManager::loadConfig(
    const std::string& pieceCode,
    const PieceStatus& state)
{
    std::string path =
        basePath + "/" +
        pieceCode +
        "/states/" +
        PieceStatusToString(state) +
        "/config.json";

    return parseConfig(path);
}

AnimConfig PieceConfigManager::parseConfig(
    const std::string& configPath)
{
    std::ifstream f(configPath);

    if (!f)
        throw std::runtime_error("Cannot open: " + configPath);

    std::string content(
        (std::istreambuf_iterator<char>(f)),
        std::istreambuf_iterator<char>()
    );

    AnimConfig cfg;

    cfg.fps =
        JsonHelper::extractInt(content, "frames_per_sec");

    cfg.isLoop =
        JsonHelper::extractBool(content, "is_loop");

    cfg.nextState =
        StringToPieceStatus(
            JsonHelper::extractStr(
                content,
                "next_state_when_finished"
            )
        );

    cfg.speed_m_per_sec =
        JsonHelper::extractDouble(
            content,
            "speed_m_per_sec"
        );

    return cfg;
}
