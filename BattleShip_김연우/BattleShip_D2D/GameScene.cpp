#include "GameScene.h"
#include "BattleField.h"
#include "UI.h"
#include "EndObject.h"

GameScene* GameScene::m_Instance = nullptr;

GameScene::GameScene()
{
	m_EnemyBattleFiled = new BattleField();
	m_MyBattleField = new BattleField();
	m_UI = new UI();
	m_EndObject = new EndObject();

	this->AddChild( m_EnemyBattleFiled );
	this->AddChild( m_MyBattleField );
	this->AddChild( m_UI );
}


GameScene::~GameScene()
{
	m_MyBattleField->Clear();
	m_EnemyBattleFiled->Clear();
	m_UI->Clear();
	m_EndObject->Clear();
}

GameScene* GameScene::GetInstance()
{
	if( m_Instance == nullptr )
	{
		m_Instance = new GameScene();
	}
	return m_Instance;
}

void GameScene::ReleaseInstance()
{
	if( m_Instance != nullptr )
	{
		SafeDelete(m_Instance);
	}
}

void GameScene::Init()
{
	m_MyBattleField->Init();
	m_EnemyBattleFiled->Init();
	m_UI->Init();
	m_EnemyBattleFiled->PosX( m_MyBattleField->PosX() + m_MyBattleField->Width() + m_MyBattleField->Width() / MAP_WIDTH );
}

void GameScene::MakeEndScene(const std::wstring& winner, int endTurn)
{
	m_EndObject->Init( winner , endTurn );
	this->AddChild( m_EndObject );
}

