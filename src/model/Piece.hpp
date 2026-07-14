#pragma once
#include <string>

enum class Color { White, Black };

class Piece {
public:
    Color color;
    char type;
    int id;

    Piece(Color c, char t);
    virtual ~Piece() = default;

    virtual Piece* onReachLastRow() const { return nullptr; }
    std::string toString() const;

private:
    static int nextId;
};
