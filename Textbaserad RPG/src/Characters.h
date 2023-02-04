#pragma once
#include <iostream>

class Character
{
private:
	std::string name = "";
	int baseHP = 0;
	int baseAttackPower = 0;
	int baseMagicPower = 0;
	int baseEvadeStat = 0;

public:

};

class Mage : public Character
{
private:
	std::string name = "Mage";
	int baseHP = 20;
	int baseAttackPower = 2;
	int baseMagicPower = 10;
	int baseEvadeStat = 1;
	//behöver override 

public:

};

class Brawler
{
public:


};

class Tank
{
public:


};