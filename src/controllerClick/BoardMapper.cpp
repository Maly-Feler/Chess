#include "BoardMapper.hpp"

CellPos BoardMapper::toCell(int x, int y, int rows, int cols, int boardWidth, int boardHeight) const {
    x -= SIDE_PANEL;
    y -= TOP_PANEL;

    int cellWidth = boardWidth / cols;
    int cellHeight = boardHeight / rows;

    int col = x / cellWidth;
    int row = y / cellHeight;

    bool valid = row >= 0 && row < rows && col >= 0 && col < cols;

    return {row, col, valid};
}