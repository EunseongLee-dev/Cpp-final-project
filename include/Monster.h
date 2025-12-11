#pragma once
#include <iostream>

class Player;

class Item;

class Monster
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

	Monster(std::string _name, int _hp, int _mp, int _atk);

	std::string GetName() const;

	bool IsAlives() const;

	void Monsterstatus() const;

	void NormalAttack(Player& target);

	void Skill(Player& target);

	void Attack(Player& target);

	void TakeDamage(int damage);

	void DropItem(Item* item);

};