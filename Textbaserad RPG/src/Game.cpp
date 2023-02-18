#include <iostream>
#include "Game.h"
#include "Characters.h"
#include "Enemy.h"
#include "stdlib.h"

//inputs
int input_StartMenu = 0;
int input_TutorialYN = 0;
int input_Combat = 0;
int input_Move = 0;
int input_Choice = 0;
int input_HealWho = 0;


bool mageTurn = true;
bool brawlerTurn = true;

//char array av varje space på mappen
//currentMap är den med spelarens position på
char currentMap[] = "   e_b_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e__h  |     |        |     |        |_____|                    ";
//map har fakta om vilka fiender som är döda eller inte
char map[] = "   e_b_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e__h  |     |        |     |        |_____|                    ";
//detta är startmappen (utan spelare och med alla fiender levande)
const char mapBlueprint[] = "   e_b_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e__h  |     |        |     |        |_____|                    ";

//spelar positioner på mappen
int playerSpawnPosition = 140;
int playerPosition = 0;

/*
012345678901234
   e_b_e     t 
   |   |     | 
___e___e_____e 
|     |    |   
|__   s    |   
  |        |   
  e_____e__e__h
  |     |      
  |__o__|      
*/

//spelar och fiende klasser
Mage mage;
Brawler brawler;
Tank tank;
Enemy enemy1;
Enemy enemy2;
Enemy enemy3;

void Game::Run()
{
	while (true)
	{
		system("cls");
		std::cout << "Text based RPG\n";
		std::cout << "1. Start Game\n";
		std::cout << "2. Credits\n";
		std::cout << "3. Exit\n";

		std::cin >> input_StartMenu;
		
		switch (input_StartMenu)
		{
		case 1:
			StartSetup();
			break;
		case 2:
			Credits();
			break;
		case 3:
			return;
		}

	}
}

void Game::Credits()
{
	system("cls");
	std::cout << "Created by Leo Lundqvist\n";
	std::cout << "Made in Visual studios\n";
	std::cout << "Press enter to go to Main Menu\n";

	std::cin.ignore();
	std::cin.get();
}

void Game::StartSetup()
{
	mage.startStats();
	brawler.setAlive(false);
	tank.setAlive(false);

	//resetar mappen
	for (int i = 0; i < sizeof(mapBlueprint); i++)
	{
		currentMap[i] = mapBlueprint[i];
		map[i] = mapBlueprint[i];
	}
	//sätter ut spelaren på mappen
	playerPosition = playerSpawnPosition;
	currentMap[playerSpawnPosition] = 'o';
	Overworld();
}

void Game::Overworld()
{
	std::cout << "Your party consists of a mage, a brawler and a tank\n";
	std::cout << "Your goal is to defeat the dragon boss at the top of the map\n";

	while (mage.getAlive() == true || brawler.getAlive() == true || tank.getAlive() == true)
	{
		system("cls");
		Map();
		std::cout << "1. Go up\n";
		std::cout << "2. Go down\n";
		std::cout << "3. Go left\n";
		std::cout << "4. Go right\n";

		std::cin >> input_Choice;
		switch(input_Choice)
		{
		case 1:
			if (currentMap[playerPosition - 15] == '|' || currentMap[playerPosition - 15] == '_' || currentMap[playerPosition - 15] == 'x')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition - 15] = 'o';
				playerPosition= playerPosition-15;
			}
			else if (currentMap[playerPosition - 15] == 'e')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition - 15] = 'o';
				playerPosition = playerPosition - 15;
				Combat();
				map[playerPosition] = 'x';
			}
			break;
		case 2:
			if (currentMap[playerPosition + 15] == '|' || currentMap[playerPosition + 15] == '_' || currentMap[playerPosition + 15] == 'x')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition + 15] = 'o';
				playerPosition = playerPosition + 15;
			}
			else if (currentMap[playerPosition + 15] == 'e')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition + 15] = 'o';
				playerPosition = playerPosition + 15;
				Combat();
				map[playerPosition] = 'x';
			}
			break;
		case 3:
			if (currentMap[playerPosition - 1] == '|' || currentMap[playerPosition - 1] == '_' || currentMap[playerPosition - 1] == 'x')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition - 1] = 'o';
				playerPosition--;
			}
			else if (currentMap[playerPosition -1] == 'e')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition -1 ] = 'o';
				playerPosition = playerPosition - 1;
				Combat();
				map[playerPosition] = 'x';
			}
			break;

		case 4:
			if (currentMap[playerPosition + 1] == '|' || currentMap[playerPosition + 1] == '_' || currentMap[playerPosition + 1] == 'x')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition + 1] = 'o';
				playerPosition++;
			}
			else if (currentMap[playerPosition + 1] == 'e')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition + 1] = 'o';
				playerPosition = playerPosition + 1;
				Combat();
				map[playerPosition] = 'x';
			}
			break;

		}
	}
	
}

