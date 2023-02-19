#include <iostream>
#include "Game.h"
#include "Characters.h"
#include "Enemy.h"
#include "Backpack.h"
#include "Items.h"
#include "stdlib.h"

//inputs
int input_StartMenu = 0;
int input_TutorialYN = 0;
int input_Combat = 0;
int input_Move = 0;
int input_Choice = 0;
int input_Who = 0;

bool mageTurn = true;
bool brawlerTurn = true;
bool tankTurn = true;

//char array av varje space på mappen
//currentMap är den med spelarens position på
char currentMap[] = "                  e_b_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e__h  |     |        |     |        |_____|                    ";
//map har fakta om vilka fiender som är döda eller inte
char map[] = "                  e_b_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e__h  |     |        |     |        |_____|                    ";
//detta är startmappen (utan spelare och med alla fiender levande)
const char mapBlueprint[] = "                  e_b_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e__h  |     |        |     |        |_____|                    ";

//spelar positioner på mappen
int playerSpawnPosition = 155;
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

Backpack backpack;
Potion potion;

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
	brawler.startStats();
	tank.startStats();
	backpack.startInventory();

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
			else if (currentMap[playerPosition - 15] == 't')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition - 15] = 'o';
				playerPosition = playerPosition - 15;

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
	std::cout << "Your map:\n";

	//skriver ut mappen
	for (int i = 0; i < sizeof(currentMap); i++) 
	{
		std::cout << currentMap[i];
		//massa enters på dessa specifika punkterna för att mappen är 15 bred och index börjar på 0
		if (i == 14 || i == 29 || i == 44 || i == 59 || i == 74 || i == 89 || i == 104 || i == 119 || i == 134 || i == 149)
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
	std::cout << "x : empty space\n";
	std::cout << "h : health station\n";
	std::cout << "s : shop\n\n";

}

