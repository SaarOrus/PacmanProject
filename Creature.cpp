#include "Creature.h"

int Creature::getDirection(const Board& board)
{
	switch (key) {

	case UP: // up
		coord.decreaseY();

		return UP;
		
	case DOWN: //down
		coord.increaseY();
			
		return DOWN;
		
	case LEFT: //left
		coord.decreaseX();
				
		return LEFT;
		
	case RIGHT: //right
		coord.increaseX();
				
		return RIGHT;
		
	default:

		return UNDEFINED;
	}
}

bool Creature::checkObstacle(const Board& board, int dir)
{

	if (board.getMatGame(coord.getY(), coord.getX()) == '#')//check object doesnt cover the walls
	{
		if (dir == UP)
			coord.increaseY();//y++
		else if (dir == DOWN)
			coord.decreaseY();//y--
		else if (dir == LEFT)
			coord.increaseX();//x++
		else if (dir == RIGHT)
			coord.decreaseX();//x--

		return true;
	}

	return false;
}

void Creature::updateStepsFile(std::ofstream& stepsFile, string objectName, int _key)
{
	string step = keyToName(_key);
	if (!step.empty())
	{
		if (objectName == "Ghost")
			stepsFile << step << " ";
		else
			stepsFile << objectName << " " << step << " ";
	}
		
}

string Creature::keyToName(int _key) {

	switch (_key)
	{
	case Creature::UP:
		return "UP";

	case Creature::DOWN:
		return "DOWN";

	case Creature::LEFT:
		return "LEFT";

	case Creature::RIGHT:
		return "RIGHT";

	default:
		return "";
		break;
	}
}