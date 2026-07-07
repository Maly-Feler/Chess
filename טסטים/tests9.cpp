#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../דפים/board.h"
#include "../דפים/commands.h"

int passed = 0;
int failed = 0;

void runTest(const std::string& testName, const std::string& input, const std::string& expected) {
    std::istringstream ss(input);
    std::string line;
    std::getline(ss, line); // "Board:"

    std::vector<std::string> boardLines;
    while (std::getline(ss, line) && line != "Commands:") {
        boardLines.push_back(line);
    }

    std::vector<std::string> commands;
    while (std::getline(ss, line)) {
        if (!line.empty()) commands.push_back(line);
    }

    std::streambuf* oldBuf = std::cout.rdbuf();
    std::ostringstream out;
    std::cout.rdbuf(out.rdbuf());

    GameState state;
    std::string error;
    if (!parseBoard(boardLines, state.board, error)) {
        std::cout << error << "\n";
    } else {
        runCommands(commands, state);
    }

    std::cout.rdbuf(oldBuf);

    if (out.str() == expected) {
        std::cout << "[PASS] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        std::cout << "  expected: " << expected;
        std::cout << "  got:      " << out.str();
        failed++;
    }
}

int main() {
    // לבן אוכל מלך שחור
    runTest("white captures black king",
        "Board:\nwR . bK\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        ". . wR\n");

    // אחרי סוף משחק - פקודות מתעלמות
    runTest("no moves after game over",
        "Board:\nwR . bK\nbR . .\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nclick 50 150\nclick 150 150\nwait 1000\nprint board\n",
        ". . wR\nbR . .\n");

    // שחור אוכל מלך לבן
    runTest("black captures white king",
        "Board:\nbR . wK\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        ". . bR\n");

    // אחרי סוף משחק - print board עדיין עובד
    runTest("print board works after game over",
        "Board:\nwR . bK\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\nprint board\n",
        ". . wR\n. . wR\n");

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return 0;
}
