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
	BattleSetup();
	yourTurn = true;

	while (true)
	{
		std::cout << mage.getName() << " : " << mage.getCurrentHP();
		std::cout << "												";
		std::cout << enemy1.getName() << " : " << enemy1.getCurrentHP() << "\n";

		//gör för alla fiender

		//när det är din tur så loopar fighting menyn
		while (yourTurn == true)
		{
			std::cout << "You can choose to attack or to use an item by pressing 1 or 2...\n";

			std::cout << "1. Moves\n";
			std::cout << "2. Items\n";
		
			std::cin >> input_Combat;
			switch (input_Combat)
			{
			//om du väljer move
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

			//om du väljer items
			case 2:
				std::cout << "Here are your items\n";
				break;

			}

		}

		//om fienden dog så vinner du och återvänder till huvudmenyn
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
	std::cout << "Your party consists of a mage, a abrawler and a tank\n";
	//directions
	//map

}

void Game::EnemyAI()
{
	
}

void Game::BattleSetup()
{
	srand(time(NULL));
	int enemyCount = rand() % 3 + 1;

	srand(time(NULL));
	int whatEnemy = rand() % 4 + 1;

	//om du möter en fiende
	enemy2.setExists(false);
	enemy3.setExists(false);

	//om fienden är besegrad eller inte
	enemy2.setAlive(false);
	enemy3.setAlive(false);


	//om det är mer än en fiende så betyder det att det är åtminstonde 2 fiender
	if (enemyCount > 1)
	{
		enemy2.setExists(true);
		
	}
	//om det är 3 fiender
	if (enemyCount == 3)
	{
		enemy3.setExists(true);
	}

	//enemy1 får värden

	switch (whatEnemy)
	{
	case 1:
		enemy1.setName("Goblin");
		enemy1.setBaseHP(30);
		enemy1.setBaseAttackPower(8);
		enemy1.setBaseMagicPower(8);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getBaseHP());
		break;
	case 2:
		enemy1.setName("Skeleton");
		enemy1.setBaseHP(30);
		enemy1.setBaseAttackPower(8);
		enemy1.setBaseMagicPower(8);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getBaseHP());
		break;
	case 3:
		enemy1.setName("Witch");
		enemy1.setBaseHP(30);
		enemy1.setBaseAttackPower(8);
		enemy1.setBaseMagicPower(8);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getBaseHP());
		break;
	case 4:
		enemy1.setName("Ghoul");
		enemy1.setBaseHP(30);
		enemy1.setBaseAttackPower(8);
		enemy1.setBaseMagicPower(8);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getBaseHP());
		break;
	}
}