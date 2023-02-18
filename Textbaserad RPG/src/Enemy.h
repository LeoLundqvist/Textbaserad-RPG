#pragma once
#include <iostream>

class Enemy
{
private:
	//hur ska man accessa?
	std::string name = "Goblin";
	int maxHP = 10;
	int attackPower = 2;
	int magicPower = 10;
	int currentHP = maxHP;
	int XP = 5;

	bool exists = true;
	bool alive = true;

	std::string Attack1name = "Hit";
	std::string Attack2name = "Telekenisis";
	std::string Attack3name = "A really tasty snack";
	std::string Attack4name = "High Five"; //buff

	//behöver override 

public:
	std::string getName()
	{
		return name;
	}
	int getMaxHP()
	{
		return maxHP;
	}
	bool getAlive()
	{
		return alive;
	}
	bool getExists()
	{
		return alive;
	}
	int getCurrentHP()
	{
		return currentHP;
	}
	int getXP()
	{
		return XP;
	}

	void setName(std::string newName)
	{
		name = newName;
	}
	void setBaseHP(int newBaseHP)
	{
		maxHP = newBaseHP;
	}
	void setBaseAttackPower(int newBaseAttackPower)
	{
		attackPower = newBaseAttackPower;
	}
	void setBaseMagicPower(int newBaseMagicPower)
	{
		magicPower = newBaseMagicPower;
	}
	void setCurrentHP(int newCurrentHP)
	{
		currentHP = newCurrentHP;
	}
	void setExists(bool newExists)
	{
		exists=newExists;
	}
	void setAlive(bool newAlive)
	{
		alive = newAlive;
	}

	void takeDamage(int damage)
	{
		currentHP -= damage;
		if (currentHP < 0)
		{
			currentHP = 0;
			alive = false;
		}
	}

	int attack1()
	{
		return attackPower;
	}

};