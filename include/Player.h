#pragma once
#include <iostream>

class Monster;

class Item;

class Player
{
private:
	std::string Name;
	int Hp;
	int MaxHp;
	int Mp;
	int MaxMp;
	int ATK;
	bool IsAlive;

public:

	Player(std::string _name, int _hp, int _mp, int _atk);

	std::string GetName() const;

	bool IsAlives() const;
	
	void Playerstatus() const;

	void NormalAttack(Monster& target);

	void Skill(Monster& target);

	void Attack(Monster& target);

	void TakeDamage(int damage);

	void UseItem(Item* item);

	
};
