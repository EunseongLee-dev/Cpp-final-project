#include "GameManager.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include <iostream>
#include <memory>
#include <string>
#include <random>

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
	int menu;

	std::cout << "전투 메뉴\n";
	std::cout << "1.공격: \n" << "2.인벤토리 사용: \n";
	std::cin >> menu;
	
	if (menu > 2)
	{
		std::cout << "잘못된 메뉴번호 입니다.\n";
	}

	if (menu == 1)
	{
		Playerr->Attack(*cur);

		if (cur->IsAlives())
		{
			cur->Attack(*Playerr);
		}
	}

	else if (menu == 2)
	{
		Playerr->PrintInventory();
		int menu;
		std::cout << "1.아이템 사용: \n" << "2.인벤토리 사용 취소(공격 전환): \n";
		std::cin >> menu;

		if (menu == 1)
		{
			int item;
			std::cout << "\n사용 할 아이템 번호: ";
			std::cin >> item;
			Playerr->UseItemFromInventory(item);
		}
		else if (menu == 2)
		{
			Playerr->Attack(*cur);

			if (cur->IsAlives())
			{
				cur->Attack(*Playerr);
			}
		}


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
		GiveRandomItem();

		delete Monsterr[0];
		Monsterr.erase(Monsterr.begin());

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
	auto drop = Monsterr[0]->DropItem();

	static std::random_device rd;
	static std::mt19937 mt(rd());

	std::uniform_int_distribution<int> dist(0, 1);

	if (dist(mt) == 0)
	{
		std::cout << drop->GetName() << "아이템을 드랍했습니다.\n\n";
		Playerr->AddItem(std::move(drop));
	}
	else if (dist(mt) == 1)
	{
		std::cout << "획득한 아이템이 없습니다.\n\n";
	}

}


