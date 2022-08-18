#pragma once
#include "Board.h"
#define SIMPLE 10
#define SAVE 6
#define LOAD 7
#define SILENT 8

class Creature { //abstract class for implement game creatures

protected:
	Point coord;
	char figure,curDir=UNDEFINED,prevDir=UNDEFINED;
	Color color=Color::WHITE;
	int key =UNDEFINED, countMoves = 0;
	int statusCreature =UNDEFINED;

public:
	virtual ~Creature(){}
	enum dir { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3,UNDEFINED=-1 };
	int getDirection(const Board& gameBoard);
	virtual void initAferDeathGhost() {};
	virtual void checkBestDirection(Board& board, int pacmanCurY, int pacmanCurX) {};
	bool checkObstacle(const Board& gameBoard,int dir);
	virtual void moveCreature(Board& board, std::ofstream& stepsFile) = 0;
	virtual void checkCreatureObs(const Board& gameBoard, int dir) {};
	void updateStepsFile(std::ofstream& stepsFile, string objectName, int _key);
	string keyToName(int _key);

	void setStatusCreature(int val)
	{
		statusCreature = val;
	}

	void setCounter(int _count)
	{
		countMoves = _count;
	}

	
	int getCounter() const {
		return countMoves;
	}
	void increasCounter() {
		countMoves++;
	}

	Color getColor()const
	{
		return color;
	}
	void setColor(Color c)
	{
		color = c;

	}
	int getCurX() const
	{
		return coord.getX();
	}
	int getCurY()const
	{
		return coord.getY();
	}

	void setCurY(int _y) {
		coord.setY(_y);
	}

	void setCurX(int _x) {
		coord.setX(_x);
	}

	char getFigure()const {
		return figure;
	}

	void setFigure(char _figure)
	{
		figure = _figure;
	}

	void draw(const char ch, Color color)const
	{
		gotoxy(coord.getX(), coord.getY());
		setTextColor(color);
		std::cout << ch;
	}

	void erase() const
	{
		gotoxy(coord.getX(), coord.getY());
		std::cout << ' ';
	}
	void setKey(int _key) {
		key = _key;
	}

	int getKey() const {
		return key;
	}

	void setCurDir(int dir)
	{
		curDir = dir;
	}

	int getCurDir()const
	{
		return curDir;
	}

	void setPrevDir(int dir)
	{
		prevDir = dir;
	}
};