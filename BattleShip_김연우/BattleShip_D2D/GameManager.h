/************************************************************************/
/*
Class:		GameManager

설명:		베틀쉽 게임 내부의 전체 로직을 관리 담당하는 싱글톤 클래스
			시스템과 게임의 상태에 따라 알맞은 연산을 수행
			플레이어들이 게임로직에 맞게 자신의 역할을 수행하도록 관리
			게임 전체의 Scene객체가 프레임마다 업데이트하고 렌더링하도록 관리

추가기능:	네트워크 모드에서 네트워크 연결, 패킷관리, 종료를 수행
*/
/************************************************************************/

#pragma once
#include "Include.h"
#include "Enum.h"

class BattleField;
class UI;
class GameScene;
class Player;
class InteractiveObject;

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

	void				StartInit();
	void				SoloInit();
	void				SoloPlay();
	void				NetworkInit();
	void				NetworkReady();
	void				NetworkReset();
	void				NetworkPlay();

	void				SoloEnd(bool isWinner);
	void				NetworkEnd();
	void				Exit();

	GameScene*			GetGameScence(){return m_GameScene;}
	void				SetGameState(GameState state) { m_GameState = state; }
	GameState			GetGameState() {return m_GameState; }
	void				SetSystemState(SystemState state) {m_SystemState = state; }
	GameMode			GetGameMode() {return m_GameMode; }
	void				SetGameMode(GameMode mode) {m_GameMode = mode; }

	void				GetPacket();
	HitResult			AttackResultPassing( AttackResultTypes result );
	bool				Engage(Player* attacker, Player* defender);

private:
	GameManager();
	~GameManager();

	static GameManager*		m_Instance;

	Player*					m_Player1;
	Player*					m_Player2;
	Network*				m_Network;
	GameScene*				m_GameScene;

	GameState				m_GameState;		//게임의 상태
	SystemState				m_SystemState;		//시스템상태
	GameMode				m_GameMode;			//SOLO or NETWORK

	int						m_NumOfTurn;		//현재 턴수
	int						m_Total;			//한 싸이클의 총 턴수의 합
	int						m_GameCount;		//한 싸이클에서 진행된 게임의 수
	int						m_WinNum;			//한 싸이클에서 승리한 횟수
	std::wstring			m_MyName;			
};

