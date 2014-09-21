#include "GameScene.h"
#include "BattleField.h"
#include "UI.h"
#include "EnemyUI.h"
#include "InteractiveObject.h"

GameScene* GameScene::m_Instance = nullptr;

GameScene::GameScene()
{
	m_EnemyBattleField = new BattleField();
	m_MyBattleField = new BattleField();
	m_UI = new UI();
	m_EnemyUI = new EnemyUI();
	m_InteractiveObject = new InteractiveObject();
}

GameScene::~GameScene()
{
	m_MyBattleField->Clear();
	m_EnemyBattleField->Clear();
	m_UI->Clear();
	m_EnemyUI->Clear();
	m_InteractiveObject->Clear();
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
	m_InteractiveObject->Init();
	m_EnemyBattleField->Init();
	m_EnemyUI->Init();
	m_MyBattleField->Init();
	m_UI->Init();
	//적의 전장을 표시하는 구역은 유저의 전장을 표시하는 구역에서 x축으로 이동시켜야한다.
	m_EnemyBattleField->PosX( 
		m_MyBattleField->PosX() + m_MyBattleField->Width() + 
		m_MyBattleField->Width() / MAP_WIDTH );
}

void GameScene::GameEndScene( bool isWin , int winNum , float turnAvg )
{
	m_InteractiveObject->EndObjectInit();
	std::wstring winner = ( isWin ) ? L"WIN" : L"LOSE";
	m_InteractiveObject->SetMessage( winner + L" in turn of " + std::to_wstring( (int)turnAvg ) );
	this->AddChild( m_InteractiveObject );
}

void GameScene::GameOverScene( int winNum , float turnAvg )
{
	SceneClear();
	m_InteractiveObject->StartObjectInit();
	m_InteractiveObject->SetMessage( std::to_wstring(winNum) + L" wins & avg: "  + std::to_wstring( turnAvg ) );
	this->AddChild( m_InteractiveObject );
}

void GameScene::StartScene()
{
	SceneClear();
	m_InteractiveObject->StartObjectInit();
	this->AddChild( m_InteractiveObject );
}

void GameScene::BattleScene()
{
	SceneClear();
	this->AddChild( m_EnemyBattleField );
	this->AddChild( m_MyBattleField );
	this->AddChild( m_UI );
	this->AddChild( m_EnemyUI );
}

void GameScene::SceneClear()
{
	for( auto childIter = m_ChildList.begin(); childIter != m_ChildList.end(); )
	{
		childIter = m_ChildList.erase( childIter );
	}
}


