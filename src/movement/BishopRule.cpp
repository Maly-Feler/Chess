#include "BishopRule.hpp"
#include <cmath>

bool BishopRule::canMove(int fromRow, int fromCol, int toRow, int toCol,
                         const Board& board) const {
    if (abs(toRow - fromRow) != abs(toCol - fromCol) || toRow == fromRow) return false;
    int dr = (toRow > fromRow) ? 1 : -1;
    int dc = (toCol > fromCol) ? 1 : -1;
    int r = fromRow + dr, c = fromCol + dc;
    while (r != toRow || c != toCol) {
        if (board.getPiece(r, c) != nullptr) return false;
        r += dr; c += dc;
    }
    return true;
}
