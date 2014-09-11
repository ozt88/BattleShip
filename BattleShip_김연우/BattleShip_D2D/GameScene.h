#pragma once
#include "D2DScene.h"

class BattleField;
class UI;
class EndObject;
class GameScene :
	public D2DScene
{
public:
	static GameScene*		GetInstance();
	static void				ReleaseInstance();

	BattleField*			GetMyBattleField(){return m_MyBattleField;}
	BattleField*			GetEnemyBattleFiled() {return m_EnemyBattleFiled; }
	UI*						GetUI(){return m_UI;}
	EndObject*				GetEndObject(){ return m_EndObject; }
	
	void					Init();
	void					MakeEndScene(const std::wstring& winner, int endTurn);

private:
	GameScene();
	~GameScene();

	static GameScene*		m_Instance;
	BattleField*			m_MyBattleField;
	BattleField*			m_EnemyBattleFiled;
	UI*						m_UI;
	EndObject*				m_EndObject;
};

