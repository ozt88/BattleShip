#include "GameManager.h"
#include "GameScene.h"
#include "BattleField.h"
#include "UI.h"
#include "EnemyUI.h"
#include "InteractiveObject.h"
#include "Player.h"
#include "Board.h"
#include "Ship.h"

//한 싸이클에서 최대 플레이 횟수
#define	MAX_GAME_COUNT 10		
//한 턴이 돌아가는 시간
#define SLEEPTIME 30			
//안정적인 네트워크 연결을 위해 시스템을 정지시키는 시간
#define SAFECONNECTIONTIME 2000	

GameManager* GameManager::m_Instance = nullptr;

GameManager::GameManager()
    :m_GameState(GAME_WAIT) , m_SystemState(START_INIT),
    m_GameCount(0) , m_NumOfTurn(0) , m_Total(0) , m_WinNum(0),
    m_MyName( L"김짱쌤" )
{
    m_GameScene = GameScene::GetInstance();
    m_Network = new Network();
    m_Player1 = new Player();
    m_Player1->SetName( L"Player1" );
    m_Player2 = new Player();
    m_Player2->SetName( L"Player2" );
}

GameManager::~GameManager()
{
    SafeDelete(m_Player1);
    SafeDelete(m_Player2);
    m_GameScene->ReleaseInstance();
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
        SafeDelete( m_Instance );
    }
}

void GameManager::Init()
{
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

    m_GameScene->Init();
}

void GameManager::Render()
{
    m_GameScene->Render();
}

void GameManager::Update()
{
    switch( m_SystemState )
    {
        case START_INIT:
            StartInit();
            SetSystemState( START_RUNNING );
            break;
        case START_RUNNING:
            //input wait
            break;
        case NETWORK_INIT:
            NetworkInit();
            break;
        case NETWORK_READY:
            NetworkReady();
            break;
        case NETWORK_RESET:
            NetworkReset();
            break;
        case NETWORK_RUNNING:
            GetPacket();
            NetworkPlay();
            break;
        case SOLO_INIT:
            SoloInit();
            SetSystemState( SOLO_RUNNING );
            break;
        case SOLO_RUNNING:
            SoloPlay();
            break;
        case SYSTEM_PAUSE:
            //input wait
            break;
        case SYSTEM_QUIT:
            PostQuitMessage( 0 );
            break;
        default:
            break;
    }
    m_GameScene->Update();
}

void GameManager::Run()
{
    Update();
    Render();
}


void GameManager::StartInit()
{
    m_GameScene->StartScene();
}

void GameManager::SoloInit()
{
    m_NumOfTurn = 0;
    m_Player1->InitPlayer();
    m_Player2->InitPlayer();
    m_GameScene->Init();
    m_GameScene->BattleScene();

    SetGameState( GAME_RUNNING );
}

