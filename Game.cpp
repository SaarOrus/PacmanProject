#include "Game.h"


void Game::deleteArray()
{
	for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
	{
		delete ghostsArr[i];
	}
		
}

//change the allocation of ghost array by user choice
void Game::initGhostsArr(Point arrGhosts[4], int size)
{
	if (status == LOAD)
	{
		menu.setchoiceLevel(1);//just for making allocation
	}

	for (int i = 0; i < size; i++)
	{
		switch (menu.getChoiceLevel())
		{
		case 1:
			ghostsArr[i] = new NoviceGhost();
			break;
		case 2:
			ghostsArr[i] = new GoodGhost();
			break;
		case 3:
			ghostsArr[i] = new SmartGhost;
			break;
		}
		ghostsArr[i]->setCurX(arrGhosts[i].getX());
		ghostsArr[i]->setCurY(arrGhosts[i].getY());
	}
}

void Game::prepareAndRunGame()
{
	string fileName;

	if (boardRunGame.getFiles().empty())//there are no files in directory
	{
		cout << "There are no game boards to charge in file, please enter game board file to start playing!" << endl
			<< "Press any key to go back to menu" << endl;
		_getch();
	}
	else
	{
		unsigned int i = 0;
		pacman.setLives(3);
		//pass from one board to another if winning, if we didnt loose and are screens ain't over
		while (((i < boardRunGame.getFiles().size()) && (isGameRun || isWon)))
		{
			if (!boardRunGame.buildBoardFromFile(boardRunGame.getFiles()[i]))//enter data from file to vector board
			{
				isGameRun = false;
				continue;//if board invalid - continue to next board
			}
			if(i>0)
				boardRunGame.setBreadCrunbs(boardRunGame.getBreadCrunbs() + boardRunGame.getCountGhosts());

			boardRunGame.setCountBoards(i+1);


			runGame(boardRunGame.getFiles()[i]);

			i++;
		}
		if(silent)
			menu.printSilentMessage(isSilentComplete);
	}
}



void Game::gameManager(int stat, bool sil)
{
	int indexFindFile = Creature::UNDEFINED;
	status = stat;
	silent = sil;
	boardRunGame.initFiles();//get game boards files from directory		

	while (isGameRun)
	{
		if(stat!=LOAD)
			menu.printAndGetMenu();
		else		
			menu.setchoiceMenu(OPTION1);
		
		boardRunGame.setCountBoards(0);

		switch (menu.getChoiceMenu())
		{
		case OPTION1:
			isColored = false;
			if(status!=LOAD)
				menu.printAndGetLevelGhost();            
			prepareAndRunGame();
			if(status != LOAD)
				setIsGameRun(true);

			
			break;
		case OPTION2:
			isColored = true;
			menu.printAndGetLevelGhost();
			prepareAndRunGame();			
			if (status != LOAD)
				setIsGameRun(true);
		
			break;
		case OPTION3:			
				menu.enterYourBoard();
				menu.printAndGetLevelGhost();			

			if (findFileInArr(menu.getUserFile(),indexFindFile))
			{
				if (boardRunGame.buildBoardFromFile(boardRunGame.getFiles()[indexFindFile]))//enter data from file to vector board
				{
					boardRunGame.setCountBoards(1);
					runGame(boardRunGame.getFiles()[indexFindFile]);
				}
			}

			if (status != LOAD)
				setIsGameRun(true);
			
			break;
		case OPTION8:
			menu.printInstructions();
			break;
		case OPTION9:
			setIsGameRun(false);

		}
	}
}

bool Game::findFileInArr(string fileName,int & indexFindFile)
{
	size_t find;

	for (int i = 0; i < boardRunGame.getFiles().size(); i++)
	{
		find = boardRunGame.getFiles()[i].find(fileName); //find only the name string in path string
		if (find !=string::npos) 
		{
			indexFindFile = i;
			return true;
		}
	}
	isGameRun = false;
	do {
		cout << "Board was not found" << endl;
	} while (!_getch());
	return false;
}

