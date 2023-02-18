#pragma once
#include <iostream>

class Character
{
private:
	std::string species = "Human";

	//tänkte ha alla värden för karaktärerna här men då måstee man iallafall byta ut värderna för de olika klasserna

public:
	//finns bara för att jag ska visa att jag vet hur arv fungerar
	std::string getSpecies()
	{
		return species;
	}

};

class Mage : public Character
{
private:
	//hur ska man accessa?

	//level 1 const variabler
	const std::string name = "Mage";
	const int baseAttackPower = 3;
	const int baseMagicPower = 10;
	const int baseHP = 60;
	const int baseLevel = 1;
	const int baseXP = 0;
	const int baseLevelUpRequirement = 10;

	int attackPower = baseAttackPower;
    int magicPower = baseMagicPower;
	int maxHP = baseHP;
	int currentHP = maxHP;

	int level = 1;
	int XP = 0;
	int levelUpRequirement = 10;

	bool alive = true;
	
	const std::string attack1Name = "Staff slap";
	const std::string attack2Name = "Explosion";
	const std::string attack3Name = "Heal";
	const std::string attack4Name = "Insta Kill(for playtesting)";
	
public:
	//gets
	std::string getName()
	{
		return name;
	}
	int getAttackPower()
	{
		return attackPower;
	}
	int getMagicPower()
	{
		return magicPower;
	}
	int getMaxHP()
	{
		return maxHP;
	}
	int getCurrentHP()
	{
		return currentHP;
	}
	int getXP()
	{
		return XP;
	}
	int getLevelUpRequirement()
	{
		return levelUpRequirement - XP;
	}
	bool getAlive()
	{
		return alive;
	}
	std::string getAttack1Name()
	{
		return attack1Name;
	}
	std::string getAttack2Name()
	{
		return attack2Name;
	}
	std::string getAttack3Name()
	{
		return attack3Name;
	}
	std::string getAttack4Name()
	{
		return attack4Name;
	}

	//funktion som ändrar värdet på alla stats till level 1 statsen
	void startStats()
	{
		attackPower = baseAttackPower;
		magicPower = baseMagicPower;
		maxHP = baseHP;
		currentHP = maxHP;
		level = baseLevel;
		XP = baseXP;
		levelUpRequirement = baseLevelUpRequirement;
		alive = true;
	}

	//set
	void setAlive(bool newAlive)
	{
		alive = newAlive;
	}
	void addXP(int newXP)
	{
		XP += newXP;
	}

	void takeDamage(int damage)
	{
		currentHP-=damage;
		if(currentHP < 0)
		{
			alive = false;
		}

	}
	void heal(int healing)
	{
		currentHP += healing;

		if (currentHP > maxHP)
		{
			currentHP = maxHP;
		}
	}

	//moves
	int Attack1()
	{
		return attackPower;
	}
	int Attack2()
	{
		return magicPower;
	}
	int Attack3(std::string healName)
	{
		int healing = magicPower;
		std::cout << name << " used " << attack4Name << " and healed " << healName << " " << healing << " hp\n";
		return healing;
	}
	int Attack4()
	{
		return 999999;
	}

	void LevelUp()
	{
		if(XP >= levelUpRequirement)
		{
			std::cout << "You leveled up\n";
			//den tar bort xp:n som behövs för att levla upp
			XP -= levelUpRequirement;
			levelUpRequirement += levelUpRequirement;
			level++;

			maxHP += 50;
			attackPower += 1;
			magicPower += 2;
		}
	}
};

class Brawler : public Character
{
private:
	bool alive = false;

public:
	bool getAlive()
	{
		return alive;
	}
	
	void setAlive(bool newAlive)
	{
		alive = newAlive;
	}

};

class Tank : public Character
{
private:

	bool alive = false;

public:
	bool getAlive()
	{
		return alive;
	}

	void setAlive(bool newAlive)
	{
		alive = newAlive;
	}

};