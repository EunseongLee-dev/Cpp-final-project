#pragma once
#include <iostream>

class Player;

enum class ItemType
{
	None,
	Weapon,
	Armor,
	Consumable
};

class Item
{
protected:
	std::string Name;
	ItemType    Itemtype;
	int			Value;

public:
	Item(const std::string& _name, ItemType _type);

	std::string GetName() const;

	ItemType GetItemType() const;

	std::string GetItemTypeName() const;

	virtual int GetValue() const = 0;

	virtual bool IsEquipable() const;

	virtual int GetATKBonus() const;

	virtual int GetHpBonus() const;

	virtual void Use(Player& player) = 0;
};

class Weapon : public Item
{
private:
	int AtkUP;

public:
	Weapon(std::string _name, int _value);
	
	virtual bool IsEquipable() const override;

	virtual int GetATKBonus() const override;

	virtual void Use(Player& player) override;

	virtual int GetValue() const override;
	
};

class Armor : public Item
{
private:
	int HpUP;

public:
	Armor(std::string _name, int _value);

	virtual bool IsEquipable() const override;

	virtual int GetHpBonus() const override;

	virtual void Use(Player& player) override;

	virtual int GetValue() const override;
};

enum class ConsumableType
{
	None,
	Heal,
	Mana,
	Atk
};

class Consumable : public Item
{
protected:
	ConsumableType ctype;
	int value;

public:
	Consumable(const std::string& name, ConsumableType ctype, int value);

	virtual void Use(Player& player) override;

	virtual int GetValue() const override;

};