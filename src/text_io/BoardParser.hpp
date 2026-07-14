#pragma once
#include "../model/Board.hpp"
#include <vector>
#include <string>

class BoardParser {
public:
    bool parse(const std::vector<std::string>& lines, Board& board, std::string& error) const;
};
