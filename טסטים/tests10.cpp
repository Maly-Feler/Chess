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
    // 1. לבן זז 2 צעדים מהשורה ההתחלתית
    runTest("white pawn double from start valid",
        "Board:\n. . .\n. . .\n. . .\n. wP .\nCommands:\nclick 150 350\nclick 150 150\nwait 2000\nprint board\n",
        ". . .\n. wP .\n. . .\n. . .\n");

    // 2. שחור זז 2 צעדים מהשורה ההתחלתית
    runTest("black pawn double from start valid",
        "Board:\n. bP .\n. . .\n. . .\n. . .\nCommands:\nclick 150 50\nclick 150 250\nwait 2000\nprint board\n",
        ". . .\n. . .\n. bP .\n. . .\n");

    // 3. מסלול חסום — לא יכול לזוז 2
    runTest("white pawn double blocked by piece in middle",
        "Board:\n. . .\n. . .\n. bP .\n. wP .\nCommands:\nclick 150 350\nclick 150 150\nwait 2000\nprint board\n",
        ". . .\n. . .\n. bP .\n. wP .\n");

    // 4. לבן לא מהשורה ההתחלתית — לא יכול לזוז 2
    runTest("white pawn double from non-start invalid",
        "Board:\n. . .\n. . .\n. wP .\n. . .\nCommands:\nclick 150 250\nclick 150 50\nwait 2000\nprint board\n",
        ". . .\n. . .\n. wP .\n. . .\n");

    // 5. לבן מגיע לשורה האחרונה — הופך לווזיר
    runTest("white pawn promotes to queen",
        "Board:\n. . .\n. wP .\n. . .\nCommands:\nclick 150 150\nclick 150 50\nwait 1000\nprint board\n",
        ". wQ .\n. . .\n. . .\n");

    // 6. שחור מגיע לשורה האחרונה — הופך לווזיר
    runTest("black pawn promotes to queen",
        "Board:\n. . .\n. bP .\n. . .\nCommands:\nclick 150 150\nclick 150 250\nwait 1000\nprint board\n",
        ". . .\n. . .\n. bQ .\n");

    // 7. לבן זז צעד אחד רגיל
    runTest("white pawn single step valid",
        "Board:\n. . .\n. . .\n. wP .\nCommands:\nclick 150 250\nclick 150 150\nwait 1000\nprint board\n",
        ". . .\n. wP .\n. . .\n");

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return 0;
}
