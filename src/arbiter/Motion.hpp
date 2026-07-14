#pragma once

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
