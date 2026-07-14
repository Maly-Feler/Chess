#include "KingRule.hpp"
#include <cmath>

bool KingRule::canMove(int fromRow, int fromCol, int toRow, int toCol,
                       const Board& board) const {
    int dr = abs(toRow - fromRow);
    int dc = abs(toCol - fromCol);
    return dr <= 1 && dc <= 1 && (dr + dc > 0);
}
