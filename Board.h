#pragma once
#include "Functions.h"


#include<sys/stat.h>
#include<typeinfo>
#include <fstream>
#include <set>
#include <filesystem>
#include <iomanip>
#include <typeinfo>

#define MAX_ROW 25
#define MAX_COL 80
#define WALL '#'
#define FOOD '.'
#define LEGEND '&'
#define GHOST '$'
#define PACMAN '@'


namespace fs = std::filesystem;
using namespace fs;
using fs::current_path;

using std::set;
using std::ifstream;
using std::ios;
using std::filesystem::exists;


class Board {

	int up=0, down=0, left=0, right=0;
	Color colorWall=Color::WHITE, colorBreadCrumbs = Color::WHITE;
	int countBreadCrumbs = 0,countBoards=0;
	Point LegendPos,pacmanPos,ghostsPos[4];	
	vector <string> filesArr;												
	int countGhosts = 0;
	char matGame[MAX_ROW][MAX_COL];

public:

	bool checkAndInit(char curBoard, int i, int j, int& countLegend, int& countPacman); //return false in case the boars invalid
	void initFiles();//getting files from directory in lexicographical order
	bool buildBoardFromFile(string fileName);
	void printBoard()const;
	void spaceForLegend();
	void initBoard();

	int getCountBoards()const
	{
		return countBoards;
	}

	void setCountBoards(int num)
	{
		countBoards=num;
	}

	int getBreadCrunbs()const
	{
		return countBreadCrumbs;
	}
	void setBreadCrunbs(int breadCrumbs)
	{
		countBreadCrumbs = breadCrumbs;
	}

	int getCountGhosts()const
	{
		return countGhosts;
	}

	Point* getGhostsPos()
	{
		return ghostsPos;
	}

	Point getPacmanPos()const
	{
		return pacmanPos;
	}

	Point getLegendPos()const
	{
		return LegendPos;
	}

	int getUp()const
	{
		return up;
	}
		
	int getDown()const
	{
		return down;
	}

	int getLeft()const
	{
		return left;
	}
	
	int getRight()const
	{
		return right;
	}

	vector<string> getFiles()const
	{
		return filesArr;
	}

	Color getColorFood() const //return current color
	{
		return colorBreadCrumbs;
	}

	Color getColorWall() const //return current color
	{
		return colorWall;
	}

	void setColorWall(Color c) // set color
	{
		colorWall = c;
	}

	void setColorFood(Color c) // set color
	{
		colorBreadCrumbs = c;
	}

	void setMatGame(char ch, int row, int col)
	{
		matGame[row][col] = ch;
	}
	char getMatGame(int row, int col)const
	{
		return matGame[row][col];
	}
};


