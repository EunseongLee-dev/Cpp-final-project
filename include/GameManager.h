#pragma once
#include <vector>

class Player;
class Monster;

class GameManager
{
private:
	Player* Playerr;
	std::vector<Monster*> Monsterr;
	bool isGameover;
	Monster* currentMonster;

public:
	GameManager(Player* _player, std::vector<Monster*> _monster);

	void StartGame();

	void GameLoop();

	void ProcessTurn();

	void CheckBattleResult();

	void SpawnMonster();

	void PrintStatus() const;

	void GiveRandomItem();

	

};