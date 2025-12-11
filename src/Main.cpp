#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "GameManager.h"
#include <vector>


int main()
{
	Player* playr = new Player("øµøı", 100, 60, 15);
	Monster* slime = new Monster("ΩΩ∂Û¿”", 40, 30, 10);

	std::vector<Monster*> monst;
	monst.push_back(slime);

	GameManager manager(playr, monst);
	manager.StartGame();

	delete playr;
	return 0;
}