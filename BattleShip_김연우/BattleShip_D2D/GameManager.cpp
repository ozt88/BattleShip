#include "GameManager.h"
#include "GameScene.h"
#include "BattleField.h"
#include "UI.h"
#include "EnemyUI.h"
#include "EndObject.h"
#include "Player.h"
#include "Board.h"
#include "Ship.h"

#define	MAX_GAME_COUNT 10
#define SLEEPTIME 100
#define NETWORK true

GameManager* GameManager::m_Instance = nullptr;

GameManager::GameManager()
    :m_GameState( RUNNING ) , m_GameCount( 0 ) , m_NumOfTurn( 0 ) , m_Total( 0 ) , m_MyName( L"±èÂ¯½Ü" )
{
    m_Network = new Network();
    m_Player1 = new Player();
    m_Player1->SetName( L"Player1" );
    if( !NETWORK )
    {
        m_Player2 = new Player();
        m_Player2->SetName( L"Player2" );
    }

    m_GameScene = GameScene::GetInstance();
    for( auto MyTile : m_Player1->GetMyBoard()->GetTileList() )
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
        m_GameScene->GetEnemyUI()->AddChild( ship->GetEnemyUISprite() );
    }

	Network::GameStartData gameStartData;
    if( NETWORK )
    {
        Network::Initialize();
        try
        {
            m_Network->Connect( SERVERIPPORT );
        }
        catch( Network::Exception )
        {
            PostQuitMessage( 0 );
        }
        m_Network->SubmitName( m_MyName.c_str() , 141019);
		m_Network->WaitForStart( &gameStartData );
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
    char mapdata[MAP_SIZE];
    if( NETWORK )
    {
        m_Player1->GetShipData()->ToMapData( mapdata );
        m_Network->SubmitMap( mapdata );
    }
    else
    {
        m_Player2->InitPlayer();
    }
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
                End(m_Player2->GetName());
            }
            else if( m_Player2->AllShipIsDestroyed() )
            {
                End( m_Player1->GetName());
            }
            else
            {
                m_NumOfTurn++;
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
        case GAME_END:
            m_GameScene->GetEndObject()->Update();
            break;
        case RESET:
            m_GameScene->RemoveChild( m_GameScene->GetEndObject() , false );
            Init();
            SetGameState( RUNNING );
            break;
        case GAME_OVER:
            Exit();
            break;
        case QUIT_GAME:
            PostQuitMessage( 0 );
            break;
        default:
            break;
    }
    
}


void GameManager::UpdateInNetwork()
{
    ErrorType error;
    Position hitPosition;
    Coord hitCoord;
    Network::AttackResultData attackResult;

    switch( m_GameState )
    {
        case ATTACK:
            hitPosition = m_Player1->Attack();
            hitCoord.mX = hitPosition.m_X;
            hitCoord.mY = hitPosition.m_Y;
            error = m_Network->SubmitAttack( hitCoord );
            _ASSERT( error != ET_INVALID_ATTACK );
            break;

        case RESULT:
            attackResult = m_Network->GetAttackResult();
            if( attackResult.isMine )
            {
                hitPosition.m_X = attackResult.pos.mX;
                hitPosition.m_Y = attackResult.pos.mY;
				m_Player1->UpdateEnemyBoard( hitPosition , AttackResultPassing( ( AttackResultTypes )attackResult.attackResult ) );
                
            }
            else
            {
				hitPosition.m_X = attackResult.pos.mX;
				hitPosition.m_Y = attackResult.pos.mY;
				m_Player1->UpdateMyBoard( hitPosition , AttackResultPassing( ( AttackResultTypes )attackResult.attackResult ) );
                m_Player1->SendResult( hitPosition );
            }
            break;

        case GAME_END:
            SetGameState( WAIT );
            Sleep( SLEEPTIME );
            break;

        case RESET:
            m_GameScene->RemoveChild( m_GameScene->GetEndObject() , false );
            Init();
            SetGameState( WAIT );
            break;

        case GAME_OVER:
            m_GameScene->GetEndObject()->Update();
            break;

        case QUIT_GAME:
            PostQuitMessage(0);
            break;

        default:
            break;
    }
}



void GameManager::Run()
{
    if( NETWORK )
    {
        GetPacket();
        UpdateInNetwork();
    }
    else
    {
        Update();
    }
    Render();
}

void GameManager::End( const std::wstring& winner )
{
    m_Total += m_NumOfTurn;
    if( ++m_GameCount >= MAX_GAME_COUNT )
    {
        SetGameState( GAME_OVER );
    }
    else
    {
        m_GameScene->MakeEndScene( winner , m_NumOfTurn );
        SetGameState( GAME_END );
        //SetGameState( RESET );
    }
    
}

void GameManager::End()
{
    Network::GameResultData gameResult;
    std::wstring winner;
    gameResult =m_Network->GetGameResult();

    if( gameResult.isWinner ) winner = L"ME";
    else winner = L"NOT ME";

    m_GameScene->MakeEndScene( winner , gameResult.turns );
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
    float average;
    Network::FinalResultData finalResult;
    if( NETWORK )
    {
		finalResult = m_Network->GetFinalResult();
		average = finalResult.avgTurns;
    }
    else
    {
        average = ( m_GameCount == 0 ) ? 0.f : ( float )m_Total / m_GameCount;
    }
    
    m_GameScene->MakeEndScene( L"total" , ( int )average );
    SetGameState( GAME_END );
}

void GameManager::GetPacket()
{
    PacketType packetType;
    ErrorType error = m_Network->GetPacketType( &packetType );
    switch( packetType )
    {
        case PKT_SC_ERROR:
            PostQuitMessage( 0 );
            break;
        case PKT_SC_NEXT_GAME:
            SetGameState( RESET );
            break;
        case PKT_SC_ALL_OVER:
            Exit();
            SetGameState( GAME_OVER );
            break;
        case PKT_SC_MY_TURN:
            SetGameState( ATTACK );
            break;
        case PKT_SC_ATTACK_RESULT:
            SetGameState( RESULT );
            break;
        case PKT_SC_GAME_OVER:
            End();
            SetGameState( GAME_END );
            break;
        default:
            break;
    }
}

HitResult GameManager::AttackResultPassing( AttackResultTypes result )
{
    switch( result )
    {
        case AR_NONE:
            return WATER;
        case AR_MISS:
            return MISS;
        case AR_HIT:
            return HIT;
		case AR_DESTROY_AIRCRAFT:
            return DESTROY_AIRCRAFT;
		case AR_DESTROY_BATTLESHIP:
            return DESTROY_BATTLESHIP;
		case AR_DESTROY_CRUISER:
            return DESTROY_CRUISER;
        case AR_DESTROY_DESTROYER:
            return DESTROY_DESTROYER;
        default:
            return WATER;
    }
}






