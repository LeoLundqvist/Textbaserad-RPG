#pragma once
#include <iostream>


class Enemy
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

class Goblin : public Enemy
{
private:
	//hur ska man accessa?
	std::string name = "Goblin";
	int baseHP = rand()% 10 + 1;
	int baseAttackPower = 2;
	int baseMagicPower = 10;
	int baseEvadeStat = 1;
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
};