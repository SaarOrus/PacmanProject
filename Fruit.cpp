#include "Fruit.h"

void Fruit::initialFruit(const Board& board)
{
	initialRandomFigure();
	initialRandomCoord(board);
	howLongFruitStay = setHowLongFruitStay();
}

void Fruit::initialRandomFigure() //select the figure between 5-9
{
	int randomFigure;

	srand((unsigned int)time(nullptr));
	randomFigure = rand() % 4 + 5; //every number symbolize a figure

	addScore = randomFigure;

	figure=(randomFigure+'0');

}
void Fruit::initialRandomCoord(const Board& board)//select random coordinate on screen
{
	int randomX, randomY;

	do { //the start point of fruit cant be on obstcale
		randomX = rand() % (board.getRight() - 3) + 2;
		randomY = rand() % (board.getDown() - 3) + 2;

	} while (board.getMatGame(randomX, randomY) == '#');

	coord.setX(randomX);
	coord.setY(randomY);
}

void Fruit::moveFruit(Pacman& pacman,Board& board,Creature** ghostsArr, int numOfIterations,std::ofstream & stepsFile,int status) {

	if (numOfIterations == whenFruitShow)
	{
		initialFruit(board);

		if (status == SAVE)
		{
			stepsFile << "FruitApear " << figure << " "<<coord.getX()<<" " <<coord.getY()<<" "; //print the current figure of fruit
		}
		isFruitOnScreen = true;
	}

	if (isFruitOnScreen) {

		if (counterFruitIter < howLongFruitStay) // fruit shows if there is no fruit on screen and in this specific score
		{
			key = rand() % 4; //every number symbolize a direction
					
			moveCreature(board,stepsFile);
			isCollision(pacman, ghostsArr,board,numOfIterations,stepsFile,status);
			counterFruitIter++;
		}
		else 
		{
			//erase
			printBeforeGhost(board);
			resetFruit();
			if (status == SAVE)
			{
				stepsFile << "FruitDisapear " << numOfIterations << " ";
			}
						
		}

	}
}


void Fruit::moveCreature(Board &board, std::ofstream& stepsFile)
{
	printBeforeGhost(board);

	while (checkObstacle(board, getDirection(board)))//choose -not wall- direction key 
	{
		curDir = rand() % 4;
		key = curDir;
		
	}

	moveGhost(board);

	if (statusCreature == SAVE)
		updateStepsFile(stepsFile, "Fruit", key);		
	
}

void Fruit::resetFruit()
{
	isFruitOnScreen = false;
	counterFruitIter = 0;
	whenFruitShow += setWhenFruitShow();
}


void Fruit::isCollision(Pacman& pacman,Creature** ghostsArr,const Board& board, int numOfIterations, std::ofstream& stepsFile,int status)
{
	if (((pacman.getCurX() == getCurX()) && (pacman.getCurY() == getCurY()))) //if pacman eat fruit he gets the food of fruit.
	{
		pacman.setScoreWithBonus(pacman.getScoreWithBonus() + addScore);
		resetFruit();
		if (status == SAVE)
		{
			stepsFile << "FruitDisapear " << numOfIterations << " ";
		}
	}

	for (int i = 0; i < board.getCountGhosts(); i++)
	{
		if (((ghostsArr[i]->getCurX() == getCurX()) && (ghostsArr[i]->getCurY() == getCurY()))) //if pacman eat fruit he gets the food of fruit.
		{
			resetFruit();
			if (status == SAVE)
			{
				stepsFile << "FruitDisapear " << numOfIterations << " ";
			}
			break;
		}
	}
}
