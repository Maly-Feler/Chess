#include "Board.hpp"

Piece* Board::getPiece(int row, int col) const {
    return grid[row][col].get();
}

void Board::addRow(std::vector<std::unique_ptr<Piece>> row) {
    cols = (int)row.size();
    grid.push_back(std::move(row));
    rows = (int)grid.size();
}

void Board::removePiece(int row, int col) {
    grid[row][col].reset();
}

char Board::movePiece(int fromRow, int fromCol, int toRow, int toCol, Color movingColor) {
    char capturedType = 0;
    if (grid[toRow][toCol])
        capturedType = grid[toRow][toCol]->type;
    grid[toRow][toCol] = std::move(grid[fromRow][fromCol]);
    int lastRow = (movingColor == Color::White) ? 0 : rows - 1;
    if (toRow == lastRow)
        promotePiece(toRow, toCol);
    return capturedType;
}

void Board::promotePiece(int row, int col) {
    Piece* promoted = grid[row][col]->onReachLastRow();
    if (promoted) {
        grid[row][col].reset(promoted);
    }
}
