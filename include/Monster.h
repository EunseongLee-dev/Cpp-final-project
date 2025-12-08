#pragma once
#include <iostream>

class Player;

class Monster
{
private:
	std::string Name;
	int Hp;
	int MaxHp;
	int ATK;

public:

	Monster(std::string _name, int _hp, int _atk);

	std::string GetName() const;

	void Attack(Player& target);

	void Monsterstatus() const;

	void TakeDamage(int damage);

};
