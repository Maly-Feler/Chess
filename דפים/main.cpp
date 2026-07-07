#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "commands.h"

static std::string trim(const std::string& s) {
    int start = 0;
    while (start < (int)s.size() && s[start] == ' ') start++;
    return s.substr(start);
}

int main() {
    std::string line;

    // קרא עד שמוצאים "Board:"
    while (std::getline(std::cin, line)) {
        if (trim(line) == "Board:") break;
    }

    std::vector<std::string> boardLines;
    while (std::getline(std::cin, line) && trim(line) != "Commands:") {
        boardLines.push_back(line);
    }

    std::vector<std::string> commands;
    while (std::getline(std::cin, line)) {
        std::string t = trim(line);
        if (!t.empty()) commands.push_back(t);
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
