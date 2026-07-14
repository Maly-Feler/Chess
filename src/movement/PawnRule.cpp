#include "PawnRule.hpp"
#include <cmath>

bool PawnRule::canMove(int fromRow, int fromCol, int toRow, int toCol,
                       const Board& board) const {
    const Piece* piece = board.getPiece(fromRow, fromCol);
    int dir = (piece->color == Color::White) ? -1 : 1;
    int dr = toRow - fromRow;
    int dc = toCol - fromCol;

    if (dc == 0 && dr == dir && board.getPiece(toRow, toCol) == nullptr)
        return true;

    int startRow = (piece->color == Color::White) ? board.rows - 2 : 1;
    if (dc == 0 && dr == 2 * dir && fromRow == startRow
        && board.getPiece(fromRow + dir, fromCol) == nullptr
        && board.getPiece(toRow, toCol) == nullptr)
        return true;

    if (abs(dc) == 1 && dr == dir
        && board.getPiece(toRow, toCol) != nullptr
        && board.getPiece(toRow, toCol)->color != piece->color)
        return true;

    return false;
}
