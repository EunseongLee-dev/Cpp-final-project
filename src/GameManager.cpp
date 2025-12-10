#include "GameManager.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

GameManager::GameManager(Player* _player, std::vector<Monster*> _monster)
	: Playerr(_player)
	, Monsterr(_monster)
{
	isGameover = true;
	turnCount = 0;
}

void GameManager::StartGame()
{
	PrintStatus();

	GameLoop();


}

void GameManager::GameLoop()
{

	while (!isGameover)
	{
		CheckBattleResult();
		if (isGameover)
		{
			break;
		}
		ProcessTurn();
		
	}
}

void GameManager::ProcessTurn()
{
	for(auto it : Monsterr)
	{
		Playerr->Attack(*it);
	}

	for (auto it : Monsterr)
	{
		it->Attack(*Playerr);
	}
}

void GameManager::CheckBattleResult()
{
	if (!Playerr->IsAlives())
	{
		isGameover = false;
		return;
	}

	bool anyMonsterAlive = true;

	for (auto it : Monsterr)
	{
		if (it->IsAlives())
		{
			anyMonsterAlive = false;
			break;
		}
	}

	if (!anyMonsterAlive)
	{
		isGameover = true;
	}
}

void GameManager::SpawnMonster()
{

}

void GameManager::PrintStatus() const
{
	Playerr->Playerstatus();

	for (auto it : Monsterr)
	{
		it->Monsterstatus();
	}
}


