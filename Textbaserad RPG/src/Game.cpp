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
int input_Shop = 0;
int input_Amount = 0;
char input_Grade = 'O';

//turns
bool mageTurn = true;
bool brawlerTurn = true;
bool tankTurn = true;

//char array av varje space på mappen
//currentMap är den med spelarens position på
char currentMap[] = "                  e_g_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e     |     |        |     |        |_____|                    ";
//map har fakta om vilka fiender som är döda eller inte
char map[] = "                  e_g_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e     |     |        |     |        |_____|                    ";
//detta är startmappen (utan spelare och med alla fiender levande)
const char mapBlueprint[] = "                  e_g_e          |   |     t ___e___e_____e |     |    |   |__   s    |     |        |     e_____e__e     |     |        |     |        |_____|                    ";

//spelar positioner på mappen
int playerSpawnPosition = 155;
int playerPosition = 0;

//enemy
int enemyTarget = 0;

//spelar och fiende klasser
Mage mage;
Brawler brawler;
Tank tank;
Enemy enemy1;
Enemy enemy2;
Enemy enemy3;

Backpack backpack;
Potion potion;
Revive revive;

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
	while (mage.getAlive() == true || brawler.getAlive() == true || tank.getAlive() == true)
	{
		system("cls");
		std::cout << "Reach the goal at the top of the map to win\n";
		Map();
		std::cout << "1. Go up\n";
		std::cout << "2. Go down\n";
		std::cout << "3. Go left\n";
		std::cout << "4. Go right\n";
		std::cout << "5. Look in inventory\n";
		std::cout << "6. Look at party\n";
		std::cout << "7. Return to main menu\n";

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
				Treasure();
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
			else if (currentMap[playerPosition + 15] == 's')
			{
				currentMap[playerPosition] = map[playerPosition];
				currentMap[playerPosition + 15] = 'o';
				playerPosition = playerPosition + 15;
				Shop();
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
			else if (currentMap[playerPosition - 1] == 'g')
			{
				system("cls");
				std::cout << "You won!\n";
				std::cout << "Press enter to return to the main menu\n";
				std::cin.ignore();
				std::cin.get();
				return;
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
			else if (currentMap[playerPosition + 1] == 'g')
			{
				system("cls");
				std::cout << "You won!\n";
				std::cout << "Press enter to return to the main menu\n";
				std::cin.ignore();
				std::cin.get();
			}
			break;
		//inventory
		case 5:
			system("cls");
			std::cout << "Inventory\n";
			std::cout << "Money : " << backpack.getMoney() << "\n";
			std::cout << "Potions : " << backpack.getPotions() << "\n";
			std::cout << "Revives : " << backpack.getRevives() << "\n";

			std::cout << "Press enter to return to the Map\n";

			std::cin.ignore();
			std::cin.get();
			break;

		case 6:
			system("cls");
			std::cout << "Party Member 1: "<< mage.getName() << "\n";
			std::cout << "Species : " << mage.getSpecies() << "\n";
			std::cout << "HP : " << mage.getCurrentHP() << "/" << mage.getMaxHP() << "\n";
			std::cout << "Level : " << mage.getLevel() << "\n";
			std::cout << "XP : " << mage.getXP() << "/" << mage.getLevelUpRequirement() << "\n";
			std::cout << "Attack : " << mage.getName() << "\n";
			std::cout << "Magic : " << mage.getName() << "\n\n";

			std::cout << "Party Member 2: " << brawler.getName() << "\n";
			std::cout << "Species : " << brawler.getSpecies() << "\n";
			std::cout << "HP : " << brawler.getCurrentHP() << "/" << brawler.getMaxHP() << "\n";
			std::cout << "Level : " << brawler.getLevel() << "\n";
			std::cout << "XP : " << brawler.getXP() << "/" << brawler.getLevelUpRequirement() << "\n";
			std::cout << "Attack : " << brawler.getName() << "\n";
			std::cout << "Magic : " << brawler.getName() << "\n\n";

			std::cout << "Party Member 3: " << tank.getName() << "\n";
			std::cout << "Species : " << tank.getSpecies() << "\n";
			std::cout << "HP : " << tank.getCurrentHP() << "/" << tank.getMaxHP() << "\n";
			std::cout << "Level : " << tank.getLevel() << "\n";
			std::cout << "XP : " << tank.getXP() << "/" << tank.getLevelUpRequirement() << "\n";
			std::cout << "Attack : " << tank.getName() << "\n";
			std::cout << "Magic : " << tank.getName() << "\n\n";

			std::cout << "Press enter to return to the Map\n";

			std::cin.ignore();
			std::cin.get();
			break;
		case 7:
			return;
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
	std::cout << "g : goal\n";
	std::cout << "e : enemy\n";
	std::cout << "x : empty space\n";
	std::cout << "s : shop\n\n";

}

void Game::Treasure()
{
	std::cout << "Before you stands a treasure chest with a one letter combination lock\n";
	std::cout << "Over the lock is a note, and it says\n";
	std::cout << "'The combination is this assignments grade, but if you get it wrong the chest will evaporate'\n";
	std::cout << "Type in one letter\n";
	std::cin >> input_Grade;
	if ((char)tolower(input_Grade) == 'b')
	{
		std::cout << "Congratulations, you got it right\n";
		backpack.rewardMoney(100000);
	}
	else if((char)tolower(input_Grade) == 'f')
	{
		std::cout << "Du är en ondskeful man\n";
	}
	else
	{
		std::cout << "The answer was B\n";
	}
	std::cout << "Press enter to return to the Map\n";

	std::cin.ignore();
	std::cin.get();

}

void Game::BattleSetup()
{

	srand((unsigned)time(0));
	int enemyCount = rand() % 3 + 1;
	
	srand((unsigned)time(0) + 1);
	int whatEnemy1 = rand() % 4 + 1;

	int whatEnemy2 = 0;
	int whatEnemy3 = 0;

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
		tankTurn = true;
		//gör så han inte protectar sina teammates varje runda
		tank.Attack3(false);

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

		while (brawlerTurn == true && brawler.getAlive() == true)
		{
			BrawlerTurn();
		}

		if (enemy1.getAlive() == false && enemy2.getAlive() == false && enemy3.getAlive() == false)
		{
			BattleWon();
			return;
		}

		while (tankTurn == true && tank.getAlive() == true)
		{
			TankTurn();
		}

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
	//fiende död är inget namn ingen där h9aha
	if (enemy1.getAlive() == false)
	{
		enemy1.setName("Noone");
	}
	if (enemy2.getAlive() == false)
	{
		enemy2.setName("Noone");
	}
	if (enemy3.getAlive() == false)
	{
		enemy3.setName("Noone");
	}


	std::cout << mage.getName() << " : " << mage.getCurrentHP() << "/" << mage.getMaxHP();
	std::cout << "												";

	if (enemy1.getAlive() == true)
	{
		std::cout << enemy1.getName() << " : " << enemy1.getCurrentHP() << "/" << enemy1.getMaxHP();
	}

	std::cout << "\n" << brawler.getName() << " : " << brawler.getCurrentHP() << "/" << brawler.getMaxHP();
	std::cout << "												";

	if (enemy2.getExists() == true && enemy2.getAlive() == true)
	{
		std::cout << enemy2.getName() << " : " << enemy2.getCurrentHP() << "/" << enemy2.getMaxHP();
	}

	std::cout << "\n" << tank.getName() << " : " << tank.getCurrentHP() << "/" << tank.getMaxHP();
	std::cout << "												";

	if (enemy3.getExists() == true && enemy3.getAlive() == true)
	{
		std::cout << enemy3.getName() << " : " << enemy3.getCurrentHP() << "/" << enemy3.getMaxHP();
	}
	std::cout << "\n\n";

}

void Game::MageTurn()
{
	system("cls");
	HPBar();
	std::cout << mage.getName() << "'s turn\n";

	std::cout << "1. Moves\n";
	std::cout << "2. Items\n";

	std::cin >> input_Combat;
	system("cls");
	HPBar();
	switch (input_Combat)
	{
	case 1:
		std::cout << "1. " << mage.getAttack1Name() << "\n";
		std::cout << "2. " << mage.getAttack2Name() << "\n";
		std::cout << "3. " << mage.getAttack3Name() << "\n";
		std::cout << "4. " << mage.getAttack4Name() << "\n";
		std::cout << "Type any other number to go back\n";

		std::cin >> input_Move;
		system("cls");
		HPBar();
		switch (input_Move)
		{
		case 1:

			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			system("cls");
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
				std::cout << "There's no enemy there...";
				std::cin.ignore();
				std::cin.get();
			}

			break;
		case 2:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			system("cls");

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
				std::cout << "There's no enemy there...";
				std::cin.ignore();
				std::cin.get();
			}

			break;
		case 3:
			std::cout << "Which party member would you like to heal?\n";
			std::cout << "1. Mage\n";
			std::cout << "2. Brawler\n";
			std::cout << "3. Tank\n";
			std::cout << "Type any other number to go back\n";
			std::cin >> input_Who;
			system("cls");

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
		UseItems();
		break;

	}
}

void Game::BrawlerTurn()
{
	std::cin.ignore();
	std::cin.get();
	system("cls");
	HPBar();
	std::cout << brawler.getName() << "'s turn\n";
	std::cout << "1. Moves\n";
	std::cout << "2. Items\n";

	std::cin >> input_Combat;
	system("cls");
	HPBar();
	switch (input_Combat)
	{
		//om du väljer move
	case 1:
		std::cout << "1. " << brawler.getAttack1Name() << "\n";
		std::cout << "2. " << brawler.getAttack2Name() << "\n";
		std::cout << "3. " << brawler.getAttack3Name() << "\n";
		std::cout << "Type any other number to go back\n";

		std::cin >> input_Move;
		system("cls");
		HPBar();
		switch (input_Move)
		{
		//attack 1
		case 1:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			system("cls");
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
				std::cout << "There's no enemy there...";
			}

			break;
		//attack 2
		case 2:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			system("cls");
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
				std::cout << "There's no enemy there...";
			}

			break;
		//attack 3
		case 3:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			system("cls");
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
				std::cout << "There's no enemy there...";
			}
			break;
		}

		break;

		//om du väljer items
	case 2:
		UseItems();

		break;

	}
}

