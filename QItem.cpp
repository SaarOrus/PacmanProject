#include "QItem.h"

int QItem::minDistance(Board& board, int curGhostY, int curGhostX, int curPacmanY, int curPacmanX)//i is the current ghost
{
    QItem source(0, 0, 0);

    //starting position of ghost
    source.row = curGhostY;
    source.col = curGhostX;


   //mark the valid places (not wall) for ghost steps
    bool visited[ROW][COL];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++)
        {
            if (board.getMatGame(i, j) == '#')
                visited[i][j] = true;
            else
                visited[i][j] = false;

        }
    }

    
    std::queue<QItem> q;

    q.push(source);
    visited[source.row][source.col] = true;

    while (!q.empty()) {

        QItem item = q.front();
        q.pop();

        // pacman found;
        if (item.row == curPacmanY && item.col == curPacmanX)
            return item.dist;

        // moving up
        if (item.row - 1 >= 0 && visited[item.row - 1][item.col] == false) {
            q.push(QItem(item.row - 1, item.col, item.dist + 1));
            visited[item.row - 1][item.col] = true;
        }

        // moving down
        if (item.row + 1 < board.getDown() && visited[item.row + 1][item.col] == false) {
            q.push(QItem(item.row + 1, item.col, item.dist + 1));
            visited[item.row + 1][item.col] = true;
        }

        // moving left
        if (item.col - 1 >= 0 && visited[item.row][item.col - 1] == false) {
            q.push(QItem(item.row, item.col - 1, item.dist + 1));
            visited[item.row][item.col - 1] = true;
        }

        // moving right
        if (item.col + 1 < board.getRight() && visited[item.row][item.col + 1] == false) {
            q.push(QItem(item.row, item.col + 1, item.dist + 1));
            visited[item.row][item.col + 1] = true;
        }
    }

    return -1;

}