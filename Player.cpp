#include "Player.h"
#include "Monster.h"

Player::Player(std::string _name, int _hp, int _atk)
	: Name(_name)
	, Hp(_hp)
	, MaxHp(_hp)
	, ATK(_atk)
	// 구현 설명:
	// _hp를 멤버 Hp, MaxHp에 둘다 생성자로 할당한 이유는
	// Maxhp에만 생성자로 넣으면 결국 멤버 Hp는 null값 이므로 생성 당시에는
	// Maxhp,Hp 멤버값이 무조건 동일한 상황밖에 없으므로 매개변수로 받은 _hp를 
	// 각각 멤버에 둘다 할당함
{
}

std::string Player::GetName() const
{
	return Name;
}

void Player::Attack(Monster& target)
{
	target.TakeDamage(this->ATK); // this-> 작성 안해도 가능 
	std::cout << "플레이어 " << "'" << Name << "'" << " 이(가) "
		<< "몬스터 " << "'" << target.GetName() << "'" << " 을 공격!"
		<< "데미지: " << ATK << "\n";

}



void Player::Playerstatus() const
{
	std::cout << Name << " 의 스테이터스\n";
	std::cout << "현재 체력: " << Hp << " / " << "최대 체력: " << MaxHp << "\n";
	std::cout << "공격력: " << ATK << "\n";
}

void Player::TakeDamage(int damage)
{
	Hp -= damage;
	if (Hp < 0)
	{
		Hp = 0;
		std::cout << "플레이어 " << "'" << Name << "'" << "의 남은 체력:" << Hp << " 사망\n";
	}
	std::cout << "현재 " << Name << "의 남은 체력: " << Hp << "\n";
}