void Game::TankTurn()
{
	std::cin.ignore();
	std::cin.get();
	system("cls");
	HPBar();

	std::cout << tank.getName() << "'s turn\n";

	std::cout << "1. Moves\n";
	std::cout << "2. Items\n";

	std::cin >> input_Combat;
	system("cls");
	HPBar();
	switch (input_Combat)
	{
	case 1:
		std::cout << "1. " << tank.getAttack1Name() << "\n";
		std::cout << "2. " << tank.getAttack2Name() << "\n";
		std::cout << "3. " << tank.getAttack3Name() << "\n";
		std::cout << "Type any other number to go back\n";

		std::cin >> input_Move;
		system("cls");
		HPBar();

		switch (input_Move)
		{
		case 1:

			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			system("cls");
			if (input_Who == 1 && enemy1.getExists() == true)
			{
				//heal funktionen behöver en int och int funktionen behöver en string
				std::cout << tank.getName() << " used " << tank.getAttack1Name() << " and dealt " << tank.Attack1() << " to " << enemy1.getName() << "\n";
				enemy1.takeDamage(tank.Attack1());
				tankTurn = false;
			}
			else if (input_Who == 2 && enemy2.getExists() == true)
			{
				std::cout << tank.getName() << " used " << tank.getAttack1Name() << " and dealt " << tank.Attack1() << " to " << enemy2.getName() << "\n";
				enemy2.takeDamage(tank.Attack1());
				tankTurn = false;
			}
			else if (input_Who == 3 && enemy3.getExists() == true)
			{
				std::cout << tank.getName() << " used " << tank.getAttack1Name() << " and dealt " << tank.Attack1() << " to " << enemy3.getName() << "\n";
				enemy3.takeDamage(tank.Attack1());
				tankTurn = false;
			}
			else
			{
				std::cout << "There's no enemy there...";
			}

			break;
		case 2:
			std::cout << "Which enemy would you like to attack?\n";
			std::cout << "1. " << enemy1.getName() << "\n";
			std::cout << "2. " << enemy2.getName() << "\n";
			std::cout << "3. " << enemy3.getName() << "\n";
			std::cin >> input_Who;
			//vem man attackerar
			system("cls");
			if (input_Who == 1 && enemy1.getExists() == true)
			{
				std::cout << tank.getName() << " used " << tank.getAttack2Name() << " and dealt " << tank.Attack2() << " to " << enemy1.getName() << "\n";
				enemy1.takeDamage(tank.Attack2());
				tankTurn = false;
			}
			else if (input_Who == 2 && enemy2.getExists() == true)
			{
				std::cout << tank.getName() << " used " << tank.getAttack2Name() << " and dealt " << tank.Attack2() << " to " << enemy2.getName() << "\n";
				enemy2.takeDamage(tank.Attack2());
				tankTurn = false;
			}
			else if (input_Who == 3 && enemy3.getExists() == true)
			{
				std::cout << tank.getName() << " used " << tank.getAttack2Name() << " and dealt " << tank.Attack2() << " to " << enemy3.getName() << "\n";
				enemy3.takeDamage(tank.Attack2());
				tankTurn = false;
			}
			else
			{
				std::cout << "There's no enemy there...";
			}
			break;
		case 3:
			system("cls");
			std::cout << tank.getName() << " used distract\n";
			tank.Attack3(true);
			std::cout << "The enemies can only attack " << tank.getName() <<" this round\n";
			tankTurn = false;

			break;
		}

		break;

		//om du väljer items
	case 2:
		UseItems();

		break;

	}
}

