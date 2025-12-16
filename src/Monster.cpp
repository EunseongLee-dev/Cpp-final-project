#include "Monster.h"
#include "Player.h"
#include "Item.h"
#include <random>
#include <memory>
#include <string>

Monster::Monster(std::string _name, int _hp, int _mp, int _atk)
	: Name(_name)
	, Hp(_hp)
	, MaxHp(_hp)
	, Mp(_mp)
	, MaxMp(_mp)
	, ATK(_atk)
{
	IsAlive = true;
}

std::string Monster::GetName() const
{
	return Name;
}

bool Monster::IsAlives() const
{
	return IsAlive;
}



void Monster::Monsterstatus() const
{
	std::cout << Name << " 의 스테이터스\n";
	std::cout << "현재 체력: " << Hp << " / " << "최대 체력: " << MaxHp << "\n";
	std::cout << "공격력: " << ATK << "\n\n";
}

void Monster::NormalAttack(Player& target)
{
	std::cout << "몬스터 " << "'" << Name << "'" << " 이(가) "
		<< "플레이어 " << "'" << target.GetName() << "'" << " 을 공격!"
		<< "데미지: " << ATK << "\n\n";

	target.TakeDamage(ATK);
}

void Monster::Skill(Player& target)
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
			std::cout << "몬스터의 마나 가 부족합니다. (마나: " << Mp << ")\n";
			std::cout << "일반 공격으로 전환\n\n";
			NormalAttack(target);
		}
		else
		{
			// 스킬 데미지 설정
			std::uniform_int_distribution<int> sk_1(20, 30);
			auto skill1_damage = sk_1(mt);

			Mp -= skill_1;

			std::cout << "몬스터 " << "'" << Name << "'" << " 이(가) "
				<< "플레이어 " << "'" << target.GetName() << "'" << " 을 공격! "
				<< "스킬_1 데미지: " << skill1_damage << "\n\n";

			target.TakeDamage(skill1_damage);
		}
		break;

	case 1:
		if (Mp < skill_2)
		{
			std::cout << "몬스터의 마나 가 부족합니다. (마나: " << Mp << ")\n\n";
			std::cout << "일반 공격으로 전환\n\n";
			NormalAttack(target);
		}
		else
		{
			std::uniform_int_distribution<int> sk_2(30, 40);
			auto skill2_damage = sk_2(mt);

			Mp -= skill_2;

			std::cout << "몬스터 " << "'" << Name << "'" << " 이(가) "
				<< "플레이어 " << "'" << target.GetName() << "'" << " 을 공격! "
				<< "스킬_2 데미지: " << skill2_damage << "\n\n";

			target.TakeDamage(skill2_damage);
		}
		break;

	}

}

void Monster::Attack(Player& target)
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

void Monster::TakeDamage(int damage)
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
		std::cout << "몬스터 " << "'" << Name << "'" << "의 남은 체력:" << Hp << " 사망\n\n";
		
	}
}

std::unique_ptr<Item> Monster::DropItem()
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	std::uniform_int_distribution<int> ch(0, 2);
	auto choice = ch(mt);

	switch (choice)
	{
	case 0:
		return std::make_unique<Consumable>("체력 포션", ConsumableType::Heal, 30);
		break;
		
	case 1:
		return std::make_unique<Consumable>("마나 포션", ConsumableType::Mana, 20);
		break;

	case 2:
		return std::make_unique<Consumable>("공격력 증가 포션", ConsumableType::Atk, 10);
		break;
	}
}

std::unique_ptr<Item> Monster::DropEq()
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	std::uniform_int_distribution<int> eq(0, 4);
	auto eqchoice = eq(mt);

	switch (eqchoice)
	{
	case 0:
		return std::make_unique<Weapon>("단검", 10);
		break;

	case 1:
		return std::make_unique<Weapon>("장검", 15);
		break;

	case 2:
		return std::make_unique<Armor>("가죽갑옷", 20);
		break;

	case 3:
		return std::make_unique<Armor>("철갑옷", 40);
		break;
	}
}
