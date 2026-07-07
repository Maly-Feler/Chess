#pragma once
#include <string>
#include <vector>

struct Board {
    std::vector<std::vector<std::string>> grid;
    int rows;
    int cols;
};

struct GameState {
    Board board;
    int selectedRow = -1;
    int selectedCol = -1;
    int clock = 0;
};

bool parseBoard(const std::vector<std::string>& lines, Board& board, std::string& error);
