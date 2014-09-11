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
	m_GameScene = GameScene::GetInstance();

	for( auto MyTile :m_Player1->GetMyBoard()->GetTileList() )
	{
		m_GameScene->GetMyBattleField()->AddChild( MyTile );
	}

	for( auto EnemyTile : m_Player1->GetEnemyBoard()->GetTileList() )
	{
		m_GameScene->GetEnemyBattleFiled()->AddChild( EnemyTile );
	}

	for( auto ship : m_Player1->GetShipList() )
	{
		m_GameScene->GetMyBattleField()->AddChild( ship->GetBFSprite() );
		m_GameScene->GetUI()->AddChild( ship->GetUISprite() );
	}
}


GameManager::~GameManager()
{
	delete m_Player1;
	delete m_Player2;
	m_GameScene->ReleaseInstance();
}

void GameManager::Init()
{
	srand( (unsigned)time( NULL ) );
	m_NumOfTurn = 0;
	m_Player1->InitPlayer();
	m_Player2->InitPlayer();
	m_GameScene->Init();

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
				Sleep( 10 );

				Position hitPosition2 = m_Player2->Attack();
				HitResult hitResult2 = m_Player1->SendResult( hitPosition2 );
				m_Player2->UpdateEnemyBoard( hitPosition2 , hitResult2 );
				m_Player1->UpdateMyBoard( hitPosition2 , hitResult2 );
				Sleep( 10 );
			}

			m_GameScene->Update();
			break;
		case END:
			m_GameScene->Render();
			m_GameScene->GetEndObject()->Update();
			break;
		case RESET:
			m_GameScene->RemoveChild( m_GameScene->GetEndObject() , false );
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

void GameManager::End( const std::wstring& winner )
{
	SetGameState( END );
	m_GameScene->MakeEndScene( winner , m_NumOfTurn );
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




