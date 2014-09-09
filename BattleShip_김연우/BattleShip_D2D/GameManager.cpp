#include "GameManager.h"
#include "GameScene.h"
#include "BattleField.h"
#include "UI.h"
#include "EndObject.h"
#include "Player.h"
#include "Board.h"
#include "Ship.h"


GameManager* GameManager::m_Instance = nullptr;

GameManager::GameManager()
{
	m_Player1 = new Player();
	m_Player2 = new Player();
	m_Player1->SetName( L"Player1" );
	m_Player2->SetName( L"Player2" );
	m_MyBattleField = new BattleField();
	m_EnemyBattleFiled = new BattleField();
	m_GameScene = new GameScene();
	m_UI = new UI();
	m_EndObject = new EndObject();
}


GameManager::~GameManager()
{
	delete m_Player1;
	m_MyBattleField->Clear();
	m_EnemyBattleFiled->Clear();
	m_GameScene->Clear();
	m_UI->Clear();
	m_EndObject->Clear();
}

void GameManager::Init()
{
	srand( (unsigned)time( NULL ) );
	m_NumOfTurn = 0;
	m_Player1->InitPlayer();
	m_Player2->InitPlayer();
	m_UI->Init();
	m_MyBattleField->Init();
	m_EnemyBattleFiled->Init();
	m_EnemyBattleFiled->PosX(m_MyBattleField->PosX() + m_MyBattleField->Width()+ m_MyBattleField->Width()/MAP_WIDTH );

	for( auto MyTile : (m_Player1->GetMyBoard())->GetTileList() )
	{
		m_MyBattleField->AddChild( MyTile );
	}

	for( auto EnemyTile :  m_Player1->GetEnemyBoard()->GetTileList()  )
	{
		m_EnemyBattleFiled->AddChild( EnemyTile );
	}

	for( auto ship : m_Player1->GetShipList() )
	{
		m_MyBattleField->AddChild( ship->GetBFSprite() );
		m_UI->AddChild( ship->GetUISprite() );
	}

	m_GameScene->AddChild( m_UI );
	m_GameScene->AddChild( m_MyBattleField );
	m_GameScene->AddChild( m_EnemyBattleFiled );
}

void GameManager::Render()
{
	m_GameScene->Render();
}

void GameManager::Update()
{
	switch( m_GameState )
	{
		case RUNNING:
			if( m_Player1->AllShipIsDestroyed() )
			{
				End( m_Player2->GetName() );
			}
			else if( m_Player2->AllShipIsDestroyed() )
			{
				End( m_Player1->GetName() );
			}
			else
			{
				++m_NumOfTurn;
				Position hitPosition = m_Player1->Attack();
				HitResult hitResult = m_Player2->SendResult( hitPosition );
				m_Player1->UpdateEnemyBoard( hitPosition , hitResult );
				m_Player2->UpdateMyBoard( hitPosition , hitResult );
				Sleep( 100 );

				Position hitPosition2 = m_Player2->Attack();
				HitResult hitResult2 = m_Player1->SendResult( hitPosition2 );
				m_Player2->UpdateEnemyBoard( hitPosition2 , hitResult2 );
				m_Player1->UpdateMyBoard( hitPosition2 , hitResult2 );
				Sleep( 100 );
			}

			m_GameScene->Update();
			break;
		case END:
			m_GameScene->Render();
			m_EndObject->Update();
			break;
		case RESET:
			m_GameScene->RemoveChild( m_EndObject , false );
			Init();
			SetGameState( RUNNING );
			break;
		case EXIT:
			PostQuitMessage( 0 );
			break;
		default:
			break;
	}
	
}

void GameManager::Run()
{
	Update();
	Render();
}

void GameManager::End( std::wstring winner )
{
	SetGameState( END );
	m_EndObject->Init( winner , m_NumOfTurn );
	m_GameScene->AddChild( m_EndObject );
}

GameManager* GameManager::GetInstance()
{
	if( m_Instance == nullptr )
	{
		m_Instance = new GameManager();
	}
	return m_Instance;
}

void GameManager::ReleaseInstance()
{
	if( m_Instance != nullptr )
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}




