#pragma once
#include <iostream>

class Item
{
protected:
	std::string Name;
	std::string Type;
	int			Value;

public:
	Item(std::string _name, std::string _type, int _value);

	std::string GetName() const;

	std::string GetType() const;

	int GetValue() const;

	virtual bool IsEquipable() const;

	virtual int GetATKBonus() const;

	virtual int GetHpBonus() const;
};

class Weapon : public Item
{
private:
	int AtkUP;

public:
	Weapon(std::string _name, std::string _type, int _value);
	
	virtual bool IsEquipable() const override;

	virtual int GetATKBonus() const override;
	
};

class Armor : public Item
{
private:
	int HpUP;

public:
	Armor(std::string _name, std::string _type, int _value);

	virtual bool IsEquipable() const override;

	virtual int GetHpBonus() const override;
};