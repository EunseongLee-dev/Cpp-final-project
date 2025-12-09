#include <iostream>
#include "Player.h"
#include "Monster.h"


int main()
{
	Player Play1("용사", 80, 50, 10);
	Monster Mons1("슬라임", 60, 40, 10);

	Play1.Playerstatus();
	Mons1.Monsterstatus();
	Play1.Attack(Mons1);
	Mons1.Attack(Play1);
	Play1.Attack(Mons1);
	Mons1.Attack(Play1);
	Play1.Attack(Mons1);
	Mons1.Attack(Play1);
	Play1.Playerstatus();
	Mons1.Monsterstatus();

	return 0;
}