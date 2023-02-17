#include <iostream>
#include "Game.h"
#include "Characters.h"
#include "Enemy.h"

//inputs
int input_StartMenu = 0;
int input_TutorialYN = 0;
int input_Combat = 0;
int input_Move = 0;

bool yourTurn = true;

//spelar och fiende klasser
Mage mage;


Enemy enemy1;
Enemy enemy2;
Enemy enemy3;

void Game::Run()
{
	while (true)
	{
		std::cout << "Text based RPG\n";
		std::cout << "1. Start Game\n";
		std::cout << "2. Credits\n";
		std::cout << "3. Exit\n";

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
		std::cout << "2. Start game\n";
		std::cout << "3. Return to main menu\n";

		std::cin >> input_TutorialYN;

		switch (input_TutorialYN)
		{
		case 1:
			CombatTutorial();

			break;
		case 2:
			BeginAdventure();
			break;
		case 3:
			return;
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
	yourTurn = true;
	while(true)
	{
		std::cout << mage.getName() << " : " << mage.getCurrentHP();
		std::cout << "												";
		std::cout << enemy1.getName() << " : " << enemy1.getCurrentHP() << "\n";

		//n�r det �r din tur s� loopar fighting menyn
		while (yourTurn == true)
		{
			std::cout << "You can choose to attack or to use an item by pressing 1 or 2...\n";

			std::cout << "1. Moves\n";
			std::cout << "2. Items\n";
		
			std::cin >> input_Combat;
			switch (input_Combat)
			{
			//om du v�ljer move
			case 1:
				std::cout << "Here are your moves\n";
				std::cout << "1. " << mage.getAttack1Name() << "\n";
				std::cout << "2. " << mage.getAttack2Name() << "\n";
				std::cout << "3. " << mage.getAttack3Name() << "\n";
				std::cout << "4. " << mage.getAttack4Name() << "\n";
				std::cout << "Anything else. Go back\n";

				std::cin >> input_Move;
				
				switch (input_Move)
				{
					case 1:
						//skriver ut text och sen attackerar fienden
						std::cout << "Player used " << mage.getAttack1Name() << " and dealt " << mage.Attack1() << " to " << enemy1.getName() << "\n";
						enemy1.takeDamage(mage.Attack1());
						yourTurn = false;

						break;
					case 2:
						std::cout << "Player used " << mage.getAttack2Name() << " and dealt " << mage.Attack2() << " to " << enemy1.getName() << "\n";
						enemy1.takeDamage(mage.Attack2());
						yourTurn = false;

						break;
					case 3:
						mage.Attack3();
						yourTurn = false;

						break;
					case 4:
						std::cout << "Player used " << mage.getAttack4Name() << " and dealt " << mage.Attack4() << " to " << enemy1.getName() << "\n";
						enemy1.takeDamage(mage.Attack4());
						yourTurn = false;

					break;
				}

				break;

			//om du v�ljer items
			case 2:
				std::cout << "Here are your items\n";
				break;

			}

		}

		//om fienden dog s� vinner du och �terv�nder till huvudmenyn
		if (enemy1.getAlive() == false)
		{
			std::cout << "You defeated the enemy and beat the combat tutorial\n";
			std::cout << "Press Enter to go to the main menu\n";
			std::cin.get();

			return;
		}
		
		EnemyAI();

		if (mage.getAlive() == false)
		{
			std::cout << "You were defeated in the combat tutorial, you should be ashamed\n";
			std::cout << "Press Enter to go to the main menu\n";
			std::cin.get();

			return;
		}

	}

}

void Game::BeginAdventure()
{
}

void Game::EnemyAI()
{
	
}

void Game::BattleSetup()
{
	srand(time(NULL));
	int enemyCount = rand() % 3 + 1;
	enemy2.setExists(false);
	enemy3.setExists(false);

	//om det �r mer �n en fiende s� betyder det att det �r �tminstonde 2 fiender
	if (enemyCount > 1)
	{
		enemy2.setExists(true);
	}
	//om det �r 3 fiender
	if (enemyCount == 3)
	{
		enemy3.setExists(true);
	}

	//enemy1 f�r v�rden
}