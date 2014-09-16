#include "GameScene.h"
#include "BattleField.h"
#include "UI.h"
#include "EnemyUI.h"
#include "EndObject.h"

GameScene* GameScene::m_Instance = nullptr;

GameScene::GameScene()
{
	m_EnemyBattleFiled = new BattleField();
	m_MyBattleField = new BattleField();
	m_UI = new UI();
	m_EnemyUI = new EnemyUI();
	m_EndObject = new EndObject();

	this->AddChild( m_EnemyBattleFiled );
	this->AddChild( m_MyBattleField );
	this->AddChild( m_UI );
	this->AddChild( m_EnemyUI );
}


GameScene::~GameScene()
{
	m_MyBattleField->Clear();
	m_EnemyBattleFiled->Clear();
	m_UI->Clear();
	m_EnemyUI->Clear();
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
	for( auto child : m_ChildList )
	{
		child->Init();
	}

	m_EnemyBattleFiled->PosX( m_MyBattleField->PosX() + m_MyBattleField->Width() + m_MyBattleField->Width() / MAP_WIDTH );
}

void GameScene::MakeEndScene(const std::wstring& winner, int endTurn)
{
	m_EndObject->Init( winner , endTurn );
	this->AddChild( m_EndObject );
}

