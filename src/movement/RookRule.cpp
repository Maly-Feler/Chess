#include "RookRule.hpp"

bool RookRule::canMove(int fromRow, int fromCol, int toRow, int toCol,
                       const Board& board) const {
    if (fromRow != toRow && fromCol != toCol) return false;
    int dr = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int dc = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;
    int r = fromRow + dr, c = fromCol + dc;
    while (r != toRow || c != toCol) {
        if (board.getPiece(r, c) != nullptr) return false;
        r += dr; c += dc;
    }
    return true;
}
