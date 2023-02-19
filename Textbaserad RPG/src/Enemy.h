#pragma once
#include <iostream>

class Enemy
{
private:
	std::string name = "Idk";
	int maxHP = 10;
	int attackPower = 2;
	int magicPower = 2;
	int currentHP = maxHP;
	int XP = 5;
	int money = 5;

	bool exists = true;
	bool alive = true;

	std::string attack1Name = "Pauwnch";
	std::string attack2Name = "Telekenisis";

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
	int getMoney()
	{
		return money;
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
		if (currentHP <= 0)
		{
			currentHP = 0;
			alive = false;
		}
	}

	int attack1()
	{
		return attackPower;
	}
	int attack2()
	{
		return magicPower;
	}

	std::string getAttack1Name()
	{
		return attack1Name;
	}
	std::string getAttack2Name()
	{
		return attack2Name;
	}
};