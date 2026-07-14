#include "controllerClick.hpp"

ClickResult controllerClick::onClick(CellPos pos, const Board& board, bool isMoving, bool isJumping) {
    if (!pos.valid) {
        if (hasSelection()) clearSelection();
        return {ClickAction::None};
    }

    const Piece* piece = board.grid[pos.row][pos.col].get();

    if (!hasSelection()) {
        if (piece == nullptr || isMoving) return {ClickAction::None};
        selectedRow = pos.row;
        selectedCol = pos.col;
        return {ClickAction::Selected, pos, pos};
    }

    if (pos.row == selectedRow && pos.col == selectedCol) {
        if (isMoving || isJumping) return {ClickAction::None};
        CellPos sel = {selectedRow, selectedCol, true};
        clearSelection();
        return {ClickAction::JumpRequest, sel, sel};
    }

    const Piece* selected = board.grid[selectedRow][selectedCol].get();
    if (piece != nullptr && selected != nullptr && piece->color == selected->color) {
        selectedRow = pos.row;
        selectedCol = pos.col;
        return {ClickAction::Reselected, pos, pos};
    }

    CellPos from = {selectedRow, selectedCol, true};
    clearSelection();
    return {ClickAction::MoveRequest, from, pos};
}

bool controllerClick::hasSelection() const { return selectedRow != -1; }
void controllerClick::clearSelection() { selectedRow = -1; selectedCol = -1; }
