#include <iostream>
#include "Game.h"
#include "Characters.h"
#include "Enemy.h"

int input_StartMenu = 0;
int input_TutorialYN = 0;
int input_Combat = 0;


Mage mage;
Goblin goblin;


void Game::Run()
{
	//timer start
	//this game is best experienced with fullscreen
	//timer stop


	while (true)
	{
		std::cout << "Text based RPG\n";
		std::cout << "1. Start Game\n";
		std::cout << "2. Credits\n";
		std::cout << "3. Exit\n";
		std::cout << mage.getName() << "\n";
		std::cout << goblin.getBaseHP() << "\n";

		std::cin >> input_StartMenu;
		
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
	std::cout << "Combat Tutorial\n";
	while(true)
	{
		std::cout << mage.getName() << " : " << mage.getBaseHP();
		std::cout << "												";
		std::cout << mage.getName() << " : " << mage.getBaseHP() << "\n";

		std::cout << "1. Moves\n";
		std::cout << "2. Items\n";

		std::cin >> input_Combat;

		switch (input_Combat)
		{
		case 1:
			
			break;
		case 2:
			
			break;
			
		}

	}

}

void Game::BeginAdventure()
{
}