void Game::initGame()
{
	isWon = false;
	isGameRun = true;

	pacman.setCurX(boardRunGame.getPacmanPos().getX());
	pacman.setCurY(boardRunGame.getPacmanPos().getY());
	pacman.setCurDir(Creature::UNDEFINED);
	pacman.setPrevDir(Creature::UNDEFINED);
	pacman.setNumPointOfLives(0);

	initGhostsArr(boardRunGame.getGhostsPos(), boardRunGame.getCountGhosts());//allocate the right level of ghosts

	numOfIterations = 0;
	pacman.setScore(0);
	pacman.setScoreWithBonus(0);
	pacman.draw(pacman.getFigure(), pacman.getColor());
}

bool Game::isPacmanMeetGhost()const
{
	for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
	{
		if ((pacman.getCurX() == ghostsArr[i]->getCurX()) && (pacman.getCurY() == ghostsArr[i]->getCurY()))
			return true;
	}

	return false;
}

void Game::statusLive(ofstream& resultFile,vector <int>& resultPointOfTime,int& resultVectorIndex)
{	
	if (status != LOAD)
	{
		// if pacman and one of the ghosts are on the same place
		if (isPacmanMeetGhost())
		{
			afterDeathInitialization();

			if (status == SAVE)
			{
				resultFile << pacman.getNumPointOfLives()-1 << endl;// insert death time of pacman
			}

			pacman.decreaseLives();
		}
	}
	else
	{
		
			if (resultPointOfTime.size() > 1)
			{
				if (isPacmanMeetGhost())
				{
					if (pacman.getNumPointOfLives() != resultPointOfTime[resultVectorIndex])//was munofiterations
						isSilentComplete = false;

					afterDeathInitialization();
					pacman.decreaseLives();
					resultVectorIndex++;
				}
			}

			if (pacman.getCurDir() != Creature::UNDEFINED)
				pacman.setNumPointOfLives(pacman.getNumPointOfLives() + 1);
		
	}
	
	if (pacman.getLives() == 0) // game over
	{
		if (status == SAVE)
		{
			resultFile << pacman.getNumPointOfLives() << endl;// insert end-lose time of current screen
		}

		if (!silent) //if silent-dont draw
		{
			clear_screen();
			gotoxy(40, 12);
			std::cout << "YOU LOSE ... G A M E   O V E R !!! :-(";
		}
		if(status!=LOAD)
			_getch();

		setIsGameRun(false); //end lives, back to menu
	}	

	if (getIsGameRun() && !silent)
	{
		gotoxy(boardRunGame.getLegendPos().getX(), boardRunGame.getLegendPos().getY() + 1);
		hideCursor();
		std::cout << "                    ";

		gotoxy(boardRunGame.getLegendPos().getX(), boardRunGame.getLegendPos().getY()+1);
		setTextColor(fruit.getColor());
		std::cout << "LIVES:";
		for (int i = 0; i < pacman.getLives(); i++)
			std::cout << figure;
	}
	
}

void Game::statusScore(ofstream& resultFile)
{
	if (pacman.getScore() ==boardRunGame.getBreadCrunbs())
	{
		if (status == SAVE)
		{
			resultFile << pacman.getNumPointOfLives() << endl;// insert end-win time of current screen
		}
		clear_screen();

		if (!silent) //if silent-dont draw
		{
			gotoxy(20, 12);
			std::cout << "CONGRATULATIONS ! Y O U  WON BOARD NUMBER " << boardRunGame.getCountBoards() << " ! ! !  (press any key to continue)" << endl;
			if (status != LOAD)
				_getch();
			clear_screen();
		}

		isWon = true;
		setIsGameRun(false); //start again
	}

	// if there is a food, increase the score
	if (boardRunGame.getMatGame(pacman.getCurY(), pacman.getCurX()) == '.')
	{
		pacman.increaseScore();
		pacman.increaseBonusScore();
	}

	if (getIsGameRun() && !silent)
	{
		gotoxy(boardRunGame.getLegendPos().getX(), boardRunGame.getLegendPos().getY());
		setTextColor(pacman.getColor());
		std::cout << "SCORE: " << pacman.getScoreWithBonus();
	}
}

