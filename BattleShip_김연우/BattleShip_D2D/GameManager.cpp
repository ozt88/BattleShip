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
	SafeDelete( m_Instance );
}

void GameManager::Init()
{
	//Player 생성까지 완료되면 플레이어로 부터 배의 스프라이트들과 
	//플레이어가 들고 있는 맵의 타일 스프라이트를 받을 수 있다.
	//초기화할때 한번만 이 스프라이트와 오브젝트들을 GameScene에 추가한다.

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
	//Render는 그냥 GameScene Render로 충분하다.
	//##GameScene과 GameManager를 분리할 수 있을것 같다.
	//##서로 다른 루프로 연산을 하도록 만드는 것이 효율적이라고 생각.
	//##수정의 여지..
    m_GameScene->Render();
}

//GM의 업데이트는 현 시스템 상태에 따라 결정된다.
void GameManager::Update()
{
    switch( m_SystemState )
    {
		//처음 프로그램 켰을때
        case START_INIT:
            StartInit();
            SetSystemState( START_RUNNING );
            break;
		//재대로 부팅이 되었으면 입력을 대기
        case START_RUNNING:
            //input wait
            break;
		//네트워크를 시작할때
        case NETWORK_INIT:
            NetworkInit();
            break;
		//네트워크 시작 대기
        case NETWORK_READY:
            NetworkReady();
            break;
		//네트워크 재시작
        case NETWORK_RESET:
            NetworkReset();
            break;
		//네트워크 게임중
        case NETWORK_RUNNING:
            GetPacket();
            NetworkPlay();
            break;
		//솔로 게임 시작
        case SOLO_INIT:
            SoloInit();
            SetSystemState( SOLO_RUNNING );
            break;
		//솔로 게임중
        case SOLO_RUNNING:
            SoloPlay();
            break;
		//시스템 전체 일시정지(update시 아무것도 안함)
        case SYSTEM_PAUSE:
            //input wait
            break;
		//시스템 종료
        case SYSTEM_QUIT:
            PostQuitMessage( 0 );
            break;
        default:
            break;
    }
	//GM업데이트 끝났으면 GS도 업데이트
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

//게임 플레이는 게임 상태에 따라 진행된다.
void GameManager::SoloPlay()
{
    switch( m_GameState )
    {
		//게임 진행중
        case GAME_RUNNING:
            m_NumOfTurn++;
			if( Engage( m_Player1 , m_Player2 ) )
			{
				SoloEnd( true );
			}
			else if( Engage( m_Player2 , m_Player1 ) )
			{
				SoloEnd( false );
			}
            break;
		//한 게임 종료
        case GAME_END:
            break;
		//게임 리셋
        case GAME_RESET:
            SoloInit();
            SetGameState( GAME_RUNNING );
            break;
		//게임사이클 종료
        case GAME_OVER:
            Exit();
            SetGameState( GAME_WAIT );
            break;
		//시스템 종료
        case GAME_QUIT:
            SetSystemState(SYSTEM_QUIT);
            break;

        default:
            break;
    }

    m_GameScene->Update();
}

//교전함수 attacker가 defender를 공격 
bool GameManager::Engage( Player* attacker , Player* defender )
{
	Position hitPosition = attacker->Attack();
	HitResult hitResult = defender->SendResult( hitPosition );
	attacker->UpdateEnemyBoard( hitPosition , hitResult );
	defender->UpdateMyBoard( hitPosition , hitResult );
	Sleep( SLEEPTIME );
	//배가 다 터졌는지를 확인하여 리턴
	return defender->AllShipIsDestroyed();
}

//네트워크 초기화하는 함수
//네트워크 오류를 try catch로 잡아서 화면에 어떤 오류인지 출력
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

//네트워크 연결이 완료되면 상대방을 기다린다.
void GameManager::NetworkReady()
{
    Network::GameStartData gameStartData;
    m_Network->WaitForStart( &gameStartData );
    m_GameScene->GetEndObject()->SetMessage( L"게임 준비중..." );
    SetSystemState( NETWORK_RESET );
	Sleep( SAFECONNECTIONTIME );
}

//게임이 끝나면 새로 리셋한다.
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

//네트워크 게임플레이 구현 함수
void GameManager::NetworkPlay()
{
    ErrorType error;
    Position hitPosition;
    Coord hitCoord;
    Network::AttackResultData attackResult;

    switch( m_GameState )
    {
		//내 공격턴
        case GAME_ATTACK:
            hitPosition = m_Player1->Attack();
            hitCoord.mX = hitPosition.m_X;
            hitCoord.mY = hitPosition.m_Y;
            error = m_Network->SubmitAttack( hitCoord );
            _ASSERT( error != ET_INVALID_ATTACK );
            break;
		//결과값 받아서 적용
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
                //내가 맞았을때 UIObject에 갱신하기 위하여 SendResult함수를 재탕한다.
				m_Player1->SendResult( hitPosition ); 
            }
            break;
		//게임 대기상태
        case GAME_WAIT:
            //waiting...
            break;
		//한 게임이 종료되면 interactiveObject를 띄우고 입력대기
        case GAME_END:
            NetworkEnd();
            break;
		//게임 리셋
        case GAME_RESET:
            NetworkReset();
            break;
		//한 사이클 종료
        case GAME_OVER:
            Exit();
            SetGameState( GAME_WAIT );
            break;
		//전체 게임 종료
        case GAME_QUIT:
            m_Network->Disconnect();
            PostQuitMessage( 0 );
            break;

        default:
            break;
    }
    m_GameScene->Update();
}


//솔로 게임이 끝나면 오브젝트띄워서 입력대기
void GameManager::SoloEnd( bool isWinner )
{
    m_Total += m_NumOfTurn;
	//전체 게임이 끝나는 경우와 아닌 경우로 나눠준다.
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

//네트워크 게임이 끝나면 오브젝트 띄우고 대기
void GameManager::NetworkEnd()
{
    Network::GameResultData gameResult;
    std::wstring winner;
    gameResult = m_Network->GetGameResult();
    if( gameResult.isWinner ) m_WinNum++;
    m_GameScene->GameEndScene( gameResult.isWinner , m_WinNum , (float)gameResult.turns );
    SetSystemState( SYSTEM_PAUSE );
}

//게임 종료처리
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

//패킷을 받는 함수
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

//HitResult값을 Network전용인 AttackResult로 바꿔주는 함수
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








