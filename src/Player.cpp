#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include <random>
#include <memory>
#include <string>

Player::Player(std::string _name, int _hp, int _mp, int _atk)
	: Name(_name)
	, Hp(_hp)
	, MaxHp(_hp)
	, BaseMaxHp(_hp)
	, Mp(_mp)
	, MaxMp(_mp)
	, ATK(_atk)
	, BaseATK(_atk)
{
	IsAlive = true;
	equippedWeapon.reset();
	equippedArmor.reset();
}


std::string Player::GetName() const
{
	return Name;
}

bool Player::IsAlives() const
{
	
	return IsAlive;
}



void Player::Playerstatus() const
{
	std::cout << Name << " 의 스테이터스\n";
	std::cout << "현재 체력: " << Hp << " / " << "최대 체력: " << MaxHp << "\n";
	std::cout << "현재 마나: " << Mp << " / " << "최대 마나: " << MaxMp << "\n";
	std::cout << "공격력: " << ATK << "\n\n";
}

void Player::NormalAttack(Monster& target)
{
	std::cout << "플레이어 " << "'" << Name << "'" << " 이(가) "
		<< "몬스터 " << "'" << target.GetName() << "'" << " 을 공격!"
		<< "데미지: " << ATK << "\n\n";

	target.TakeDamage(this->ATK);
}

void Player::Skill(Monster& target)
{
	// 랜덤 조건
	static std::random_device rd;
	static std::mt19937 mt(rd());
	
	// 랜덤 스킬 선택
	std::uniform_int_distribution<int> select(0, 1);
	auto skill_select = select(mt);

	// 스킬 마나 소모량
	std::uniform_int_distribution<int> sk_1(10, 20);
	auto skill_1 = sk_1(mt);
	std::uniform_int_distribution<int> sk_2(20, 30);
	auto skill_2 = sk_2(mt);

	switch (skill_select)
	{
	case 0:
		if (Mp < skill_1)
		{
			std::cout << "플레이어의 마나 가 부족합니다. (마나: " << Mp << ")\n";
			std::cout << "일반 공격으로 전환\n\n";
			NormalAttack(target);
		}
		else
		{
			// 스킬 데미지 설정
			std::uniform_int_distribution<int> sk_1(20, 30);
			auto skill1_damage = sk_1(mt);

			Mp -= skill_1;
		
			std::cout << "플레이어 " << "'" << Name << "'" << " 이(가) "
				<< "몬스터 " << "'" << target.GetName() << "'" << " 을 공격! "
				<< "공격 스킬_1 데미지: " << skill1_damage << "\n\n";

			target.TakeDamage(skill1_damage);
		}
		break;

	case 1:
		if (Mp < skill_2)
		{
			std::cout << "플레이어의 마나 가 부족합니다. (마나: " << Mp << ")\n\n";
			std::cout << "일반 공격으로 전환\n\n";
			NormalAttack(target);
		}
		else
		{
			std::uniform_int_distribution<int> sk_2(30, 40);
			auto skill2_damage = sk_2(mt);

			Mp -= skill_2;

			std::cout << "플레이어 " << "'" << Name << "'" << " 이(가) "
				<< "몬스터 " << "'" << target.GetName() << "'" << " 을 공격! "
				<< "공격 스킬_2 데미지: " << skill2_damage << "\n\n";

			target.TakeDamage(skill2_damage);
		}
		break;
	}
}

void Player::Attack(Monster& target)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	std::uniform_int_distribution<int> ch(0, 1);
	auto choice = ch(mt);

	switch (choice)
	{
	case 0:
		NormalAttack(target);
		break;

	case 1:
		Skill(target);
		break;
	}
}

void Player::TakeDamage(int damage)
{
	Hp -= damage;

	if (Hp <= 0)
	{
		Hp = 0;
		IsAlive = false;
	}

	std::cout << Name << "이(가) " << damage << " 데미지를 입었습니다! "
		<< "(Hp: " << Hp << " / " << MaxHp << ")\n\n";

	if (!IsAlive)
	{
		std::cout << "플레이어 " << "'" << Name << "'" << "의 남은 체력:" << Hp << " 사망\n\n";
	}
}

