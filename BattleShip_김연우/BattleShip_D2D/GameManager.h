/************************************************************************/
/*
Class:		GameManager

����:		��Ʋ�� ���� ������ ��ü ������ ���� ����ϴ� �̱��� Ŭ����
			�ý��۰� ������ ���¿� ���� �˸��� ������ ����
			�÷��̾���� ���ӷ����� �°� �ڽ��� ������ �����ϵ��� ����
			���� ��ü�� Scene��ü�� �����Ӹ��� ������Ʈ�ϰ� �������ϵ��� ����

�߰����:	��Ʈ��ũ ��忡�� ��Ʈ��ũ ����, ��Ŷ����, ���Ḧ ����
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

	void				End(bool isWinner);
	void				End();
	void				Exit();
	void				SetGameState(GameState state) { m_GameState = state; }
	GameState			GetGameState() {return m_GameState; }
	void				SetSystemState(SystemState state) {m_SystemState = state; }
	GameMode			GetGameMode() {return m_GameMode; }
	void				SetGameMode(GameMode mode) {m_GameMode = mode; }

	void				GetPacket();
	HitResult			AttackResultPassing( AttackResultTypes result );

private:
	GameManager();
	~GameManager();

	static GameManager*		m_Instance;

	Player*					m_Player1;
	Player*					m_Player2;
	Network*				m_Network;
	GameScene*				m_GameScene;

	GameState				m_GameState;		//������ ����
	SystemState				m_SystemState;		//�ý��ۻ���
	GameMode				m_GameMode;			//SOLO or NETWORK

	int						m_NumOfTurn;		//���� �ϼ�
	int						m_Total;			//�� ����Ŭ�� �� �ϼ��� ��
	int						m_GameCount;		//�� ����Ŭ���� ����� ������ ��
	int						m_WinNum;			//�� ����Ŭ���� �¸��� Ƚ��
	std::wstring			m_MyName;			
};