void Game::afterDeathInitialization()
{
	if (!silent) //if silent-dont draw
	{
		//update the board
		for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
			ghostsArr[i]->draw(boardRunGame.getMatGame(ghostsArr[i]->getCurY(), ghostsArr[i]->getCurX()), boardRunGame.getColorFood());
	}

	//returns pacman and the ghosts to starting position
	pacman.erase();
	pacman.setCurX(boardRunGame.getPacmanPos().getX());
	pacman.setCurY(boardRunGame.getPacmanPos().getY());

	for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
	{
		ghostsArr[i]->setCurX(boardRunGame.getGhostsPos()[i].getX());
		ghostsArr[i]->setCurY(boardRunGame.getGhostsPos()[i].getY());
		if (!silent) //if silent-dont draw
			ghostsArr[i]->draw(ghostsArr[i]->getFigure(), ghostsArr[i]->getColor());
		ghostsArr[i]->setCounter(0);
		ghostsArr[i]->initAferDeathGhost();		
	}
	
} 

void Game::updateColor()
{
	// if the user chose to play with color 
	if (isColored)
	{
		pacman.setColor(Color::YELLOW);
		boardRunGame.setColorWall(Color::CYAN);
		boardRunGame.setColorFood(Color::GREEN);
		fruit.setColor(Color::LIGHTRED);
	}
	else
	{
		pacman.setColor(Color::WHITE);
		boardRunGame.setColorWall(Color::WHITE);
		boardRunGame.setColorFood(Color::WHITE);
		fruit.setColor(Color::WHITE);
	}

}

vector <int> Game::readResultFile(ifstream& resultFile)
{
vector <int> results;	
	int i = 0;
	int num;
	string str;

	getline(resultFile, str);

	while (!str.empty())
	{
		num = std::stoi(str);//convert string to int
		results.push_back(num);	
		getline(resultFile, str);
	}

	return results;
}


void Game::runGame(string path)
{
	vector <int> resultPointOfTime;
	int resultVectorIndex = 0;
	ofstream stepsFileSave, resultFileSave;
	ifstream stepsFileLoad, resultFileLoad;
	string extractFileName = getFileNameFromPath(path, ".screen");

	if (status == SAVE)
	{		
		stepsFileSave = openFiles(extractFileName, ".steps");
		resultFileSave = openFiles(extractFileName, ".result");
	}

	if (status == LOAD)
	{
		string stepsFileName = extractFileName;
		stepsFileName.append(".steps");

		string resultFileName = extractFileName;
		resultFileName.append(".result");

		stepsFileLoad.open(stepsFileName);
		resultFileLoad.open(resultFileName);

		resultPointOfTime = readResultFile(resultFileLoad);
	}

	updateColor();
	initGame();

	if (silent == false || status != LOAD)
	{
		
		gotoxy(0, 0); // start from the right up corner
		boardRunGame.printBoard();
	}

	if (status != SIMPLE) 
	{
		//update relevant game status
		pacman.setStatusCreature(status);
		for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
		{
			ghostsArr[i]->setStatusCreature(status);
		}
		fruit.setStatusCreature(status);
	}

	while (isGameRun)
	{

		if (status != LOAD)
			pacman.moveCreature(boardRunGame, stepsFileSave);
		else //game status is load mode
		{
			if (moveObjectByFile(stepsFileLoad, 'P', resultPointOfTime, resultVectorIndex))
				isGameRun = false;
		}

		statusScore(resultFileSave);

		if (status != LOAD)
		{
			if (numOfIterations % 2 == 0) { //every 2 steps of pacaman, the ghost and the fruit does 1 step - half pacman's speed

				for (int i = 0; i < boardRunGame.getCountGhosts(); i++)
				{


					if (menu.getChoiceLevel() != 1)
					{
						ghostsArr[i]->checkBestDirection(boardRunGame, pacman.getCurY(), pacman.getCurX());
					}

					if (status == SAVE)
					{
						string str = "Ghost";
						str.append(std::to_string(i)); //adding the num of the ghost to its name
						stepsFileSave << str << " ";
					}

					ghostsArr[i]->moveCreature(boardRunGame, stepsFileSave);
				}
			}
		}
		else
		{			
			if (moveObjectByFile(stepsFileLoad, 'G', resultPointOfTime, resultVectorIndex))
				isGameRun = false;
		}

		if(status != LOAD)
			fruit.moveFruit(pacman, boardRunGame, ghostsArr, numOfIterations,stepsFileSave,status);
		else
		{
			string object, key;
			int cursorPlace = stepsFileLoad.tellg();

			if (stepsFileLoad.eof())
				isGameRun = false;

			stepsFileLoad >> object >> key;

			if (object == "FruitApear")
			{
				fruit.setIsFruitOnScreen(true);
				stepsFileLoad.seekg(cursorPlace, stepsFileLoad.beg);
			}
			else
			{
				stepsFileLoad.seekg(cursorPlace, stepsFileLoad.beg);
			}

			if (fruit.getIsFruitOnScreen())
				moveObjectByFile(stepsFileLoad, 'F', resultPointOfTime, resultVectorIndex);
		}
		
		
		statusLive(resultFileSave, resultPointOfTime, resultVectorIndex);

		if (!silent) //if silent-dont draw
			Sleep(300);
		numOfIterations++;//increase number of iterations
	}

	if (silent && status == LOAD)
	{
		if (pacman.getNumPointOfLives() != resultPointOfTime[resultPointOfTime.size() - 1])//check number of iterations in silent mode
		{
			isSilentComplete = false;
		}
	}

	if (status == SAVE)
	{
		stepsFileSave.close();
		resultFileSave.close();
	}
	else //status = load
	{
		stepsFileLoad.close();
		resultFileLoad.close();
	}

}