void Game::BattleSetup()
{

	srand((unsigned)time(0));
	int enemyCount = rand() % 3 + 1;
	
	srand((unsigned)time(0) + 1);
	int whatEnemy1 = rand() % 4 + 1;

	int whatEnemy2 = 0;
	int whatEnemy3 = 0;

	std::cout << enemyCount;


	//om det är mer än en fiende så betyder det att det är åtminstonde 2 fiender
	if (enemyCount > 1)
	{
		enemy2.setExists(true);
		srand((unsigned)time(0) + 2);
		whatEnemy2 = rand() % 4 + 1;
	}
	else
	{
		enemy2.setExists(false);
		enemy2.setAlive(false);
		enemy2.setName("Noone");
	}
	//om det är 3 fiender
	if (enemyCount == 3)
	{
		enemy3.setExists(true);
		srand((unsigned)time(0) + 3);
		whatEnemy3 = rand() % 4 + 1;
	}
	else
	{
		enemy3.setExists(false);
		enemy3.setAlive(false);
		enemy3.setName("Noone");
	}

	//enemy1 får värden
	switch (whatEnemy1)
	{
	case 1:
		enemy1.setName("Goblin");
		enemy1.setBaseHP(40);
		enemy1.setBaseAttackPower(14);
		enemy1.setBaseMagicPower(1);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getMaxHP());
		break;
	case 2:
		enemy1.setName("Skeleton");
		enemy1.setBaseHP(60);
		enemy1.setBaseAttackPower(7);
		enemy1.setBaseMagicPower(7);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getMaxHP());
		break;
	case 3:
		enemy1.setName("Witch");
		enemy1.setBaseHP(40);
		enemy1.setBaseAttackPower(1);
		enemy1.setBaseMagicPower(16);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getMaxHP());
		break;
	case 4:
		enemy1.setName("Ghoul");
		enemy1.setBaseHP(80);
		enemy1.setBaseAttackPower(6);
		enemy1.setBaseMagicPower(6);
		enemy1.setAlive(true);
		enemy1.setCurrentHP(enemy1.getMaxHP());
		break;
	}

	switch (whatEnemy2)
	{
	case 1:
		enemy2.setName("Goblin");
		enemy2.setBaseHP(40);
		enemy2.setBaseAttackPower(14);
		enemy2.setBaseMagicPower(1);
		enemy2.setAlive(true);
		enemy2.setCurrentHP(enemy2.getMaxHP());
		break;
	case 2:
		enemy2.setName("Skeleton");
		enemy2.setBaseHP(60);
		enemy2.setBaseAttackPower(7);
		enemy2.setBaseMagicPower(7);
		enemy2.setAlive(true);
		enemy2.setCurrentHP(enemy2.getMaxHP());
		break;
	case 3:
		enemy2.setName("Witch");
		enemy2.setBaseHP(40);
		enemy2.setBaseAttackPower(1);
		enemy2.setBaseMagicPower(16);
		enemy2.setAlive(true);
		enemy2.setCurrentHP(enemy2.getMaxHP());
		break;
	case 4:
		enemy2.setName("Ghoul");
		enemy2.setBaseHP(80);
		enemy2.setBaseAttackPower(6);
		enemy2.setBaseMagicPower(6);
		enemy2.setAlive(true);
		enemy2.setCurrentHP(enemy2.getMaxHP());
		break;
	}

	switch (whatEnemy3)
	{
	case 1:
		enemy3.setName("Goblin");
		enemy3.setBaseHP(40);
		enemy3.setBaseAttackPower(14);
		enemy3.setBaseMagicPower(1);
		enemy3.setAlive(true);
		enemy3.setCurrentHP(enemy3.getMaxHP());
		break;
	case 2:
		enemy3.setName("Skeleton");
		enemy3.setBaseHP(60);
		enemy3.setBaseAttackPower(7);
		enemy3.setBaseMagicPower(7);
		enemy3.setAlive(true);
		enemy3.setCurrentHP(enemy3.getMaxHP());
		break;
	case 3:
		enemy3.setName("Witch");
		enemy3.setBaseHP(40);
		enemy3.setBaseAttackPower(1);
		enemy3.setBaseMagicPower(16);
		enemy3.setAlive(true);
		enemy3.setCurrentHP(enemy3.getMaxHP());
		break;
	case 4:
		enemy3.setName("Ghoul");
		enemy3.setBaseHP(80);
		enemy3.setBaseAttackPower(6);
		enemy3.setBaseMagicPower(6);
		enemy3.setAlive(true);
		enemy3.setCurrentHP(enemy3.getMaxHP());
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

		HPBar();

		//när det är din tur så loopar fighting menyn
		while (mageTurn == true && mage.getAlive() == true)
		{
			MageTurn();
		}

		//om alla fiender är döda
		if (enemy1.getAlive() == false && enemy2.getAlive() == false && enemy3.getAlive() == false)
		{
			BattleWon();
			return;
		}

		if (mage.getAlive() == true)
		{
			HPBar();
		}

		while (brawlerTurn == true && brawler.getAlive() == true)
		{
			BrawlerTurn();
		}

		//om alla fiender är döda
		if (enemy1.getAlive() == false && enemy2.getAlive() == false && enemy3.getAlive() == false)
		{
			BattleWon();
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

void Game::HPBar()
{
	std::cout << mage.getName() << " : " << mage.getCurrentHP() << "/" << mage.getMaxHP();
	std::cout << "												";
	std::cout << enemy1.getName() << " : " << enemy1.getCurrentHP() << "/" << enemy1.getMaxHP() << "\n";
	std::cout << brawler.getName() << " : " << brawler.getCurrentHP() << "/" << brawler.getMaxHP();
	std::cout << "												";
	if (enemy2.getExists() == true)
	{
		std::cout << enemy2.getName() << " : " << enemy2.getCurrentHP() << "/" << enemy2.getMaxHP(); //ändra till enemy 2 sen
	}
	std::cout << "\n" << tank.getName() << " : " << tank.getCurrentHP() << "/" << tank.getMaxHP();
	std::cout << "												";
	if (enemy3.getExists() == true)
	{
		std::cout << enemy3.getName() << " : " << enemy3.getCurrentHP() << "/" << enemy3.getMaxHP(); //ändra till enemy 2 sen
	}
	std::cout << "\n";

}

void Game::MageTurn()
{
	std::cout << mage.getName() << "'s turn\n";

	std::cout << "1. Moves\n";
	std::cout << "2. Items\n";

	std::cin >> input_Combat;
	switch (input_Combat)
	{
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

			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			if (input_Who == 1 && enemy1.getExists() == true)
			{
				//heal funktionen behöver en int och int funktionen behöver en string
				std::cout << mage.getName() << " used " << mage.getAttack1Name() << " and dealt " << mage.Attack1() << " to " << enemy1.getName() << "\n";
				enemy1.takeDamage(mage.Attack1());
				mageTurn = false;
			}
			else if (input_Who == 2 && enemy2.getExists() == true)
			{
				std::cout << mage.getName() << " used " << mage.getAttack1Name() << " and dealt " << mage.Attack1() << " to " << enemy2.getName() << "\n";
				enemy2.takeDamage(mage.Attack1());
				mageTurn = false;
			}
			else if (input_Who == 3 && enemy3.getExists() == true)
			{
				std::cout << mage.getName() << " used " << mage.getAttack1Name() << " and dealt " << mage.Attack1() << " to " << enemy3.getName() << "\n";
				enemy3.takeDamage(mage.Attack1());
				mageTurn = false;
			}
			else
			{
				std::cout << "There's no enemy there...\n";
			}

			break;
		case 2:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			//vem man attackerar
			if (input_Who == 1 && enemy1.getExists() == true)
			{
				std::cout << mage.getName() << " used " << mage.getAttack2Name() << " and dealt " << mage.Attack2() << " to " << enemy1.getName() << "\n";
				enemy1.takeDamage(mage.Attack2());
				mageTurn = false;
			}
			else if (input_Who == 2 && enemy2.getExists() == true)
			{
				std::cout << mage.getName() << " used " << mage.getAttack2Name() << " and dealt " << mage.Attack2() << " to " << enemy2.getName() << "\n";
				enemy2.takeDamage(mage.Attack2());
				mageTurn = false;
			}
			else if (input_Who == 3 && enemy3.getExists() == true)
			{
				std::cout << mage.getName() << " used " << mage.getAttack2Name() << " and dealt " << mage.Attack2() << " to " << enemy3.getName() << "\n";
				enemy3.takeDamage(mage.Attack2());
				mageTurn = false;
			}
			else
			{
				std::cout << "There's no enemy there...\n";
			}

			break;
		case 3:
			std::cout << "Which party member would you like to heal?\n";
			std::cout << "1. Mage\n";
			std::cout << "2. Brawler\n";
			std::cout << "3. Tank\n";
			std::cout << "Type any other number to go back\n";
			std::cin >> input_Who;
			if (input_Who == 1)
			{
				//heal funktionen behöver en int och int funktionen behöver en string
				mage.heal(mage.Attack3(mage.getName()));
				mageTurn = false;
			}
			else if (input_Who == 2)
			{
				brawler.heal(mage.Attack3(brawler.getName()));
				mageTurn = false;
			}
			else if (input_Who == 3)
			{
				tank.heal(mage.Attack3(tank.getName()));
				mageTurn = false;
			}
			break;
		case 4:
			std::cout << mage.getName() << " used " << mage.getAttack4Name() << " and dealt " << mage.Attack4() << " to every enemy\n";
			enemy1.takeDamage(mage.Attack4());
			enemy2.takeDamage(mage.Attack4());
			enemy3.takeDamage(mage.Attack4());

			mageTurn = false;

			break;
		}

		break;

		//om du väljer items
	case 2:

		break;

	}
}

void Game::BrawlerTurn()
{
	std::cout << brawler.getName() << "'s turn\n";
	std::cout << "1. Moves\n";
	std::cout << "2. Items\n";

	std::cin >> input_Combat;
	switch (input_Combat)
	{
		//om du väljer move
	case 1:
		std::cout << "1. " << brawler.getAttack1Name() << "\n";
		std::cout << "2. " << brawler.getAttack2Name() << "\n";
		std::cout << "3. " << brawler.getAttack3Name() << "\n";
		std::cout << "Type any other number to go back\n";

		std::cin >> input_Move;

		switch (input_Move)
		{
		//attack 1
		case 1:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			if (input_Who == 1 && enemy1.getExists() == true)
			{
				//heal funktionen behöver en int och int funktionen behöver en string
				std::cout << brawler.getName() << " used " << brawler.getAttack1Name() << " and dealt " << brawler.Attack1() << " to " << enemy1.getName() << "\n";
				enemy1.takeDamage(brawler.Attack1());
				brawlerTurn = false;
			}
			else if (input_Who == 2 && enemy2.getExists() == true)
			{
				std::cout << brawler.getName() << " used " << brawler.getAttack1Name() << " and dealt " << brawler.Attack1() << " to " << enemy2.getName() << "\n";
				enemy2.takeDamage(brawler.Attack1());
				brawlerTurn = false;
			}
			else if (input_Who == 3 && enemy3.getExists() == true)
			{
				std::cout << brawler.getName() << " used " << brawler.getAttack1Name() << " and dealt " << brawler.Attack1() << " to " << enemy3.getName() << "\n";
				enemy3.takeDamage(brawler.Attack1());
				brawlerTurn = false;
				mageTurn = false;
			}
			else
			{
				std::cout << "There's no enemy there...\n";
			}

			break;
		//attack 2
		case 2:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			if (input_Who == 1 && enemy1.getExists() == true)
			{
				//heal funktionen behöver en int och int funktionen behöver en string
				std::cout << brawler.getName() << " used " << brawler.getAttack2Name() << " and dealt " << brawler.Attack2() << " to " << enemy1.getName() << "\n";
				enemy1.takeDamage(brawler.Attack2());
				brawlerTurn = false;
			}
			else if (input_Who == 2 && enemy2.getExists() == true)
			{
				std::cout << brawler.getName() << " used " << brawler.getAttack2Name() << " and dealt " << brawler.Attack2() << " to " << enemy2.getName() << "\n";
				enemy2.takeDamage(brawler.Attack2());
				brawlerTurn = false;
			}
			else if (input_Who == 3 && enemy3.getExists() == true)
			{
				std::cout << brawler.getName() << " used " << brawler.getAttack2Name() << " and dealt " << brawler.Attack2() << " to " << enemy3.getName() << "\n";
				enemy3.takeDamage(brawler.Attack2());
				brawlerTurn = false;
			}
			else
			{
				std::cout << "There's no enemy there...\n";
			}

			break;
		//attack 3
		case 3:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			if (input_Who == 1 && enemy1.getExists() == true)
			{
				//heal funktionen behöver en int och int funktionen behöver en string
				enemy1.takeDamage(brawler.Attack3());
				std::cout << " damage to " << enemy1.getName() << "\n";
				brawlerTurn = false;
			}
			else if (input_Who == 2 && enemy2.getExists() == true)
			{
				enemy2.takeDamage(brawler.Attack3());
				std::cout << " damage to " << enemy2.getName() << "\n";
				brawlerTurn = false;
			}
			else if (input_Who == 3 && enemy3.getExists() == true)
			{
				enemy3.takeDamage(brawler.Attack3());
				std::cout << " damage to " << enemy3.getName() << "\n";
				brawlerTurn = false;
			}
			else
			{
				std::cout << "There's no enemy there...\n";
			}
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

void Game::BattleWon()
{
	//ger karaktärerna xp
	mage.addXP(enemy1.getXP());
	brawler.addXP(enemy1.getXP());

	std::cout << "You won the battle\n";

	//skriver ut hur mycket de får, om de levlade upp och hur mycket det är kvar
	std::cout << mage.getName() << " gained " << enemy1.getXP() << " XP\n";
	std::cout << brawler.getName() << " gained " << enemy1.getXP() << " XP\n";
	mage.LevelUp();
	brawler.LevelUp();
	std::cout << mage.getName() << " now needs " << mage.getLevelUpRequirement() << " XP to level up\n";
	std::cout << brawler.getName() << " now needs " << brawler.getLevelUpRequirement() << " XP to level up\n";

	std::cout << "Press enter to return to map\n";
	std::cin.ignore();
	std::cin.get();
}
