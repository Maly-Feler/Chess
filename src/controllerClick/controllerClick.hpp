#pragma once
#include "CellPos.hpp"
#include "ClickResult.hpp"
#include "../model/Board.hpp"

class controllerClick {
public:
    ClickResult onClick(CellPos pos, const Board& board, bool isMoving, bool isJumping);
    bool hasSelection() const;
    void clearSelection();

private:
    int selectedRow = -1;
    int selectedCol = -1;
};
