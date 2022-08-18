#include "Pacman.h"



bool Pacman::checkInit(const char curDir,const Board& board)const //check input
{

	if (curDir == ESC)//if user pressed escape
	{
		do {
			clear_screen();
			gotoxy(40, 13);
			std::cout << "Game paused, press ESC again to continue" << std::endl;
		} while (_getch() != ESC);
		clear_screen();
		board.printBoard();
	}

	if (curDir == 'S' || curDir == 's')//if user press the stay key
		return false;

	gotoxy(0, 0);//print board from same starting place

	return true;
}

bool Pacman::getDirectionPacman(char dir,const Board& board)
{
	if ((dir <= 'Z' && dir >= 'A') || (dir <= 'z' && dir >= 'a')) //from small letters to capital letters
		dir = toupper(dir);

	switch (dir) { //switch on char value direction using enum

	case UP: // up
		key=Creature::UP;
		
		break;
	case DOWN: //down
		key = Creature::DOWN;
		
		break;
	case LEFT: //left
		key = Creature::LEFT;
		
		break;
	case RIGHT: //right
		key = Creature::RIGHT;
		
		break;
	default:
		return false;
	}

	checkCreatureObs(board,getDirection(board));
	return true;

}

void Pacman::checkCreatureObs(const Board& board, int dir)
{
	checkObstacle(board, dir);//check if pacman run into a wall

	//check if its a secret pass	
	if ((coord.getY() == (board.getUp())) && (board.getMatGame(coord.getY(), coord.getX()) != '#'))
		coord.setY(board.getDown());
	else if (coord.getY() == (board.getDown()) && (board.getMatGame(coord.getY(), coord.getX()) != '#'))
		coord.setY(board.getUp());
	else if (coord.getX() == (board.getLeft()-1) && (board.getMatGame(coord.getY(), coord.getX()) != '#'))
		coord.setX(board.getRight());
	else if (coord.getX() == (board.getRight()+1) && (board.getMatGame(coord.getY(), coord.getX()) != '#'))
		coord.setX(board.getLeft());
}

void Pacman:: moveCreature(Board& board, std::ofstream& stepsFile) {
		
	bool check = true, stay = false;	
	
		if (!_kbhit || check)
		{

			if (_kbhit()) // if we get input
			{
				if (!stay)
				{
					prevDir = curDir;
					curDir = _getch();
				}
				else
				{
					stay = false;
					curDir = prevDir;
				}
			}

			erase(); // erase prev step

			board.setMatGame(' ', getCurY(), getCurX());// update the chars table

			check = getDirectionPacman(curDir, board);

			if (statusCreature == SAVE)
				if (check)
					updateStepsFile(stepsFile, "Pacman",key);					
			

			if (!check) //if it is a "special" move
			{
				check = checkInit(curDir, board);
				if (check)
					curDir = prevDir;
				else
				{
					stay = true;
					if (statusCreature == SAVE)
						stepsFile << "Pacman STAY ";
					check = true;
				}
			}

			hideCursor();

			draw(figure, color);
		}
	
		if(statusCreature==SAVE)
			if (curDir != UNDEFINED)
				numPointOfLives++;
}
