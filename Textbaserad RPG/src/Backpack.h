#pragma once
class Backpack
#include <iostream>
{	
private:
	const int basemoney = 0;
	const int basepotions = 1;
	const int baseRevives = 1;

	int money = 0;
	int potions = 1;
	int revives = 1;

public:
	//gets
	int getMoney()
	{
		return money;
	}
	int getPotions()
	{
		return potions;
	}	
	int getRevives()
	{
		return revives;
	}

	void startInventory()
	{
		money = basemoney;
		potions = basepotions;
		revives = baseRevives;
	}
	void useRevive()
	{
		revives--;
	}
	void usePotion()
	{
		potions--;
	}
	void buy(int cost)
	{
		money -= cost;
	}
	void rewardMoney(int amount)
	{
		money += amount;
	}
};
