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
	int getLevel()
	{
		return level;
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
		if(currentHP <= 0)
		{
			currentHP = 0;
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
		return magicPower*2;
	}
	int Attack3(std::string healName)
	{
		int healing = magicPower*2;
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
	//hur ska man accessa?

	//level 1 const variabler
	const std::string name = "Brawler";
	const int baseAttackPower = 20;
	const int baseMagicPower = 3;
	const int baseHP = 30;
	const int baseLevel = 1;
	const int baseXP = 0;
	const int baseLevelUpRequirement = 10;

	int attackPower = baseAttackPower;
	int magicPower = baseMagicPower;
	int maxHP = baseHP;
	int currentHP = maxHP;

	int level = 1;
	int XP = 0;
	int levelUpRequirement = 12;

	bool alive = true;

	const std::string attack1Name = "Knuckle Sandwich";
	const std::string attack2Name = "Card trick";
	const std::string attack3Name = "Headbutt";

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
	int getLevel()
	{
		return level;
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
		currentHP -= damage;
		if (currentHP <= 0)
		{
			currentHP = 0;
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
	int Attack3()
	{
		int selfHarm = attackPower;
		currentHP -= selfHarm;
		int damage = attackPower * 3;
		std::cout << name << " used " << attack3Name << " and took " << selfHarm << " HP and dealt " << damage;
		if (currentHP < 0)
		{
			currentHP = 0;
		}
		return damage;
	}

	void LevelUp()
	{
		if (XP >= levelUpRequirement)
		{
			std::cout << "You leveled up\n";
			//den tar bort xp:n som behövs för att levla upp
			XP -= levelUpRequirement;
			levelUpRequirement += levelUpRequirement;
			level++;

			maxHP += 5;
			attackPower += 5;
			magicPower += 1;
		}
	}
};

class Tank : public Character
{
private:
	//hur ska man accessa?

	//level 1 const variabler
	const std::string name = "Tank";
	const int baseAttackPower = 3;
	const int baseMagicPower = 1;
	const int baseHP = 150;
	const int baseLevel = 1;
	const int baseXP = 0;
	const int baseLevelUpRequirement = 5;

	int attackPower = baseAttackPower;
	int magicPower = baseMagicPower;
	int maxHP = baseHP;
	int currentHP = maxHP;

	int level = 1;
	int XP = 0;
	int levelUpRequirement = 17;

	bool alive = true;
	bool protecting = false;

	const std::string attack1Name = "Weak push";
	const std::string attack2Name = "Finger Gun";
	const std::string attack3Name = "Distraction";

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
	int getLevel()
	{
		return level;
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
	bool getProtecting()
	{
		return protecting;
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
		currentHP -= damage;
		if (currentHP <= 0)
		{
			currentHP = 0;
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
	void Attack3(bool Y_N)
	{
		protecting = Y_N;
	}

	void LevelUp()
	{
		if (XP >= levelUpRequirement)
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