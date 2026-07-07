#include "commands.h"
#include <iostream>
#include <sstream>

static void handleClick(int x, int y, GameState& state) {
    int col = x / 100;
    int row = y / 100;

    if (row < 0 || row >= state.board.rows || col < 0 || col >= state.board.cols)
        return;

    std::string& cell = state.board.grid[row][col];
    bool hasSelection = state.selectedRow != -1;

    if (!hasSelection) {
        if (cell != ".") {
            state.selectedRow = row;
            state.selectedCol = col;
        }
        return;
    }

    // יש בחירה
    std::string& selected = state.board.grid[state.selectedRow][state.selectedCol];
    bool sameColor = (cell != "." && cell[0] == selected[0]);

    if (sameColor) {
        state.selectedRow = row;
        state.selectedCol = col;
    } else {
        cell = selected;
        selected = ".";
        state.selectedRow = -1;
        state.selectedCol = -1;
    }
}

void runCommands(const std::vector<std::string>& commands, GameState& state) {
    for (const std::string& cmd : commands) {
        if (cmd == "print board") {
            for (const auto& row : state.board.grid) {
                for (int i = 0; i < (int)row.size(); i++) {
                    if (i > 0) std::cout << " ";
                    std::cout << row[i];
                }
                std::cout << "\n";
            }
        } else if (cmd.substr(0, 5) == "click") {
            int x, y;
            std::istringstream ss(cmd.substr(6));
            ss >> x >> y;
            handleClick(x, y, state);
        } else if (cmd.substr(0, 4) == "wait") {
            int ms;
            std::istringstream ss(cmd.substr(5));
            ss >> ms;
            state.clock += ms;
        }
    }
}
