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
	void				UpdateInNetwork();
	void				End(const std::wstring& winner);
	void				End();
	void				Exit();
	void				SetGameState(GameState state) { m_GameState = state; }
	GameState			GetGameState() {return m_GameState; }
	void				GetPacket();
	HitResult			AttackResultPassing( AttackResultTypes result );

private:
	GameManager();
	~GameManager();

	static GameManager*		m_Instance;
	Player*					m_Player1;
	Player*					m_Player2;
	int						m_NumOfTurn;
	int						m_Total;
	int						m_GameCount;
	GameScene*				m_GameScene;
	GameState				m_GameState;


	Network*				m_Network;
	std::wstring			m_MyName;

};