void Game::EnemyAI()
{
	//spagetti kod delen av projektet
	//Jag har inte tid att göra en bra "AI" och jag har aldrig gjort en AI

	srand((unsigned)time(0)+1);
	enemyTarget = rand() % 3 + 1;
	//enemy 1 "AI"
	if(enemy1.getAlive() == true && enemy1.getExists() == true)
	{
		//om tank protectar
		if (tank.getProtecting() == true && tank.getAlive() == true)
		{
			if (enemy1.attack1() > enemy1.attack2())
			{
				std::cout << enemy1.getName() << " used " << enemy1.getAttack1Name() << " and dealt " << enemy1.attack1() << " to " << tank.getName() << "\n";
				tank.takeDamage(enemy1.attack1());
			}
			else
			{
				std::cout << enemy1.getName() << " used " << enemy2.getAttack1Name() << " and dealt " << enemy2.attack1() << " to " << tank.getName() << "\n";
				tank.takeDamage(enemy1.attack2());
			}
		}
		//om tank är låg
		else if (tank.getCurrentHP() < enemy1.attack1())
		{
			std::cout << enemy1.getName() << " used " << enemy1.getAttack1Name() << " and dealt " << enemy1.attack1() << " to " << enemy1.getName() << "\n";
			tank.takeDamage(enemy1.attack1());
		}
		else if (tank.getCurrentHP() < enemy1.attack2())
		{
			std::cout << enemy1.getName() << " used " << enemy1.getAttack2Name() << " and dealt " << enemy1.attack2() << " to " << tank.getName() << "\n";
			tank.takeDamage(enemy1.attack2());
		}
		//om mage är låg
		else if (mage.getCurrentHP() < enemy1.attack1())
		{
			std::cout << enemy1.getName() << " used " << enemy1.getAttack1Name() << " and dealt " << enemy1.attack1() << " to " << mage.getName() << "\n";
			mage.takeDamage(enemy1.attack1());
		}
		else if (mage.getCurrentHP() < enemy1.attack2())
		{
			std::cout << enemy1.getName() << " used " << enemy1.getAttack2Name() << " and dealt " << enemy1.attack2() << " to " << mage.getName() << "\n";
			mage.takeDamage(enemy1.attack2());
		}
		else if (brawler.getCurrentHP() < enemy1.attack1())
		{
			std::cout << enemy1.getName() << " used " << enemy1.getAttack1Name() << " and dealt " << enemy1.attack1() << " to " << brawler.getName() << "\n";
			brawler.takeDamage(enemy1.attack1());
		}
		else if (brawler.getCurrentHP() < enemy1.attack2())
		{
			std::cout << enemy1.getName() << " used " << enemy1.getAttack2Name() << " and dealt " << enemy1.attack2() << " to " << brawler.getName() << "\n";
			brawler.takeDamage(enemy1.attack2());
		}
		//tank
		else if (enemyTarget == 1)
		{
			if(enemy1.attack1() > enemy1.attack2())
			{
				std::cout << enemy1.getName() << " used " << enemy1.getAttack1Name() << " and dealt " << enemy1.attack1() << " to " << enemy1.getName() << "\n";
				tank.takeDamage(enemy1.attack1());
			}
			else 
			{
				std::cout << enemy1.getName() << " used " << enemy1.getAttack2Name() << " and dealt " << enemy1.attack2() << " to " << tank.getName() << "\n";
				tank.takeDamage(enemy1.attack2());
			}
		}
		//mage
		else if (enemyTarget == 2)
		{
			if (enemy1.attack1() > enemy1.attack2())
			{
				std::cout << enemy1.getName() << " used " << enemy1.getAttack1Name() << " and dealt " << enemy1.attack1() << " to " << mage.getName() << "\n";
				mage.takeDamage(enemy1.attack1());
			}
			else
			{
				std::cout << enemy1.getName() << " used " << enemy1.getAttack2Name() << " and dealt " << enemy1.attack2() << " to " << mage.getName() << "\n";
				mage.takeDamage(enemy1.attack2());
			}
		}
		//brawler
		else if (enemyTarget == 3)
		{
			if (enemy1.attack1() > enemy1.attack2())
			{
				std::cout << enemy1.getName() << " used " << enemy1.getAttack1Name() << " and dealt " << enemy1.attack1() << " to " << brawler.getName() << "\n";
				brawler.takeDamage(enemy1.attack1());
			}
			else
			{
				std::cout << enemy1.getName() << " used " << enemy1.getAttack2Name() << " and dealt " << enemy1.attack2() << " to " << brawler.getName() << "\n";
				brawler.takeDamage(enemy1.attack2());
			}
		}


	}
	//jag kan fixa så att alla fiender kan attackera men det är bara att kopiera koden och ändra några värden
	//tror inte att det är värt för att det kommer inte höja betyget och det finns andra viktigare saker jag kan göra med tiden

	std::cin.ignore();
	std::cin.get();
}