void Player::UseItem(Item* item)
{
	item->Use(*this);
}

void Player::AddItem(std::unique_ptr<Item> item)
{
	inventory.AddItem(std::move(item));
}

void Player::UseItemFromInventory(int index)
{
	if (index < 0 || index >= inventory.Count())
	{
		std::cout << "잘못된 인덱스입니다.\n\n";
		return;
	}
	
	Item* item = inventory.GetItem(index);
	UseItem(item);
	inventory.RemoveItem(index);
}

void Player::PrintInventory() const
{
	inventory.PrintInventory();
}

void Player::EquipItemFromInventory(int index)
{

	if (index < 0 || index >= inventory.Count())
	{
		std::cout << "잘못된 인덱스입니다.\n\n";
		return;
	}

	Item* item = inventory.GetItem(index);

	if (!item->IsEquipable())
	{
		std::cout << "착용 불가능한 아이템 입니다.\n\n";
		return;
	}

	if (auto weapon = dynamic_cast<Weapon*>(item))
	{
		if (!equippedWeapon)
		{
			EquipWeapon(index);
		}

		else if (equippedWeapon)
		{
			TryequipWeapon(weapon);
		}
	}
 
	if (auto armor = dynamic_cast<Armor*>(item))
	{
		if (!equippedArmor)
		{
			EquipArmor(index);
		}

		else if (equippedArmor)
		{
			TryequipArmor(armor);
		}
	}
}

void Player::EquippWeapon(int index)
{
	auto item = inventory.RemoveItem(index);

	if (auto weapon = dynamic_cast<Weapon*>(item.get()))
	{
		equippedWeapon = std::unique_ptr<Weapon>(static_cast<Weapon*>(item.release()));
	}
	equippedWeapon->Use(*this);
}

void Player::TryequipWeapon(Weapon* weapon)
{
	
	int menu;
	std::cout << "현재 착용 중인 무기가 있습니다.\n"
		<< "1. 착용 중인 장비를 교체한다: \n"
		<< "2. 이전 메뉴: ";
	std::cin >> menu;

	if (menu == 1)
	{
		ATK = BaseATK;
		inventory.AddItem(std::move(equippedWeapon));
		UseItem(weapon);
		return;
	}
	else if (menu == 2)
	{
		return;
	}
}

void Player::EquippArmor(int index)
{
	auto item = inventory.RemoveItem(index);

	if (auto weapon = dynamic_cast<Armor*>(item.get()))
	{
		equippedArmor = std::unique_ptr<Armor>(static_cast<Armor*>(item.release()));
	}
	equippedArmor->Use(*this);
}

void Player::TryequipArmor(Armor* armor)
{
	int menu;
	std::cout << "현재 착용 중인 무기가 있습니다.\n"
		<< "1. 착용 중인 장비를 교체한다: \n"
		<< "2. 이전 메뉴: ";
	std::cin >> menu;

	if (menu == 1)
	{
		MaxHp = BaseMaxHp;
		inventory.AddItem(std::move(equippedArmor));
		UseItem(armor);
		return;
	}
	else if (menu == 2)
	{
		return ;
	}
}

void Player::Heal(int amount)
{
	Hp += amount;
	if (Hp > MaxHp)
	{
		Hp = MaxHp;
	}
	std::cout << " (Hp: " << Hp << " / " << MaxHp << ")\n\n";
}

void Player::Mana(int amount)
{
	Mp += amount;
	if (Mp > MaxMp)
	{
		Mp = MaxMp;
	}
	std::cout << " (Mp: " << Mp << " / " << MaxHp << ")\n\n";
}

void Player::ATKUP(int amount)
{
	ATK += amount;
	std::cout << " (ATK: " << ATK << ")\n\n";
}

void Player::EquipWeapon(int atkbonus)
{
	ATK += atkbonus;
	std::cout << " (ATK: " << ATK << ")\n\n";
}

void Player::EquipArmor(int hpbonus)
{
	MaxHp += hpbonus;
	std::cout << " (Hp: " << Hp << " / " << MaxHp << ")\n\n";
}




