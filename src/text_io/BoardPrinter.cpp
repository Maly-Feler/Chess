#include "BoardPrinter.hpp"
#include <iostream>

void BoardPrinter::print(const Board& board) const {
    for (int i = 0; i < board.rows; i++) {
        for (int j = 0; j < board.cols; j++) {
            if (j > 0) std::cout << " ";
            std::cout << (board.getPiece(i, j) ? board.getPiece(i, j)->toString() : ".");
        }
        std::cout << "\n";
    }
}
