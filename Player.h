#pragma once
#include <iostream>

class Monster;

class Player
{
private:
	std::string Name;
	int Hp;
	int MaxHp;
	int ATK;


public:

	Player(std::string _name, int _hp, int _atk);

	std::string GetName() const;

	void Attack(Monster& target);
	
	void Playerstatus() const;

	void TakeDamage(int damage);
};
