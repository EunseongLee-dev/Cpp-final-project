#include "Monster.h"
#include "Player.h"

Monster::Monster(std::string _name, int _hp, int _atk)
	:Name(_name)
	,Hp(_hp)
	,MaxHp(_hp)
	,ATK(_atk)
{
}

std::string Monster::GetName() const
{
	return Name;
}


void Monster::Attack(Player& target)
{
	target.TakeDamage(ATK);
	std::cout << "몬스터 " << "'" << Name << "'" << " 이(가) "
		<< "플레이어 " << "'" << target.GetName() << "'" << " 을 공격!"
		<< "데미지: " << ATK << "\n";
}

void Monster::Monsterstatus() const
{
	std::cout << Name << " 의 스테이터스\n";
	std::cout << "현재 체력: " << Hp << " / " << "최대 체력: " << MaxHp << "\n";
	std::cout << "공격력: " << ATK << "\n";
}

void Monster::TakeDamage(int damage)
{
	Hp -= damage;
	if (Hp < 0)
	{
		Hp = 0;
		std::cout << "몬스터 " << "'" << Name << "'" << "의 남은 체력:" << Hp << " 사망\n";
	}
	std::cout << "현재 " << Name << "의 남은 체력: " << Hp << "\n";
}
