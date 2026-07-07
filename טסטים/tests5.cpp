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
    // לבן זז למעלה צעד אחד
    runTest("white pawn moves up one",
        "Board:\n. . .\nwP . .\n. . .\nCommands:\nclick 50 150\nclick 50 50\nprint board\n",
        "wP . .\n. . .\n. . .\n");

    // שחור זז למטה צעד אחד
    runTest("black pawn moves down one",
        "Board:\n. . .\nbP . .\n. . .\nCommands:\nclick 50 150\nclick 50 250\nprint board\n",
        ". . .\n. . .\nbP . .\n");

    // לבן זז שתיים מהשורה ההתחלתית
    runTest("white pawn moves two from start",
        "Board:\n. . .\n. . .\nwP . .\nCommands:\nclick 50 250\nclick 50 50\nprint board\n",
        "wP . .\n. . .\n. . .\n");

    // לבן לא יכול לזוז שתיים שלא מהשורה ההתחלתית
    runTest("white pawn cannot move two from non-start",
        "Board:\n. . .\nwP . .\n. . .\nCommands:\nclick 50 150\nclick 50 -50\nprint board\n",
        ". . .\nwP . .\n. . .\n");

    // לבן אוכל באלכסון
    runTest("white pawn captures diagonally",
        "Board:\n. bP .\nwP . .\n. . .\nCommands:\nclick 50 150\nclick 150 50\nprint board\n",
        ". wP .\n. . .\n. . .\n");

    // שחור אוכל באלכסון
    runTest("black pawn captures diagonally",
        "Board:\n. . .\nbP . .\n. wP .\nCommands:\nclick 50 150\nclick 150 250\nprint board\n",
        ". . .\n. . .\n. bP .\n");

    // לבן לא יכול לאכול קדימה
    runTest("white pawn cannot capture forward",
        "Board:\nbP . .\nwP . .\n. . .\nCommands:\nclick 50 150\nclick 50 50\nprint board\n",
        "bP . .\nwP . .\n. . .\n");

    // שחור לא יכול לאכול קדימה
    runTest("black pawn cannot capture forward",
        "Board:\n. . .\nbP . .\nwP . .\nCommands:\nclick 50 150\nclick 50 250\nprint board\n",
        ". . .\nbP . .\nwP . .\n");

    // לבן לא יכול לזוז למטה
    runTest("white pawn cannot move down",
        "Board:\n. . .\nwP . .\n. . .\nCommands:\nclick 50 150\nclick 50 250\nprint board\n",
        ". . .\nwP . .\n. . .\n");

    // שחור לא יכול לזוז למעלה
    runTest("black pawn cannot move up",
        "Board:\n. . .\nbP . .\n. . .\nCommands:\nclick 50 150\nclick 50 50\nprint board\n",
        ". . .\nbP . .\n. . .\n");

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return 0;
}
