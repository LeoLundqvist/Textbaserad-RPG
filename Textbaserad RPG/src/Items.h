#pragma once
class Potion
{
private:
	int healPoints = 75;
	int cost = 10;

public:
	int healPoints()
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
	int cost = 20;
public:
	int getCost()
	{
		return cost;
	}
};