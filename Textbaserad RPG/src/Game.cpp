#include <iostream>
#include "Game.h"

void Game::Run()
{
	//timer start
	//this game is best experienced with fullscreen
	//timer stop

	int input_StartMenu = 0;

	while (true)
	{
		std::cout << "Text based RPG\n";
		std::cout << "1. Start Game\n";
		std::cout << "2. Credits\n";
		std::cout << "3. Exit\n";
	
		std::cin >> input_StartMenu;
		
		system("cls");

		switch (input_StartMenu)
		{
		case 1:
			Start();
			break;
		case 2:
			Credits();
			break;
		case 3:
			return;
		}

	}
}

void Game::Start()
{
	int input_TutorialYN = 0;
	while (true)
	{
		std::cout << "Text based RPG\n";
		std::cout << "1. CombatTutorial\n";
		std::cout << "2. Start Game\n";

		std::cin >> input_TutorialYN;

		switch (input_TutorialYN)
		{
		case 1:
			CombatTutorial();
			break;
		case 2:
			BeginAdventure();
			break;
		}
	}
}

void Game::Credits()
{
	std::cout << "Created by Leo Lundqvist\n";
	std::cout << "Made in Visual studios\n";
	std::cout << "Press enter to go to Main Menu\n";

	std::cin.get();
}

void Game::CombatTutorial()
{
	std::cout << "";

}

void Game::BeginAdventure()
{
}

