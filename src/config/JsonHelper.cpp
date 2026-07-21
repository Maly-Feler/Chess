#include "JsonHelper.hpp"

std::string JsonHelper::extractStr(
    const std::string& content,
    const std::string& key)
{
    auto pos = content.find("\"" + key + "\"");

    if (pos == std::string::npos)
        return "";

    pos = content.find(":", pos);
    pos = content.find("\"", pos);

    auto end = content.find("\"", pos + 1);

    return content.substr(pos + 1, end - pos - 1);
}


int JsonHelper::extractInt(
    const std::string& content,
    const std::string& key)
{
    auto pos = content.find("\"" + key + "\"");

    if (pos == std::string::npos)
        return 0;

    pos = content.find(":", pos) + 1;

    while (pos < content.size() && !isdigit(content[pos]))
        pos++;

    return std::stoi(content.substr(pos));
}


bool JsonHelper::extractBool(
    const std::string& content,
    const std::string& key)
{
    auto pos = content.find("\"" + key + "\"");

    if (pos == std::string::npos)
        return true;

    pos = content.find(":", pos) + 1;

    while (pos < content.size() && content[pos] == ' ')
        pos++;

    return content.substr(pos, 4) == "true";
}


double JsonHelper::extractDouble(
    const std::string& content,
    const std::string& key)
{
    auto pos = content.find("\"" + key + "\"");

    if (pos == std::string::npos)
        return 0;

    pos = content.find(":", pos) + 1;

    while (pos < content.size() &&
          (content[pos] == ' ' || content[pos] == '\t'))
        pos++;

    size_t end = pos;

    while (end < content.size() &&
          (isdigit(content[end]) || content[end] == '.'))
        end++;

    return std::stod(content.substr(pos, end - pos));
}