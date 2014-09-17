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
	BattleField*			GetEnemyBattleFiled() {return m_EnemyBattleFiled; }
	UI*						GetUI(){return m_UI;}
	InteractiveObject*		GetEndObject(){ return m_InteractiveObject; }
	EnemyUI*				GetEnemyUI(){return m_EnemyUI;}
	
	void					Init();
private:
	GameScene();
	~GameScene();

	static GameScene*		m_Instance;
	BattleField*			m_MyBattleField;
	BattleField*			m_EnemyBattleFiled;
	UI*						m_UI;
	EnemyUI*				m_EnemyUI;
	InteractiveObject*		m_InteractiveObject;
};

