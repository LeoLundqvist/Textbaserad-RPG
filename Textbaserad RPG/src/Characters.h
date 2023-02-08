#pragma once
#include <iostream>

class Character
{
private:
	std::string name = "hello";
	int baseHP = 0;
	int baseAttackPower = 0;
	int baseMagicPower = 0;
	int baseEvadeStat = 0;
	std::string Attack1name = "";
	std::string Attack2name = "";
	std::string Attack3name = "";
	std::string Attack4name = "";

public:

};

class Mage : public Character
{
private:
	//hur ska man accessa?

	//const variabler
	const std::string name = "Mage";
	int baseHP = 200;
	int baseAttackPower = 3;
	int baseMagicPower = 10;
	int baseEvadeStat = 1;
	int level = 1;
	bool alive = true;

	int levelUpRequirement = 10;
	int levelUpXP = 0;

	int currentHP = baseHP;

	std::string Attack1name = "Staff slap";
	std::string Attack2name = "Explosion";
	std::string Attack3name = "Heal";
	std::string Attack4name = "Insta Kill(for playtesting)";
	

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

	std::string getAttack1Name()
	{
		return Attack1name;
	}

	std::string getAttack2Name()
	{
		return Attack2name;
	}

	std::string getAttack3Name()
	{
		return Attack3name;
	}

	std::string getAttack4Name()
	{
		return Attack4name;
	}

	void takeDamage(int damage)
	{
		currentHP-=damage;
		if(currentHP < 0)
		{
			alive = false;
		}

	}

	int Attack1()
	{
		std::cout << "Player used " << Attack1name << "\n";		
		//damage räknas ut med vanliga attack + en random från 0 - 3 och sen tar jag minus
		//då blir damagen mellan baseAttackpower-1 och baseAttackpower+2
		int damage = baseAttackPower + (rand() % 4) - 1;

		return damage;

	}
	int Attack2()
	{
		std::cout << "Player used " << Attack2name << "\n";

	}

	int Attack4()
	{
		std::cout << "Player used " << Attack4name << "\n";
		currentHP += baseMagicPower;

		if(currentHP > baseHP)
		{
			currentHP = baseHP;
		}

	}

	void LevelUp()
	{
		levelUpRequirement += levelUpRequirement;
		levelUpXP -= levelUpRequirement;
		level++;

		baseHP += 50;
		baseAttackPower += 1;
		baseMagicPower += 2;
		baseEvadeStat++;

	}
};

class Brawler : public Character
{
public:

};

class Tank : public Character
{
public:


};