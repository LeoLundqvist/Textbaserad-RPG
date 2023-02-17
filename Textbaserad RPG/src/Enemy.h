#pragma once
#include <iostream>

class Enemy
{
private:
	//hur ska man accessa?
	std::string name = "Goblin";
	int baseHP = rand()% 10 + 1;
	int baseAttackPower = 2;
	int baseMagicPower = 10;
	int baseEvadeStat = 1;
	
	bool exists = true;
	bool alive = true;

	int currentHP = baseHP;

	std::string Attack1name = "Bite";
	std::string Attack2name = "Rock throw";
	std::string Attack3name = "Apple";
	std::string Attack4name = "High Five"; //buff

	//behöver override 

public:
	std::string getName()
	{
		return name;
	}

	int getBaseHP()
	{
		return baseHP;
	}

	int getCurrentHP()
	{
		return currentHP;
	}

	bool getAlive()
	{
		return alive;
	}

	bool getExists()
	{
		return alive;
	}
	void setExists(bool newExists)
	{
		exists=newExists;
	}

	void takeDamage(int damage)
	{
		currentHP -= damage;
		if (currentHP < 0)
		{
			alive = false;
		}
	}

};