#include "GameManager.h"
#include "GameScene.h"
#include "BattleField.h"
#include "UI.h"
#include "EndObject.h"
#include "Player.h"
#include "Board.h"
#include "Ship.h"

#define	MAX_GAME_COUNT 10
#define SLEEPTIME 50


GameManager* GameManager::m_Instance = nullptr;

GameManager::GameManager()
    :m_GameState(RUNNING) , m_GameCount(0) , m_NumOfTurn(0) , m_Total(0)
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
    SafeDelete(m_Player1);
    SafeDelete(m_Player2);
    m_GameScene->ReleaseInstance();
}

void GameManager::Init()
{
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
            if( m_Player2->AllShipIsDestroyed() )
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
                Sleep( SLEEPTIME );

                Position hitPosition2 = m_Player2->Attack();
                HitResult hitResult2 = m_Player1->SendResult( hitPosition2 );
                m_Player2->UpdateEnemyBoard( hitPosition2 , hitResult2 );
                m_Player1->UpdateMyBoard( hitPosition2 , hitResult2 );
                Sleep( SLEEPTIME );
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
            Exit();
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
    _ASSERT( m_NumOfTurn <= 64 );
    m_Total += m_NumOfTurn;
    if( ++m_GameCount >= MAX_GAME_COUNT )
    {
        SetGameState( EXIT );
    }
    else
    {
        m_GameScene->MakeEndScene( winner , m_NumOfTurn );
        SetGameState( END );
        //SetGameState( RESET );
    }
    
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
        SafeDelete(m_Instance);
    }
}

void GameManager::Exit()
{
    float average = (float)m_Total / m_GameCount;
    PostQuitMessage( 0 );
}




