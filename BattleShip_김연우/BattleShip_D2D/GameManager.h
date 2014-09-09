#pragma once
#include "Include.h"
#include "Enum.h"

class BattleField;
class UI;
class GameScene;
class Player;
class EndObject;
class GameManager
{
public:
	static GameManager*	GetInstance();
	static void			ReleaseInstance();

	void				Init();
	void				Reset();
	void				Render();
	void				Run();
	void				Update();
	void				End(std::wstring winner);
	void				SetGameState(GameState state) { m_GameState = state; }
	GameState			GetGameState() {return m_GameState; }

private:
	GameManager();
	~GameManager();

	static GameManager*		m_Instance;
	Player*					m_Player1;
	Player*					m_Player2;
	int						m_NumOfTurn;

	BattleField*			m_MyBattleField;
	BattleField*			m_EnemyBattleFiled;
	UI*						m_UI;
	EndObject*				m_EndObject;
	GameScene*				m_GameScene;
	GameState				m_GameState;
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
