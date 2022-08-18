#pragma once
#include "Menu.h"
#define PH_SIZE 4
#define OPTION1 1
#define OPTION2 2
#define OPTION3 3
#define OPTION8 8
#define OPTION9 9



using std::ofstream;

class Game {
	
	bool isGameRun = true, isWon = false, isColored = false, isSilentComplete = true, silent = false;
	char figure = 3;
	int lives=3,numOfIterations=0;
	int status = Creature::UNDEFINED;
	Board boardRunGame;
	Pacman pacman;
	Fruit fruit;
	Creature* ghostsArr[PH_SIZE]= { nullptr };
	Menu menu;

public: 
	Game() {};// empty ctor
	//ctor
	Game(Pacman& _pacman, Fruit& _fruit) : pacman(_pacman), fruit(_fruit) {};
	~Game() { deleteArray(); }
	const Game& operator=(const Game& g) = delete;
	Game (const Game& g) = delete;
	bool isPacmanMeetGhost()const;
	void initGhostsArr(Point arrGhosts[4],int size);
	void runGame(string path); // the functions that runs all the game
	void gameManager(int stat, bool sil = false);
	void initGame(); //initliaze the features game
	void statusLive(ofstream& resultFile,vector <int>& resultPointOfTime, int& resultVectorIndex); // updtade current number of lives
	void statusScore(ofstream& resultFile); // updtade current number of scores
	void afterDeathInitialization();//when user lose
	void updateColor();//update colors
	void deleteArray();
	bool findFileInArr(string fileName, int& indexFindFile);
	void prepareAndRunGame();
	ofstream openFiles(string fileName, string end);
	string getFileNameFromPath(string path, string end);
	bool moveObjectByFile(ifstream& stepsFile,char currObject, vector <int> resultVector, int indexOfVector);
	int keyToNumber(string key);
	vector <int> readResultFile(ifstream& resultFile);
	

	void setIsGameRun(bool value)
	{
		isGameRun = value;
	}
	int getIsGameRun()const
	{
		return isGameRun;
	}

};
