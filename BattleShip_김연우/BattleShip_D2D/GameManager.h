#pragma once
#include "Include.h"

class BattleField;
class UI;
class GameScene;
class Player;

class GameManager
{
public:
	GameManager();
	~GameManager();
	
	void Init();
	void Render();
	void Run();
	void Update();

private:
	Player*			m_Player1;
	Player*			m_Player2;
	BattleField*	m_BattleField;
	UI*				m_UI;
	GameScene*		m_GameScene;
};


// 
// #pragma once
// #include "Include.h"
// 
// class Player;
// 
// class GameManager
// {
// public:
// 	GameManager();
// 	~GameManager();
// 
// 	void InitGame();
// 	void Update();
// 	void PrintResult( HitResult hitResult );
// 	void GameStart();
// 
// private:
// 	Player* m_Attacker;
// 	Player* m_Defender;
// 	int		m_NumOfTurn;
// };
// 
