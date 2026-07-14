#include "BoardMapper.hpp"
#include "../Constants.hpp"

CellPos BoardMapper::toCell(int x, int y, int rows, int cols) const {
    int col = x / CELL_SIZE_PX;
    int row = y / CELL_SIZE_PX;
    bool valid = row >= 0 && row < rows && col >= 0 && col < cols;
    return {row, col, valid};
}
