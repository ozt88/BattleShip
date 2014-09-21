/************************************************************************/
/*
Class:		GameScene

설명:		베틀쉽 게임 내부의 전체 D2D오브젝트들을 관리하는 싱글톤 클래스
			D2DScene을 상속받는 최상위 D2DObject

추가기능:	게임 모드별로 그리는 씬을 변경, 관리
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
	
	void					Init();
private:
	GameScene();
	~GameScene();

	static GameScene*		m_Instance;
	BattleField*			m_MyBattleField;		//유저의 전장을 표시
	BattleField*			m_EnemyBattleField;		//적의 전장을 표시
	UI*						m_UI;					//유저의 상황을 표시
	EnemyUI*				m_EnemyUI;				//적의 상황을 표시
	InteractiveObject*		m_InteractiveObject;	//유저의 인풋을 받는 오브젝트
};