void Game::BattleWon()
{
	//ger karaktärerna xp
	mage.addXP(enemy1.getXP());
	brawler.addXP(enemy1.getXP());
	tank.addXP(enemy1.getXP());

	std::cout << "You won the battle\n";

	//skriver ut hur mycket de får, om de levlade upp och hur mycket det är kvar
	std::cout << mage.getName() << " gained " << enemy1.getXP() << " XP\n";
	std::cout << brawler.getName() << " gained " << enemy1.getXP() << " XP\n";
	std::cout << tank.getName() << " gained " << enemy1.getXP() << " XP\n";
	mage.LevelUp();
	brawler.LevelUp();
	tank.LevelUp();
	std::cout << mage.getName() << " now needs " << mage.getLevelUpRequirement() << " XP to level up\n";
	std::cout << brawler.getName() << " now needs " << brawler.getLevelUpRequirement() << " XP to level up\n";
	std::cout << tank.getName() << " now needs " << tank.getLevelUpRequirement() << " XP to level up\n";

	backpack.rewardMoney(enemy1.getMoney());

	std::cout << "Press enter to return to map\n";
	std::cin.ignore();
	std::cin.get();
}

void Game::Shop()
{
	std::cout << "What do you want to buy?\n";
	std::cout << "1. " << potion.getName() << " which costs " << potion.getCost()  << "\n";
	std::cout << "2. " << revive.getName() << " which costs " << revive.getCost() << "\n";
	std::cout << "Press anything else to return to map\n";
	std::cin >> input_Shop;
	if(input_Shop == 1)
	{
		std::cout << "How many?\n";
		std::cout << "Your money : " << backpack.getMoney() << "\n";

		std::cin >> input_Amount;
		if (input_Amount * potion.getCost() > backpack.getMoney())
		{
			std::cout << "You don't have the money for that many\n";
			std::cout << "Press anything to return to map\n";
			std::cin.ignore();
			std::cin.get();
		}
		else
		{
			backpack.recivePotions(input_Amount);
			backpack.buy(input_Amount * potion.getCost());
		}
	}
	else if (input_Shop == 2)
	{
		std::cout << "How many?\n";
		std::cin >> input_Amount;
		if (input_Amount * revive.getCost() > backpack.getMoney())
		{
			std::cout << "You don't have the money for that many\n";
			std::cout << "Press anything to return to map\n";
			std::cin.ignore();
			std::cin.get();
		}
		else
		{
			backpack.reciveRevives(input_Amount);
			backpack.buy(input_Amount*revive.getCost());
		}
	}

}

