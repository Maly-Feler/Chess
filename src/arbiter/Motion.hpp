#pragma once

enum class PieceStatus { Idle, ShortReset, LongReset, Move, Jump };

struct Motion {
    int fromRow, fromCol;
    int toRow, toCol;
    int startTime;
    int arrivalTime;
    int order;
};

struct Jump {
    int row, col;
    int startTime;
    int endTime;
    int order;
};
