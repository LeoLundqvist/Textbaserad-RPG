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
	int currentHP = baseHP;

	bool exists = true;
	bool alive = true;

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

	void setName(std::string newName)
	{
		name = newName;
	}
	void setBaseHP(int newBaseHP)
	{
		baseHP = newBaseHP;
	}
	void setBaseAttackPower(int newBaseAttackPower)
	{
		baseAttackPower = newBaseAttackPower;
	}
	void setBaseMagicPower(int newBaseMagicPower)
	{
		baseMagicPower = newBaseMagicPower;
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
			alive = false;
		}
	}

};