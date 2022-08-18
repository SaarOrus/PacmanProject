#include "Game.h"

int main(int argc, char* argv[])
{
	if (argc > 3) // check the user didn't put too much parameters
		return 0;
	if (argc > 1 && argv[1][0] != '-') // if the user wrote load or save without -
		return 0;
	
	if (argc > 1 && strcmp(argv[1], "-load") != 0 && strcmp(argv[1], "-save") != 0)
		return 0;
	if (argc == 3 && strcmp(argv[2], "[-silent]") != 0)
		return 0;

	Game game;

	switch (argc)
	{
	case 1:
		game.gameManager(SIMPLE);
		break;
	case 2:
		if (strcmp(argv[1], "-load") == 0)
			game.gameManager(LOAD);
		else
			game.gameManager(SAVE);
		
		break;
	case 3:
		if (strcmp(argv[1], "-load") == 0)
			game.gameManager(LOAD, true);
		else
			game.gameManager(SAVE);
		break;
	}
	return 0;
}