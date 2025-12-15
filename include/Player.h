#pragma once
#include "Inventory.h"
#include "Item.h"

class Monster;

class Player
{
private:
	std::string Name;
	int Hp;
	int MaxHp;
	int BaseMaxHp;
	int Mp;
	int MaxMp;
	int ATK;
	int BaseATK;
	bool IsAlive;
	Inventory inventory;
	std::unique_ptr<Weapon> equippedWeapon;
	std::unique_ptr<Armor> equippedArmor;

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

	void AddItem(std::unique_ptr<Item> item);

	void UseItemFromInventory(int index);

	void PrintInventory() const;

	void EquipItemFromInventory(int index);
	
	void UnequipWeapon();

	void UnequipArmor();
};
