#include "Piece.hpp"

int Piece::nextId = 0;

Piece::Piece(Color c, char t) : color(c), type(t), id(nextId++) {}

std::string Piece::toString() const {
    std::string s;
    s += (color == Color::White ? 'w' : 'b');
    s += type;
    return s;
}
