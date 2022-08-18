#pragma once

#include "SmartGhost.h"
#define LOWER_RANGE 10
#define ADD_TO_RANGE 15
#define STUPID_MOVES 5

class GoodGhost: public SmartGhost {

	int countSmartMoves = 0,countStupidMoves=0,smartMoves=0;
	
	bool is5Moves = false,isStupid=false;


public:
	GoodGhost() { figure = '$', color = Color::WHITE; }//empty ctor
	GoodGhost(int  _x, int _y) { coord.setX(_x), coord.setY(_y), figure = '$', color = Color::WHITE; }//ctor 
	virtual ~GoodGhost() {}
	void initAferDeathGhost() override;
	void moveCreature(Board& board, std::ofstream& stepsFile) override;
	void getStupid();
	bool getIs5Moves()const
	{
		return is5Moves;
	}

	bool getIsStupid()const
	{
		return isStupid;
	}

	void setIsStupid(bool val)
	{
		isStupid = val;
	}
	
};