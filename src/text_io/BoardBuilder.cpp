#include "BoardBuilder.hpp"
#include "../model/PieceFactory.hpp"
#include <sstream>

bool BoardBuilder::build(const std::string& input, Board& board, std::string& error) const {
    std::istringstream ss(input);
    std::string line;
    int rowWidth = -1;

    while (std::getline(ss, line)) {
        std::istringstream rowSS(line);
        std::string token;
        std::vector<std::unique_ptr<Piece>> row;

        while (rowSS >> token) {
            auto p = PieceFactory::make(token);
            if (token != "." && p == nullptr) {
                error = "ERROR UNKNOWN_TOKEN";
                return false;
            }
            row.push_back(std::move(p));
        }

        if (row.empty()) continue;

        if (rowWidth == -1) rowWidth = (int)row.size();
        else if ((int)row.size() != rowWidth) {
            error = "ERROR ROW_WIDTH_MISMATCH";
            return false;
        }
        board.addRow(std::move(row));
    }

    return true;
}
