#pragma once

#include <string>

class JsonHelper {
public:
    static std::string extractStr(
        const std::string& content,
        const std::string& key
    );

    static int extractInt(
        const std::string& content,
        const std::string& key
    );

    static bool extractBool(
        const std::string& content,
        const std::string& key
    );

    static double extractDouble(
        const std::string& content,
        const std::string& key
    );
};