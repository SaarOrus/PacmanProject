#pragma once

#include "NoviceGhost.h"
#include <queue>
#define ROW 25
#define COL 80

class QItem {
public:
    int row;
    int col;
    int dist;
    QItem() :QItem(-1, -1, -1) {}
    QItem(int x, int y, int w)
        : row(x), col(y), dist(w)
    {
    }
    int minDistance(Board& board, int curGhostY, int curGhostX, int curPacmanY, int curPacmanX);
};

