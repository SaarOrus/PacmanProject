#include "NoviceGhost.h"


void NoviceGhost::moveCreature(Board& board, std::ofstream& stepsFile)
{	
	printBeforeGhost(board); // print the value in point before ghost been there
	
	if (countMoves % 20 == 0)//direction selected randomly every 20 moves
	{
		if (countMoves > 0)
			prevDir = curDir;

		curDir = rand() % 4; //every number symbolize a direction

		key = curDir;
		
	}

	while (checkObstacle(board, getDirection(board)))
	{
		curDir = rand() % 4;
		key = curDir;
		
	}

	moveGhost(board);//move relevant just for ghosts

	if (statusCreature == SAVE)
		updateStepsFile(stepsFile, "Ghost", key);
}



void NoviceGhost::moveGhost(const Board& board) {
			
	checkCreatureObs(board,key);
	gotoxy(coord.getX(), coord.getY());
	setTextColor(getColor());
	std::cout << figure;

	increasCounter();
}

void NoviceGhost::checkCreatureObs(const Board& board,int dir) {
		 
	if ((coord.getY() == board.getUp()) && (board.getMatGame(coord.getY(), coord.getX()) != '#'))//prevent from ghost go into upper tunnel
		coord.increaseY();
	else if ((coord.getY() == board.getDown()) && (board.getMatGame(coord.getY(), coord.getX()) != '#'))//prevent from ghost go into lower tunnel
		coord.decreaseY();
	else if ((coord.getX() == board.getLeft()) && (board.getMatGame(coord.getY(), coord.getX()) != '#'))//prevent from ghost go into left tunnel
		coord.increaseX();
	else if ((coord.getX() == board.getRight()) && (board.getMatGame(coord.getY(), coord.getX()) != '#'))//prevent from ghost go into right tunnel
		coord.decreaseX();
	
}

// print the prev char on screen before ghost been there
void NoviceGhost::printBeforeGhost(const Board& board)const
{
	if (board.getMatGame(coord.getY(), coord.getX()) == ' ')
		draw(' ', Color::WHITE);
	else if (board.getMatGame(coord.getY(), coord.getX()) == '.')
		draw('.', board.getColorFood());
}