void Game::Map()
{
	std::cout << "Your map:\n\n";

	//skriver ut mappen
	for (int i = 0; i < sizeof(currentMap); i++) 
	{
		std::cout << currentMap[i];
		//massa enters på dessa specifika punkterna för att mappen är 15 bred och index börjar på 0
		if (i == 14 || i == 29 || i == 44 || i == 59 || i == 74 || i == 89 || i == 104 || i == 119 || i == 134)
		{
			std::cout << "\n";
		}
	}
	//const char* arraynamn = stringnamn.c_str();
	//två arrays, en main mappen utan ändringar och andra med current map

	std::cout << "\n";
	std::cout << "o : you\n";
	std::cout << "b : boss\n";
	std::cout << "e : enemy\n";
	std::cout << "x : defeated enemy\n";
	std::cout << "h : health station\n";
	std::cout << "s : shop\n\n";

}

void Game::BattleSetup()
{

	srand(time(NULL));
	int enemyCount = rand() % 3 + 1;

	srand(time(NULL));
	int whatEnemy1 = rand() % 4 + 1;

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

	switch (whatEnemy1)
	{
	case 1:
		enemy1.setName("Goblin");
		enemy1.setBaseHP(30);
		enemy1.setBaseAttackPower(8);
		enemy1.setBaseMagicPower(8);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getMaxHP());
		break;
	case 2:
		enemy1.setName("Skeleton");
		enemy1.setBaseHP(30);
		enemy1.setBaseAttackPower(8);
		enemy1.setBaseMagicPower(8);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getMaxHP());
		break;
	case 3:
		enemy1.setName("Witch");
		enemy1.setBaseHP(30);
		enemy1.setBaseAttackPower(8);
		enemy1.setBaseMagicPower(8);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getMaxHP());
		break;
	case 4:
		enemy1.setName("Ghoul");
		enemy1.setBaseHP(30);
		enemy1.setBaseAttackPower(8);
		enemy1.setBaseMagicPower(8);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getMaxHP());
		break;
	}
}

void Game::Combat()
{
	system("cls");
	BattleSetup();

	while (true)
	{
		mageTurn = true;
		brawlerTurn = true;
		std::cout << mage.getName() << " : " << mage.getCurrentHP() << "/" << mage.getMaxHP();
		std::cout << "												";
		std::cout << enemy1.getName() << " : " << enemy1.getCurrentHP() << "/" << enemy1.getMaxHP() << "\n";

		//när det är din tur så loopar fighting menyn
		while (mageTurn == true)
		{
			MageTurn();
		}
		while (brawlerTurn == true)
		{
			BrawlerTurn();
		}
		//om fienden dog så vinner du och återvänder till huvudmenyn
		if (enemy1.getAlive() == false)
		{
			//enemy1.getXP()
			mage.addXP(enemy1.getXP());
			std::cout << "You defeated the enemy\n";

			mage.LevelUp();
			std::cout << mage.getName() << " gained " << enemy1.getXP() << " XP and now needs " << mage.getLevelUpRequirement()  << " XP to level up\n";


			std::cout << "Press enter to return to map\n";
			std::cin.ignore();
			std::cin.get();
			return;
		}

		EnemyAI();

		if (mage.getAlive() == false && brawler.getAlive() == false && tank.getAlive() == false)
		{
			std::cout << "You lost\n";
			std::cout << "Press enter to return to main menu\n";

			std::cin.ignore();
			std::cin.get();
			return;
		}
	}
}

void Game::MageTurn()
{
	std::cout << "1. Moves\n";
	std::cout << "2. Items\n";

	std::cin >> input_Combat;
	switch (input_Combat)
	{
		//om du väljer move
	case 1:
		std::cout << "1. " << mage.getAttack1Name() << "\n";
		std::cout << "2. " << mage.getAttack2Name() << "\n";
		std::cout << "3. " << mage.getAttack3Name() << "\n";
		std::cout << "4. " << mage.getAttack4Name() << "\n";
		std::cout << "Type any other number to go back\n";

		std::cin >> input_Move;

		switch (input_Move)
		{
		case 1:
			//skriver ut text och sen attackerar fienden
			std::cout << mage.getName() << " used " << mage.getAttack1Name() << " and dealt " << mage.Attack1() << " to " << enemy1.getName() << "\n";
			enemy1.takeDamage(mage.Attack1());
			mageTurn = false;

			break;
		case 2:
			std::cout << mage.getName() << " used " << mage.getAttack2Name() << " and dealt " << mage.Attack2() << " to " << enemy1.getName() << "\n";
			enemy1.takeDamage(mage.Attack2());
			mageTurn = false;

			break;
		case 3:
			std::cout << "Which party member would you like to heal?\n";
			std::cout << "1. Mage\n";
			std::cout << "2. Brawler\n";
			std::cout << "3. Tank\n";
			std::cout << "Type any other number to go back\n";
			std::cin >> input_HealWho;
			if (input_HealWho == 1)
			{
				//heal funktionen behöver en int och int funktionen behöver en string
				mage.heal(mage.Attack3(mage.getName()));
				mageTurn = false;
			}
			else if (input_HealWho == 2)
			{
				mageTurn = false;
			}
			else if (input_HealWho == 3)
			{
				mageTurn = false;
			}
			break;
		case 4:
			std::cout << mage.getName() << " used " << mage.getAttack4Name() << " and dealt " << mage.Attack4() << " to " << enemy1.getName() << "\n";
			enemy1.takeDamage(mage.Attack4());
			mageTurn = false;

			break;
		}

		break;

		//om du väljer items
	case 2:

		break;

	}
}

void Game::EnemyAI()
{
	mage.takeDamage(enemy1.attack1());
}

