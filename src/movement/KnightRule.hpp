#pragma once
#include "MoveRule.hpp"

class KnightRule : public MoveRule {
public:
    bool canMove(int fromRow, int fromCol, int toRow, int toCol,
                 const Board& board) const override;
};
