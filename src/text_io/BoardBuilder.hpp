#pragma once
#include "../model/Board.hpp"
#include <string>

class BoardBuilder {
public:
    bool build(const std::string& input, Board& board, std::string& error) const;
};
