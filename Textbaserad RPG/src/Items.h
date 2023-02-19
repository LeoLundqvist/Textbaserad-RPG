#pragma once
#include <iostream>

class Potion
{
private:
	std::string name = "Potion";
	int healPoints = 75;
	int cost = 10;

public:
	std::string getName()
	{
		return name;
	}
	int getHealPoints()
	{
		return healPoints;
	}
	int getCost()
	{
		return cost;
	}
};

class Revive : public Potion
{
private:
	std::string name = "Revive";
	int cost = 20;
public:
	int getCost()
	{
		return cost;
	}
};

