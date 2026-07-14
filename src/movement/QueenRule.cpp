#include "QueenRule.hpp"
#include "RookRule.hpp"
#include "BishopRule.hpp"

bool QueenRule::canMove(int fromRow, int fromCol, int toRow, int toCol,
                        const Board& board) const {
    return RookRule().canMove(fromRow, fromCol, toRow, toCol, board) ||
           BishopRule().canMove(fromRow, fromCol, toRow, toCol, board);
}