bool Game::moveObjectByFile(ifstream& stepsFile, char currObject,vector <int> resultVector, int indexOfVector)
{
	int numGhost, cursorPlace, fruitX,fruitY;
	string object, key, fruitApear = "FruitApear", fruitDisapear = "FruitDisapear";

	cursorPlace = stepsFile.tellg();
	if (!stepsFile.eof()) //check if steps file is over before number of iterations
		stepsFile >> object >> key;
	else //steps file over
		return true;

	if (object == fruitApear)
	{
		fruit.setFigure(key[0]);
		stepsFile >> fruitX >> fruitY;
		fruit.setCurX(fruitX);
		fruit.setCurY(fruitY);
		stepsFile >> object >> key;
	}

	
	if (object == fruitDisapear)
	{
		fruit.setIsFruitOnScreen(false);
		if (!silent) //if silent-dont draw
		{
			if (boardRunGame.getMatGame(fruit.getCurY(), fruit.getCurX()) == ' ')
				fruit.draw(' ', Color::WHITE);
			else if (boardRunGame.getMatGame(fruit.getCurY(), fruit.getCurX()) == '.')
				fruit.draw('.', boardRunGame.getColorFood());
		}

		return false;
	}

	
	if (object[0] != currObject)
	{
		stepsFile.seekg(cursorPlace, stepsFile.beg);
		return false;
	}

	switch (object[0])
	{
	case 'P'://pacman		

		if (key == "STAY")
		{
			return false;
		}

		pacman.erase(); // erase prev step

		boardRunGame.setMatGame(' ', pacman.getCurY(), pacman.getCurX());// update the chars table

		pacman.setKey(keyToNumber(key));

		pacman.checkCreatureObs(boardRunGame, pacman.getDirection(boardRunGame));		
			
		pacman.setCurDir(pacman.getKey());

		if (!silent) //if silent-dont draw
			pacman.draw(pacman.getFigure(), pacman.getColor());

		return false;
	case 'G'://ghosts

		for (numGhost = 0; numGhost < boardRunGame.getCountGhosts(); numGhost++)
		{
			if(numGhost>0)
				stepsFile >> object >> key;

			ghostsArr[numGhost]->erase();

			if (!silent) //if silent-dont draw
			{
				// update the chars table
				if (boardRunGame.getMatGame(ghostsArr[numGhost]->getCurY(), ghostsArr[numGhost]->getCurX()) == ' ')
					ghostsArr[numGhost]->draw(' ', Color::WHITE);
				else if (boardRunGame.getMatGame(ghostsArr[numGhost]->getCurY(), ghostsArr[numGhost]->getCurX()) == '.')
					ghostsArr[numGhost]->draw('.', boardRunGame.getColorFood());
			}

			ghostsArr[numGhost]->setKey(keyToNumber(key));

			ghostsArr[numGhost]->checkObstacle(boardRunGame, ghostsArr[numGhost]->getDirection(boardRunGame));

			ghostsArr[numGhost]->checkCreatureObs(boardRunGame, ghostsArr[numGhost]->getKey());

			
			if (!silent) //if silent-dont draw
				ghostsArr[numGhost]->draw(ghostsArr[numGhost]->getFigure(), ghostsArr[numGhost]->getColor());
		}

		return false;
	case 'F'://fruit

		fruit.erase(); // erase prev step

		if (!silent) //if silent-dont draw
		{
			// update the chars table
			if (boardRunGame.getMatGame(fruit.getCurY(), fruit.getCurX()) == ' ')
				fruit.draw(' ', Color::WHITE);
			else if (boardRunGame.getMatGame(fruit.getCurY(), fruit.getCurX()) == '.')
				fruit.draw('.', boardRunGame.getColorFood());
			else if (boardRunGame.getMatGame(fruit.getCurY(), fruit.getCurX()) == '#')
				fruit.draw('#', boardRunGame.getColorFood());
		}

		fruit.setKey(keyToNumber(key));

		fruit.checkObstacle(boardRunGame, fruit.getDirection(boardRunGame));

		fruit.checkCreatureObs(boardRunGame, fruit.getKey());

		if (((pacman.getCurX() == fruit.getCurX()) && (pacman.getCurY() == fruit.getCurY()))) //if pacman eat fruit he gets the food of fruit.
		{
			pacman.setScoreWithBonus(pacman.getScoreWithBonus() + (fruit.getFigure() - '0'));

			cursorPlace = stepsFile.tellg();
			if (!stepsFile.eof()) //check if steps file is over before number of iterations
				stepsFile >> object >> key;
			else
				return true;

			if (object == fruitDisapear)
			{
				fruit.setIsFruitOnScreen(false);

				if (!silent) //if silent-dont draw
				{
					if (boardRunGame.getMatGame(fruit.getCurY(), fruit.getCurX()) == ' ')
						fruit.draw(' ', Color::WHITE);
					else if (boardRunGame.getMatGame(fruit.getCurY(), fruit.getCurX()) == '.')
						fruit.draw('.', boardRunGame.getColorFood());
				}
				return false;
			}
			else
				stepsFile.seekg(cursorPlace, stepsFile.beg);
		}

		if (!silent) //if silent-dont draw
				fruit.draw(fruit.getFigure(), fruit.getColor());
				
		return false;
	default:
		return false;
	}
	
}

int Game::keyToNumber(string key)
{
	switch (key[0])
	{
	case 'U'://case the char reading from file is up
		return 0;

	case 'D'://case the char reading from file is down
		return 1;

	case 'L'://case the char reading from file is left
		return 2;

	case 'R'://case the char reading from file is right
		return 3;

	default:
		break;
	}
}




ofstream Game::openFiles(string fileName, string end)
{
	string openFileName = fileName;
	openFileName.append(end);
	ofstream retFile;
	retFile.open(openFileName);

	if (!retFile)
	{
		cout << "can't open file" << endl;
	}

	return retFile;
}



string Game::getFileNameFromPath(string path, string end)
{
	int foundIndex=-1, i;
	string fileName;

	for (i = path.size(); i > 0 && foundIndex==-1; i--)
	{
		if (path[i] == '\\')		
			foundIndex = i;
			
		
	}
	for (i = foundIndex + 1; i < (path.size()-end.size()); i++)
	{
		fileName.push_back(path[i]);
	}
	return fileName;
}
