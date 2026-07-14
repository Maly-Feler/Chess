#include "KnightRule.hpp"
#include <cmath>

bool KnightRule::canMove(int fromRow, int fromCol, int toRow, int toCol,
                         const Board& board) const {
    int dr = abs(toRow - fromRow);
    int dc = abs(toCol - fromCol);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}
