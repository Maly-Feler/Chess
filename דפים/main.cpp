#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "commands.h"

int main() {
    std::string line;
    std::getline(std::cin, line); // "Board:"

    std::vector<std::string> boardLines;
    while (std::getline(std::cin, line) && line != "Commands:") {
        boardLines.push_back(line);
    }

    std::vector<std::string> commands;
    while (std::getline(std::cin, line)) {
        if (!line.empty()) commands.push_back(line);
    }

    GameState state;
    std::string error;
    if (!parseBoard(boardLines, state.board, error)) {
        std::cout << error << "\n";
        return 0;
    }

    runCommands(commands, state);
    return 0;
}