void GameManager::SoloPlay()
{
    switch( m_GameState )
    {
        case GAME_RUNNING:
            if( m_Player1->AllShipIsDestroyed() )
            {
                End( false );
            }
            else if( m_Player2->AllShipIsDestroyed() )
            {
                End( true );
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
            break;

        case GAME_END:
            break;

        case GAME_RESET:
            SoloInit();
            SetGameState( GAME_RUNNING );
            break;

        case GAME_OVER:
            Exit();
            SetGameState( GAME_WAIT );
            break;

        case GAME_QUIT:
            SetSystemState(SYSTEM_QUIT);
            break;

        default:
            break;
    }

    m_GameScene->Update();
}
void GameManager::NetworkInit()
{
    ErrorType error;
    try
    {
        Network::Initialize();
    }
    catch( Network::Exception )
    {
        m_GameScene->GetEndObject()->SetMessage( L"초기화 문제 발생!" );
        SetSystemState( SYSTEM_PAUSE );
        return;
    }

    try
    {
        m_Network->Connect( SERVERIPPORT );
    }
    catch( Network::Exception ex )
    {
        switch( ex )
        {
            case Network::NETWORK_ERROR:
                m_GameScene->GetEndObject()->SetMessage( L"서버 연결 실패!" );
                break;
            case Network::PARAMETER_ERROR:
                m_GameScene->GetEndObject()->SetMessage( L"인수 오류!" );
                break;
        }
        SetSystemState( SYSTEM_PAUSE );
        return;
    }
    m_GameScene->GetEndObject()->SetMessage( L"게임 시작 대기중..." );

    error = m_Network->SubmitName( m_MyName.c_str() , 141019 );
    if( error == ET_DUPLICATED_NAME )
    {
        m_GameScene->GetEndObject()->SetMessage( L"이미 있는 이름!" );
        SetSystemState( SYSTEM_PAUSE );
        return;
    }
    Sleep( SAFECONNECTIONTIME );
    SetSystemState( NETWORK_READY );
}

void GameManager::NetworkReady()
{
    Network::GameStartData gameStartData;
    m_Network->WaitForStart( &gameStartData );
    m_GameScene->GetEndObject()->SetMessage( L"게임 준비중..." );
    SetSystemState( NETWORK_RESET );
	Sleep( SAFECONNECTIONTIME );
}
    
void GameManager::NetworkReset()
{
    char mapdata[MAP_SIZE];
    m_NumOfTurn = 0;
    m_Player1->InitPlayer();
    m_GameScene->Init();
    m_GameScene->BattleScene();

    m_Player1->GetShipData()->ToMapData( mapdata );
    m_Network->SubmitMap( mapdata );
    SetSystemState( NETWORK_RUNNING );
    SetGameState( GAME_WAIT );
}

void GameManager::NetworkPlay()
{
    ErrorType error;
    Position hitPosition;
    Coord hitCoord;
    Network::AttackResultData attackResult;

    switch( m_GameState )
    {
        case GAME_ATTACK:
            hitPosition = m_Player1->Attack();
            hitCoord.mX = hitPosition.m_X;
            hitCoord.mY = hitPosition.m_Y;
            error = m_Network->SubmitAttack( hitCoord );
            _ASSERT( error != ET_INVALID_ATTACK );
            break;

        case GAME_RESULT:
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
        case GAME_WAIT:
            //waiting...
            break;
        case GAME_END:
            End();
            break;

        case GAME_RESET:
            NetworkReset();
            break;

        case GAME_OVER:
            Exit();
            SetGameState( GAME_WAIT );
            break;

        case GAME_QUIT:
            m_Network->Disconnect();
            PostQuitMessage( 0 );
            break;

        default:
            break;
    }
    m_GameScene->Update();
}



void GameManager::End( bool isWinner )
{
    m_Total += m_NumOfTurn;
    if( m_GameCount++ >= MAX_GAME_COUNT )
    {
        SetGameState( GAME_OVER );
    }
    else
    {
        m_GameScene->GameEndScene( isWinner , m_GameCount , (float)m_NumOfTurn );
        if( isWinner )m_WinNum++;
        SetGameState( GAME_END );
        //SetGameState( GAME_RESET );
    }

}

void GameManager::End()
{
    Network::GameResultData gameResult;
    std::wstring winner;
    gameResult = m_Network->GetGameResult();
    if( gameResult.isWinner ) m_WinNum++;
    m_GameScene->GameEndScene( gameResult.isWinner , m_WinNum , (float)gameResult.turns );
    SetSystemState( SYSTEM_PAUSE );
}


void GameManager::Exit()
{
    
    float average;
    int winCount;
    Network::FinalResultData finalResult;
    if( m_GameMode == NETWORK )
    {
        finalResult = m_Network->GetFinalResult();
        winCount = finalResult.winCount;
        average = finalResult.avgTurns;
    }
    else
    {
        winCount = m_WinNum;
        average = ( m_GameCount == 0 ) ? 0.f : ( float )m_Total / m_GameCount;
    }
    m_GameScene->GetEndObject()->SetMessage( L"Calculating..." );
    m_GameScene->GameOverScene( winCount , average );
    m_Total = 0;
    m_GameCount = 0;
    m_WinNum = 0;
    Sleep( SAFECONNECTIONTIME );
    SetSystemState( SYSTEM_PAUSE );
}


void GameManager::GetPacket()
{
    Sleep(SLEEPTIME);
    PacketType packetType;
    ErrorType error = m_Network->GetPacketType( &packetType );
    switch( packetType )
    {
        case PKT_SC_ERROR:
            PostQuitMessage( 0 );
            break;
        case PKT_SC_NEXT_GAME:
            SetGameState( GAME_RESET );
            break;
        case PKT_SC_ALL_OVER:
            SetGameState( GAME_OVER );
            break;
        case PKT_SC_MY_TURN:
            SetGameState( GAME_ATTACK );
            break;
        case PKT_SC_ATTACK_RESULT:
            SetGameState( GAME_RESULT );
            break;
        case PKT_SC_GAME_OVER:
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








