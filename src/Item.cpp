#include "Item.h"
#include "Player.h"

Item::Item(const std::string& _name, ItemType _type)
	:Name(_name)
	,Itemtype(_type)
	,Value(0)
{
}

std::string Item::GetName() const
{
	return Name;
}

ItemType Item::GetItemType() const
{
	return Itemtype;
}

std::string Item::GetItemTypeName() const
{
	switch (Itemtype)
	{
	case ItemType::Weapon:
		return "Weapon";
		break;

	case ItemType::Armor:
		return "Armor";
		break;

	case ItemType::Consumable:
		return "Consumable";
		break;

	default:
		return "Unknown";
		break;
	}
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

void Item::Use(Player& player)
{
}


Weapon::Weapon(std::string _name, int _value)
	:Item(_name, ItemType::Weapon)
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

void Weapon::Use(Player& player)
{
	std::cout << "플레이어 " << player.GetName() << "이 '" << Name << "'을 착용했습니다.\n"
		<< "공격력 +" << AtkUP;
	player.EquipWeapon(AtkUP);
}

int Weapon::GetValue() const
{
	return AtkUP;
}

Armor::Armor(std::string _name, int _value)
	:Item(_name, ItemType::Armor)
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

void Armor::Use(Player& player)
{
	std::cout << "플레이어 " << player.GetName() << "이 '" << Name << "'을 착용했습니다.\n"
		<< "MaxHp +" << HpUP;
	player.EquipArmor(HpUP);
}

int Armor::GetValue() const
{
	return HpUP;
}

Consumable::Consumable(const std::string& name, ConsumableType ctype, int value)
	:Item(name, ItemType::Consumable)
	, ctype(ctype)
	, value(value)
{
}

void Consumable::Use(Player& player)
{
	switch (ctype)
	{
	case ConsumableType::Heal:
		std::cout << "플레이어 " << player.GetName() << "이 '" << Name << "'을 사용했습니다.\n"
			<< "Hp +" << value;
		player.Heal(value);
		break;

	case ConsumableType::Mana:
		std::cout << "플레이어 " << player.GetName() << "이 '" << Name << "'을 사용했습니다.\n"
			<< "Mp +" << value;
		player.Mana(value);
		break;

	case ConsumableType::Atk:
		std::cout << "플레이어 " << player.GetName() << "이 '" << Name << "'을 사용했습니다.\n"
			<< "공격력 +" << value;
		player.ATKUP(value);
		break;
	}
}

int Consumable::GetValue() const
{
	return value;
}
