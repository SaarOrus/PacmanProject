#include "Menu.h"


void Menu::enterYourBoard()
{
	clear_screen();
	cout << "Enter your fileName" << endl;
	cin >> userFileName;
}

void Menu::printSilentMessage(bool succesful) const
{
	gotoxy(0, 0);

	if (succesful)
		cout << "Test passed" << endl;
	else
		cout << "Test failed"<<endl;
}

void Menu::printAndGetMenu()
{
	clear_screen();

	setTextColor(Color::WHITE);
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> WELCOME TO PACAMAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<\n" << endl
		<< "1. Start a new game - Without colors" << endl
		<< "2. Start a new game - With colors" << endl
		<< "3. Start a new game - With the name of the board you want" << endl
		<< "8. Present instructions and keys" << endl
		<< "9. EXIT" << endl;

	do {
		cin >> choiceMenu;

		if (choiceMenu != 1 && choiceMenu != 2 && choiceMenu != 3 && choiceMenu != 4 && choiceMenu != 8 && choiceMenu != 9)
			cout << "WRONG INPUT. Please choose valid choice." << endl;

	} while (choiceMenu != 1 && choiceMenu != 2 && choiceMenu != 3 && choiceMenu != 4 && choiceMenu != 8 && choiceMenu != 9);

}

void Menu::printAndGetLevelGhost()
{
	clear_screen();

	setTextColor(Color::WHITE);
	cout << "Choose your level :" << endl
		<< "1. Beginner" << endl
		<< "2. Advanced" << endl
		<< "3. Fully controled" << endl;

	do {
		cin >> choiceLevel;
		if (choiceLevel != 1 && choiceLevel != 2 && choiceLevel != 3)
			cout << "WRONG INPUT. Please choose valid level." << endl;

	} while (choiceLevel != 1 && choiceLevel != 2 && choiceLevel != 3);

}


void Menu::printInstructions() const {

	clear_screen();

	do
	{
		cout << "Goal: \nGuide Pacman around the maze and eat all the little white dots whilst avoiding the ghosts." << endl
			<< "\nKeys: \nW-up \nX-down \nD-right \nA-left \nS-stay in your place\n\nPress any key to go back to menu\n";
	} while (!_getch());
	
}