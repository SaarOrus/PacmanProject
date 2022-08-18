#pragma once
#include "Creature.h"

#define ESC 27


class Pacman : public Creature {
	int lives = 3, score = 0, scoreWithBonus = 0;
	int numPointOfLives = 0;
public:
	Pacman() { figure='@',color = Color::WHITE, lives=3,score=0, scoreWithBonus = 0;}//ctor for init pacman
	enum dir { UP = 'W', DOWN = 'X', LEFT = 'A', RIGHT = 'D' ,UNDEFINED=-1};
	virtual ~Pacman(){}
	bool getDirectionPacman(char key,const Board& board); // gets curr direction
	bool checkInit(const char dir,const Board& board)const; // check unregular buttons moves
	void moveCreature(Board& board, std::ofstream& stepsFile)override; // responsible on the movment of pacman
	void checkCreatureObs(const Board& gameBoard, int dir);// checks if pacman touches obstacle
	
	int getNumPointOfLives()const
	{
		return numPointOfLives;
	}

	void setNumPointOfLives(int num)
	{
		numPointOfLives = num;
	}

	int getScoreWithBonus()const
	{
		return scoreWithBonus;
	}
	void setScoreWithBonus(int _scoreWithBonus)
	{
		scoreWithBonus = _scoreWithBonus;
	}

	int getScore()const
	{
		return score;
	}
	void setScore(int _score)
	{
		score = _score;
	}

	int getLives()const
	{
		return lives;
	}
	void setLives(int _lives)
	{
		lives = _lives;
	}

	void decreaseLives()
	{
		setLives(--lives);
	}

	void increaseScore()
	{
		setScore(++score);
	}

	void increaseBonusScore()
	{
		setScoreWithBonus(++scoreWithBonus);
	}

};
