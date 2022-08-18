#pragma once
#include "Pacman.h"



class NoviceGhost : public Creature {	

	
public:
	
	NoviceGhost() { figure='$', color = Color::WHITE; }//empty ctor
	NoviceGhost(int  _x, int _y) { coord.setX(_x), coord.setY(_y), figure = '$', color = Color::WHITE; }//ctor
	virtual ~NoviceGhost(){}
	void moveCreature(Board& board, std::ofstream& stepsFile)override;
	void checkCreatureObs(const Board& gameBoard, int dir)override;
	void printBeforeGhost(const Board& board)const;
	void moveGhost(const Board& board);
	
	
};