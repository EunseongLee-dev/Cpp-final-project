#include "GameManager.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include <iostream>

GameManager::GameManager(Player* _player, std::vector<Monster*> _monster)
	: Playerr(_player)
	, Monsterr(_monster)
{
	isGameover = false;
	currentMonster = Monsterr[0];
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
	Monster* cur = Monsterr[0];

	Playerr->Attack(*cur);

	if (cur->IsAlives())
	{
		cur->Attack(*Playerr);
	}
}

void GameManager::CheckBattleResult()
{
	if (!Playerr->IsAlives())
	{
		isGameover = true;
		return;
	}

	if (!Monsterr[0]->IsAlives())
	{
		delete Monsterr[0];
		Monsterr.erase(Monsterr.begin());

		GiveRandomItem();

		SpawnMonster();
	}
}

void GameManager::SpawnMonster()
{
	Monster* newMonster = new Monster("고블린", 50, 40, 10);
	Monsterr.push_back(newMonster);
}

void GameManager::PrintStatus() const
{
	Playerr->Playerstatus();

	Monsterr[0]->Monsterstatus();
}

void GameManager::GiveRandomItem()
{
	Item* potion = new Item("체력 포션", "Heal", 30);
	Playerr->UseItem(potion);
	delete potion;
}


