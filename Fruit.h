#pragma once
#include "GoodGhost.h"



class Fruit : public NoviceGhost{
	bool isFruitOnScreen = false,isFruitDisapear=false;
	int whenFruitShow=0, howLongFruitStay=0;
	int counterFruitIter = 0, addScore = 0;
	

public:
	Fruit() { figure = ' ', color = Color::WHITE, whenFruitShow += setWhenFruitShow(); }//empty ctor
	Fruit(int  _x, int _y) { coord.setX(_x), coord.setY(_y), figure = ' ', color = Color::WHITE; }//ctor 
	virtual ~Fruit(){}
	void moveFruit( Pacman& pacman, Board& board, Creature** ghostsArr, int numOfIterations,std::ofstream& stepsFile, int status);
	void initialFruit(const Board& board);
	void moveCreature(Board& board, std::ofstream& stepsFile)override;
	void initialRandomFigure(); //select the figure between 5-9
	void initialRandomCoord(const Board& board);//select random coordinate on screen
	void isCollision(Pacman& pacman,Creature** ghostsArr,const Board& board, int numOfIterations, std::ofstream& stepsFile,int status); //fruit meets pacman
	void resetFruit();

	bool getIsFruitDisapear()
	{
		return isFruitDisapear;
	}

	void setIsFruitOnScreen(bool _val)
	{
		isFruitOnScreen = _val;
	}
		
	bool getIsFruitOnScreen()
	{
		return isFruitOnScreen;
	}

	int setWhenFruitShow() // how often fruit will show
	{
		int ret;
		ret =  rand() % 10 + 15;
		return ret * 2; //numOfIteration is even
	}

	int setHowLongFruitStay() // how much time fruit is going to stay
	{
		int ret;
		ret= rand() % 5 + 10;
		return ret;
	}
};