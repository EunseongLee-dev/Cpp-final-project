#include "Item.h"

Item::Item(std::string _name, std::string _type, int _value)
	:Name(_name)
	,Type(_type)
	,Value(_value)
{
}

std::string Item::GetName() const
{
	return Name;
}

std::string Item::GetType() const
{
	return Type;
}

int Item::GetValue() const
{
	return Value;
}

bool Item::IsEquipable() const
{
	return 0;
}

int Item::GetATKBonus() const
{
	return 0;
}

int Item::GetHpBonus() const
{
	return 0;
}


Weapon::Weapon(std::string _name, std::string _type, int _value)
	:Item(_name, _type, _value)
	, AtkUP(_value)
{
}

bool Weapon::IsEquipable() const
{
	return true;
}

int Weapon::GetATKBonus() const
{
	return AtkUP;
}

Armor::Armor(std::string _name, std::string _type, int _value)
	:Item(_name, _type, _value)
	, HpUP(_value)
{
}

bool Armor::IsEquipable() const
{
	return true;
}

int Armor::GetHpBonus() const
{
	return HpUP;
}
