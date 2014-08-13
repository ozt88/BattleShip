#pragma once
#include "Enums.h"

class Board;
class Player;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void InitGame();
	void Update();
	void PrintResult( HitResult hitResult );
	void GameStart();

private:
	Player* m_Attacker;
	Player* m_Defender;
};

