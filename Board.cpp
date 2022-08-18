#include "Board.h"
#define UNDEFINED -1

void Board::printBoard()const
{
	clear_screen();
	
	for (int i = 0; i < down; i++)
	{
		for (int j = 0; j < right; j++)
		{
			if (matGame[i][j] == WALL)
				setTextColor(colorWall);
			else if(matGame[i][j] == FOOD)
				setTextColor(colorBreadCrumbs);
			cout << matGame[i][j];
		}
		cout << endl;
	}
}

void Board::initBoard()
{
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			matGame[i][j] = ' ';
}

void Board::initFiles()
{
	string path = fs::current_path().string(); //getting the path of the open working directory 
	
	int found = UNDEFINED;
	set <fs::path> sortedFiles;//file in set are sorted by lexicografical order

	for (auto& entry : fs::directory_iterator(path))
	{
		found = entry.path().string().find(".screen");
		if (found != UNDEFINED)
		{
			sortedFiles.insert(entry.path());
			found = UNDEFINED;//find the next file ended with .screen from directory
		}
	}

	for (auto& fileName : sortedFiles)
		filesArr.push_back(fileName.string());//enter sorted files to vector
}


bool Board::buildBoardFromFile(string fileName)
{
	string line;
	ifstream myFile;
	bool firstRow = true;
	int countRow = 0;
	int countLegend = 0, countPacman = 0;

	countBreadCrumbs = 0;
	countGhosts = 0;	

	initBoard();

	myFile.open(fileName);
	if (myFile.is_open())
	{
		while (std::getline(myFile, line))//get line from file
		{
			if (firstRow)
			{
				if (line.length() == 0)
				{
					clear_screen();
					cout << "Invalid. First line is empty." << endl << "Press any key to continue" << endl;
					_getch();
					return false;
				}

				right =line.length()-1;//get boundries
				firstRow = false;
			}

			if (line.length() > MAX_COL)//if one of lines is bigger than max size
			{
				clear_screen();
				cout << "Invalid. Line is bigger than max size" << endl << "Press any key to continue" << endl;
				_getch();
				return false;
			}

			for (int i = 0; i < line.length(); i++)
			{
				if (!checkAndInit(line[i], countRow, i, countLegend, countPacman))//get input for board mat from file
				{
					return false;//some invalid board
				}

			}		
			countRow++;
		}
	}
	else
	{
		cout << "can't open file" << endl;
		return false;
	}
	
	down= countRow;//boundries
	myFile.close();

	if (LegendPos.getY() == down)//if legend is down with not enugh space
		down += 2;


	if (down > MAX_ROW)
	{
		clear_screen();
		cout << "Invalid. Number of lines is bigger than max size" << endl << "Press any key to continue" << endl;
		_getch();
		return false;
	}

	spaceForLegend();//runover default place for legend

	return true;
}

void Board::spaceForLegend()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 20; j++)
		{
			if (matGame[LegendPos.getY() + i][LegendPos.getX() + j] == FOOD)
				countBreadCrumbs--;
			matGame[LegendPos.getY() + i][LegendPos.getX() + j] = ' ';
		}
}

bool Board::checkAndInit(char curChar, int row, int col,int& countLegend, int& countPacman)
{
	
	switch (curChar)
	{
	case LEGEND: 
		LegendPos.setX(col);//update start point
		LegendPos.setY(row);
		countLegend++;

		if (LegendPos.getY() == 0)//get boundries if legend at the end of first line
		{
			if ((LegendPos.getX() + 19) > right)
				right = LegendPos.getX() + 19;
		}
		
		if ((LegendPos.getX() + 19) > MAX_COL)
		{
			clear_screen();
			cout << "Invalid Board. Line is bigger than max size" << endl << "Press any key to continue" << endl;
			_getch();
			return false;
		}

		if (countLegend > 1)
		{
			clear_screen();
			cout << "Invalid Board. More than 1 legend." << endl << "Press any key to continue" << endl;
			_getch();
			return false; 
		}
		return true;

	case GHOST: 

		countGhosts++;

		if (countGhosts <= 4)//start Point
		{
			ghostsPos[countGhosts - 1].setX(col);
			ghostsPos[countGhosts - 1].setY(row);
		}
		else
		{
			clear_screen();
			cout << "Invalid board. More than 4 ghosts." << endl << "Press any key to continue" << endl;
			_getch();
			return false;
		}
		
		matGame[row][col] = FOOD;

		return true;

	case PACMAN: 
		pacmanPos.setX(col);//Pacman start point
		pacmanPos.setY(row);
		matGame[row][col] =' ';
		countPacman++;

		if (countPacman > 1)
		{

			clear_screen();
			cout << "Invalid Board. More than 1 pacman." << endl << "Press any key to continue" << endl;
			_getch();
			return false;

		}
		return true;

	case ' ': //food
		matGame[row][col] = FOOD;	
		countBreadCrumbs++;

		return true;

	case WALL:
		matGame[row][col] = WALL;
		return true;

	case '%':
		matGame[row][col] = ' ';
		return true;
	}
}