void Game::UseItems()
{
	std::cout << "What do you want to use?\n";
	std::cout << "1. " << potion.getName() << " (" << potion.getHealPoints() << " hp) Amount in backpack : " << backpack.getPotions()  << "\n";
	std::cout << "2. " << revive.getName() << " (" << revive.getHealPoints() << " hp) Amount in backpack : " << backpack.getRevives() << "\n";
	std::cout << "Type any other number to go back\n";

	std::cin >> input_Combat;
	if (input_Combat == 1 && backpack.getPotions() > 0)
	{
		std::cout << "Which party member would you like to heal?\n";
		std::cout << "1. Mage\n";
		std::cout << "2. Brawler\n";
		std::cout << "3. Tank\n";
		std::cout << "Type any other number to go back\n";
		std::cin >> input_Who;

		if (input_Who == 1 && mage.getAlive() == true)
		{
			//heal funktionen behöver en int och int funktionen behöver en string
			mage.heal(potion.getHealPoints());
			backpack.usePotion();
		}
		else if (input_Who == 2 && brawler.getAlive() == false)
		{
			brawler.heal(potion.getHealPoints());
			backpack.usePotion();
		}
		else if (input_Who == 3 && tank.getAlive() == false)
		{
			tank.heal(potion.getHealPoints());
			backpack.usePotion();
		}

	}
	else if (input_Combat == 2 && backpack.getRevives() > 0)
	{
		std::cout << "Which party member would you like to heal?\n";
		std::cout << "1. Mage\n";
		std::cout << "2. Brawler\n";
		std::cout << "3. Tank\n";
		std::cout << "Type any other number to go back\n";
		std::cin >> input_Who;

		if (input_Who == 1 && mage.getAlive() == false)
		{
			//heal funktionen behöver en int och int funktionen behöver en string
			mage.setAlive(true);
			mage.heal(revive.getHealPoints());
			backpack.useRevive();
		}
		else if (input_Who == 2 && brawler.getAlive() == false)
		{
			brawler.setAlive(true);
			brawler.heal(revive.getHealPoints());
			backpack.useRevive();
		}
		else if (input_Who == 3 && tank.getAlive() == false)
		{
			tank.setAlive(true);
			tank.heal(revive.getHealPoints());
			backpack.useRevive();
		}
	}
}