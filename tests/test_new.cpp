#include <iostream>
#include <sstream>
#include <string>
#include "text_test_runner/TextTestRunner.hpp"

int passed = 0;
int failed = 0;

void runTest(const std::string& name, const std::string& input, const std::string& expected) {
    std::istringstream ss(input);
    std::streambuf* old = std::cout.rdbuf();
    std::ostringstream out;
    std::cout.rdbuf(out.rdbuf());

    TextTestRunner().run(ss);

    std::cout.rdbuf(old);

    if (out.str() == expected) {
        std::cout << "[PASS] " << name << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << name << "\n";
        std::cout << "  expected: " << expected;
        std::cout << "  got:      " << out.str();
        failed++;
    }
}

int main() {
    std::cout << "=== BoardParser ===\n";

    runTest("valid 3x4 board",
        "Board:\nwK . . bK\n. . . .\nwR . . bR\nCommands:\nprint board\n",
        "wK . . bK\n. . . .\nwR . . bR\n");

    runTest("valid 1x1 board",
        "Board:\n.\nCommands:\nprint board\n",
        ".\n");

    runTest("valid 8x8 board",
        "Board:\nwR wN wB wQ wK wB wN wR\nwP wP wP wP wP wP wP wP\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\nbP bP bP bP bP bP bP bP\nbR bN bB bQ bK bB bN bR\nCommands:\nprint board\n",
        "wR wN wB wQ wK wB wN wR\nwP wP wP wP wP wP wP wP\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\nbP bP bP bP bP bP bP bP\nbR bN bB bQ bK bB bN bR\n");

    runTest("unknown token",
        "Board:\nwK xZ\n. .\nCommands:\n",
        "ERROR UNKNOWN_TOKEN\n");

    runTest("uppercase token invalid",
        "Board:\nWK .\n. .\nCommands:\n",
        "ERROR UNKNOWN_TOKEN\n");

    runTest("invalid color token",
        "Board:\nxK .\n. .\nCommands:\n",
        "ERROR UNKNOWN_TOKEN\n");

    runTest("row width mismatch",
        "Board:\nwK . .\n. bK\nCommands:\n",
        "ERROR ROW_WIDTH_MISMATCH\n");

    std::cout << "\n=== controllerClick: קליקים ובחירה ===\n";

    runTest("click empty cell no selection ignored",
        "Board:\nwK .\n. .\nCommands:\nclick 150 50\nprint board\n",
        "wK .\n. .\n");

    runTest("click selects piece",
        "Board:\nwK .\n. .\nCommands:\nclick 50 50\nprint board\n",
        "wK .\n. .\n");

    runTest("click outside board ignored",
        "Board:\nwK .\n. .\nCommands:\nclick 50 50\nclick 9999 9999\nprint board\n",
        "wK .\n. .\n");

    runTest("click negative coords clears selection",
        "Board:\nwK .\n. .\nCommands:\nclick 50 50\nclick -1 -1\nprint board\n",
        "wK .\n. .\n");

    runTest("click friendly piece reselects",
        "Board:\nwK wR\n. .\nCommands:\nclick 50 50\nclick 150 50\nprint board\n",
        "wK wR\n. .\n");

    runTest("click same cell twice triggers jump",
        "Board:\nwK .\n. .\nCommands:\nclick 50 50\nclick 50 50\nprint board\n",
        "wK .\n. .\n");

    std::cout << "\n=== RuleEngine: חוקי תנועה ===\n";

    runTest("king moves one step",
        "Board:\nwK . .\nCommands:\nclick 50 50\nclick 150 50\nwait 1000\nprint board\n",
        ". wK .\n");

    runTest("king cannot move two steps",
        "Board:\nwK . .\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        "wK . .\n");

    runTest("rook moves straight",
        "Board:\nwR . .\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        ". . wR\n");

    runTest("rook blocked by piece",
        "Board:\nwR wP .\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        "wR wP .\n");

    runTest("rook captures enemy",
        "Board:\nwR bR .\nCommands:\nclick 50 50\nclick 150 50\nwait 1000\nprint board\n",
        ". wR .\n");

    runTest("rook cannot capture friendly",
        "Board:\nwR wK .\nCommands:\nclick 50 50\nclick 150 50\nwait 1000\nprint board\n",
        "wR wK .\n");

    runTest("bishop moves diagonal",
        "Board:\nwB . .\n. . .\n. . .\nCommands:\nclick 50 50\nclick 250 250\nwait 2000\nprint board\n",
        ". . .\n. . .\n. . wB\n");

    runTest("bishop blocked by piece",
        "Board:\nwB . .\n. wP .\n. . .\nCommands:\nclick 50 50\nclick 250 250\nwait 2000\nprint board\n",
        "wB . .\n. wP .\n. . .\n");

    runTest("bishop captures enemy",
        "Board:\nwB . .\n. bP .\n. . .\nCommands:\nclick 50 50\nclick 150 150\nwait 1000\nprint board\n",
        ". . .\n. wB .\n. . .\n");

    runTest("queen moves straight",
        "Board:\nwQ . .\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        ". . wQ\n");

    runTest("queen moves diagonal",
        "Board:\nwQ . .\n. . .\n. . .\nCommands:\nclick 50 50\nclick 250 250\nwait 2000\nprint board\n",
        ". . .\n. . .\n. . wQ\n");

    runTest("queen blocked",
        "Board:\nwQ wP .\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        "wQ wP .\n");

    runTest("knight jumps over pieces",
        "Board:\nwN wP .\nwP . .\n. . .\nCommands:\nclick 50 50\nclick 150 250\nwait 2000\nprint board\n",
        ". wP .\nwP . .\n. wN .\n");

    runTest("knight cannot move straight",
        "Board:\nwN . .\nCommands:\nclick 50 50\nclick 150 50\nwait 1000\nprint board\n",
        "wN . .\n");

    std::cout << "\n=== Pawn: חוקי רגלי ===\n";

    runTest("white pawn moves up one",
        "Board:\n. . .\n. . .\n. wP .\n. . .\nCommands:\nclick 150 250\nclick 150 150\nwait 1000\nprint board\n",
        ". . .\n. wP .\n. . .\n. . .\n");

    runTest("black pawn moves down one",
        "Board:\n. . .\n. bP .\n. . .\n. . .\nCommands:\nclick 150 150\nclick 150 250\nwait 1000\nprint board\n",
        ". . .\n. . .\n. bP .\n. . .\n");

    runTest("white pawn cannot move down",
        "Board:\n. . .\n. wP .\n. . .\nCommands:\nclick 150 150\nclick 150 250\nwait 1000\nprint board\n",
        ". . .\n. wP .\n. . .\n");

    runTest("white pawn captures diagonally",
        "Board:\n. . .\nbR . .\n. wP .\n. . .\nCommands:\nclick 150 250\nclick 50 150\nwait 1000\nprint board\n",
        ". . .\nwP . .\n. . .\n. . .\n");

    runTest("white pawn cannot capture forward",
        "Board:\n. bR .\n. wP .\n. . .\nCommands:\nclick 150 150\nclick 150 50\nwait 1000\nprint board\n",
        ". bR .\n. wP .\n. . .\n");

    runTest("white pawn cannot capture friendly diagonally",
        "Board:\nwR . .\n. wP .\n. . .\nCommands:\nclick 150 150\nclick 50 50\nwait 1000\nprint board\n",
        "wR . .\n. wP .\n. . .\n");

    runTest("white pawn double step from start row",
        "Board:\n. . .\n. . .\n. . .\n. wP .\n. . .\nCommands:\nclick 150 350\nclick 150 150\nwait 2000\nprint board\n",
        ". . .\n. wP .\n. . .\n. . .\n. . .\n");

    runTest("white pawn promotes to queen",
        "Board:\n. . .\n. wP .\n. . .\nCommands:\nclick 150 150\nclick 150 50\nwait 1000\nprint board\n",
        ". wQ .\n. . .\n. . .\n");

    runTest("black pawn promotes to queen",
        "Board:\n. bP .\n. . .\nCommands:\nclick 150 50\nclick 150 150\nwait 1000\nprint board\n",
        ". . .\n. bQ .\n");

    std::cout << "\n=== RealTimeArbiter: תנועה וזמן ===\n";

    runTest("piece not moved before arrival",
        "Board:\nwR . .\nCommands:\nclick 50 50\nclick 150 50\nwait 500\nprint board\n",
        "wR . .\n");

    runTest("piece moved after arrival",
        "Board:\nwR . .\nCommands:\nclick 50 50\nclick 150 50\nwait 1000\nprint board\n",
        ". wR .\n");

    runTest("two cell move exactly at arrival",
        "Board:\nwR . .\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        ". . wR\n");

    runTest("multiple waits accumulate",
        "Board:\nwR . .\nCommands:\nclick 50 50\nclick 150 50\nwait 500\nwait 500\nprint board\n",
        ". wR .\n");

    runTest("print before and after arrival",
        "Board:\nwR . .\nCommands:\nclick 50 50\nclick 150 50\nwait 500\nprint board\nwait 500\nprint board\n",
        "wR . .\n. wR .\n");

    runTest("moving piece cannot be selected",
        "Board:\nwR . .\nCommands:\nclick 50 50\nclick 250 50\nwait 500\nclick 50 50\nwait 2000\nprint board\n",
        ". . wR\n");

    runTest("can move again after arrival",
        "Board:\nwR . .\nCommands:\nclick 50 50\nclick 150 50\nwait 1000\nclick 150 50\nclick 250 50\nwait 1000\nprint board\n",
        ". . wR\n");

    runTest("two pieces move concurrently",
        "Board:\nwR . . wK\nCommands:\nclick 50 50\nclick 150 50\nclick 350 50\nclick 250 50\nwait 1000\nprint board\n",
        ". wR wK .\n");

    std::cout << "\n=== RealTimeArbiter: התנגשויות ===\n";

    runTest("head-on collision white started first wins",
        "Board:\nwR . . bR\nCommands:\nclick 50 50\nclick 350 50\nclick 350 50\nclick 50 50\nwait 3000\nprint board\n",
        ". . . wR\n");

    runTest("head-on collision black started first wins",
        "Board:\nwR . . bR\nCommands:\nclick 350 50\nclick 50 50\nclick 50 50\nclick 350 50\nwait 3000\nprint board\n",
        "bR . . .\n");

    runTest("friendly landing cancelled",
        "Board:\nwR wK .\nCommands:\nclick 50 50\nclick 150 50\nwait 1000\nprint board\n",
        "wR wK .\n");

    runTest("two friendly pieces same destination both cancelled",
        "Board:\nwR . wB\nCommands:\nclick 50 50\nclick 150 50\nclick 250 50\nclick 150 50\nwait 1000\nprint board\n",
        ". wR wB\n");

    runTest("two enemy pieces same destination last started wins",
        "Board:\nwR . bR\nCommands:\nclick 50 50\nclick 150 50\nclick 250 50\nclick 150 50\nwait 1000\nprint board\n",
        ". bR .\n");

    std::cout << "\n=== GameEngine: סיום משחק ===\n";

    runTest("white captures black king",
        "Board:\nwR . bK\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        ". . wR\n");

    runTest("black captures white king",
        "Board:\nbR . wK\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\n",
        ". . bR\n");

    runTest("no moves after game over",
        "Board:\nwR . bK\nbR . .\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nclick 50 150\nclick 150 150\nwait 1000\nprint board\n",
        ". . wR\nbR . .\n");

    runTest("print board works after game over",
        "Board:\nwR . bK\nCommands:\nclick 50 50\nclick 250 50\nwait 2000\nprint board\nprint board\n",
        ". . wR\n. . wR\n");

    std::cout << "\n=== Jump: קפיצה ===\n";

    runTest("jump on empty cell ignored",
        "Board:\n. . .\nwK . bR\n. . .\nCommands:\njump 150 150\nprint board\n",
        ". . .\nwK . bR\n. . .\n");

    runTest("airborne piece stays in cell",
        "Board:\n. . .\nwK . bR\n. . .\nCommands:\njump 50 150\nprint board\n",
        ". . .\nwK . bR\n. . .\n");

    runTest("airborne piece captures arriving enemy",
        "Board:\n. . .\nwK . bR\n. . .\nCommands:\njump 50 150\nclick 250 150\nclick 50 150\nwait 2000\nprint board\n",
        ". . .\nbR . .\n. . .\n");

    runTest("jump too late does not save piece",
        "Board:\n. . .\nwK . bR\n. . .\nCommands:\nclick 250 150\nclick 50 150\nwait 2000\njump 50 150\nprint board\n",
        ". . .\nbR . .\n. . .\n");

    runTest("moving piece cannot jump",
        "Board:\n. . .\nwK . bR\n. . .\nCommands:\nclick 250 150\nclick 150 150\njump 250 150\nwait 1000\nprint board\n",
        ". . .\nwK bR .\n. . .\n");

    runTest("click same cell twice is jump",
        "Board:\nwK . bR\nCommands:\nclick 50 50\nclick 50 50\nclick 250 50\nclick 50 50\nwait 500\nprint board\n",
        "wK . bR\n");

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
