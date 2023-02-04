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
	std::string name = "Mage";
	int baseHP = 2000;
	int baseAttackPower = 2;
	int baseMagicPower = 10;
	int baseEvadeStat = 1;
	std::string Attack1name = "Staff slap";
	std::string Attack2name = "Explosion";
	std::string Attack3name = "Heal";
	std::string Attack4name = "Insta Kill(for playtesting)";

	//beh�ver override 

public:
	std::string getName()
	{
		return name;
	}
	int getBaseHP()
	{
		return baseHP;
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