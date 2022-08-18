#include "SmartGhost.h"

void SmartGhost::moveCreature(Board& board, std::ofstream& stepsFile)
{
	printBeforeGhost(board);
	
	checkObstacle(board, getDirection(board));

	moveGhost(board);

	if (statusCreature == SAVE)
		updateStepsFile(stepsFile, "Ghost", key);
}

//check the minimal distance from every valid (not wall) direction
void SmartGhost::checkBestDirection(Board& board,int pacmanCurY,int pacmanCurX)
{
	int dir,dist,min=5555;
	int prevGhostX, prevGhostY;

	prevGhostX = coord.getX();
	prevGhostY = coord.getY();


	for (int i = 0; i < 4; i++)
	{
		key = i;
		coord.setX(prevGhostX);
		coord.setY(prevGhostY);

		if (!checkObstacle(board, getDirection(board)))
		{
			dist = item.minDistance(board, coord.getY(), coord.getX(), pacmanCurY, pacmanCurX);

			if (dist < min)
			{
				min = dist;
				dir = i;
			}
		}
	}

	coord.setX(prevGhostX);
	coord.setY(prevGhostY);
	key = dir;
	
}