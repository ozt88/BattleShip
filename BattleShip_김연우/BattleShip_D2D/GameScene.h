/************************************************************************/
/*
Class:		GameScene

����:		��Ʋ�� ���� ������ ��ü D2D������Ʈ���� �����ϴ� �̱��� Ŭ����
			D2DScene�� ��ӹ޴� �ֻ��� D2DObject

�߰����:	���� ��庰�� �׸��� ���� ����, ����
*/
/************************************************************************/

#pragma once
#include "D2DScene.h"

class BattleField;
class UI;
class InteractiveObject;
class EnemyUI;
class GameScene :
	public D2DScene
{
public:
	static GameScene*		GetInstance();
	static void				ReleaseInstance();

	void					Init();

	void					StartScene();
	void					BattleScene();
	void					GameEndScene(bool isWin, int winNum, float turnAvg);
	void					GameOverScene(int winNum , float turnAvg);

	void					SceneClear();

	BattleField*			GetMyBattleField(){return m_MyBattleField;}
	BattleField*			GetEnemyBattleFiled() {return m_EnemyBattleField; }
	UI*						GetUI(){return m_UI;}
	InteractiveObject*		GetEndObject(){ return m_InteractiveObject; }
	EnemyUI*				GetEnemyUI(){return m_EnemyUI;}
	
private:
	GameScene();
	~GameScene();

	static GameScene*		m_Instance;
	BattleField*			m_MyBattleField;		//������ ������ ǥ��
	BattleField*			m_EnemyBattleField;		//���� ������ ǥ��
	UI*						m_UI;					//������ ��Ȳ�� ǥ��
	EnemyUI*				m_EnemyUI;				//���� ��Ȳ�� ǥ��
	InteractiveObject*		m_InteractiveObject;	//������ ��ǲ�� �޴� ������Ʈ
};

