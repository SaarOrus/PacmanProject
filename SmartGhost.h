#pragma once

#include "QItem.h"


class SmartGhost : public NoviceGhost{

	QItem item;

public:
	SmartGhost() { figure = '$', color = Color::WHITE; }//empty ctor
	SmartGhost(int  _x, int _y) { coord.setX(_x), coord.setY(_y), figure = '$', color = Color::WHITE; }//ctor 
	virtual ~SmartGhost(){}
	void moveCreature(Board& board, std::ofstream& stepsFile) override;
	void checkBestDirection(Board& board, int pacmanCurY, int pacmanCurX)override;
};

