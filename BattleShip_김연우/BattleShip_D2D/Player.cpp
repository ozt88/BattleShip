#include "Player.h"
#include "GameScene.h"
#include "EnemyUI.h"
#include "Board.h"
#include "AirCraft.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Enum.h"

#define MAGIC_NUM 70
#define BIG_PROB 1000

Player::Player()
{
    m_Name = L"Player";
    m_MyBoard = new Board();
    m_EnemyBoard = new Board();
    m_ShipData = new ShipData();
    float posY = 0.f;

    //배들을 y축 위치값 순서대로 하나씩 UI에 배치하면서 생성
    m_MyShipList.push_back( new AirCraft( ++posY ) );
    m_MyShipList.push_back( new BattleShip( ++posY ) );
    m_MyShipList.push_back( new Cruiser( ++posY ) );
    m_MyShipList.push_back( new Destroyer( ++posY ) );
    m_MyShipList.push_back( new Destroyer( ++posY ) );

    //std::list<Ship*> shipListFromManager;
    //std::list<Ship*>::iterator iterPos = m_ShipList.begin();
    //m_ShipList.insert( iterPos , shipListFromManager.begin() , shipListFromManager.end() );
}


Player::~Player()
{
    SafeDelete(m_MyBoard);
    SafeDelete(m_EnemyBoard);
    for( auto ship : m_MyShipList )
    {
        SafeDelete(ship);
    }
    m_MyShipList.clear();
    for( auto enemyShip : m_EnemyShipList )
    {
        SafeDelete( enemyShip );
    }
    m_EnemyShipList.clear();
}

//가지고 있는 배들을 자동으로 배치하는 함수
void Player::SetupShips()
{
    Position setPos;
    MyDirection direction = UP;
    
    //먼저 배들을 초기화 한다. 
    //for문이 2개 따로 있는 이유는 전부 초기화를 시키지 않으면,
    //초기화 하지 않은 배들에 앞서 배치해야되는 배들이 영향을 받기 때문이다.
    for( auto shipIter : m_MyShipList )
    {
        shipIter->ShipInit();
    }

    for( auto shipIter : m_MyShipList )
    {
        do
        {
            FindBestSetupPos( &setPos , &direction , shipIter->GetMaxHP() );
        } while( !IsValidPosition( setPos , shipIter->GetMaxHP() , direction ) );
        shipIter->PlaceShip( setPos , direction );
    }
    m_EnemyBoard->InitBoard();
}

bool Player::IsValidPosition( const Position& setPos , int maxHp , const MyDirection& direction )
{
    Position curPos = setPos;
    for( int i = 0; i < maxHp; i++ )
    {
        if( !curPos.isValid() )
        {
            return false;
        }

        for( auto iterPos : m_MyShipList )
        {
            if( iterPos->IsDuplicate( curPos ) )
            {
                return false;
            }
        }
        curPos = curPos.dirPos( direction );
    }
    return true;
}



Position Player::Attack()
{
    Position maxProbPos = Position( 0 , 0 );
    //타겟모드와 헌트모드로 구분
    //하나 맞췄으면 타겟 맞춘게 없으면 헌트
    if( m_AImode == HUNT)
    {
        //일단 맵의 확률을 계산하고 확률이 가장 높은 포지션을 리턴
        CalculateBoard();	
        Position curPos;
        int	maxProb = 0;
        for( int y = 0; y < MAP_HEIGHT; ++y )
        {
            for( int x = 0; x < MAP_WIDTH; ++x )
            {
                curPos = Position( x , y );
                if( m_EnemyBoard->IsWater( curPos ) && m_EnemyBoard->GetBoardProb( curPos ) > maxProb && !((x+y)%2) )
                {
                    maxProbPos = curPos;
                    maxProb = m_EnemyBoard->GetBoardProb( maxProbPos );
                }
            }
        }
    }
    else
    {
        //타겟을 추적한다.
        maxProbPos = FindTarget( m_EnemyBoard->GetBoardStatus( m_LastHit.m_X, m_LastHit.m_Y ) );
    }

    return maxProbPos;
}

//위치를 공격받으면 공격 결과를 리턴하는 함수
HitResult Player::SendResult( const Position& position )
{
    HitResult hitResult = WATER;

    for( auto shipIter : m_MyShipList )
    {
        hitResult = shipIter->HitCheck( position );
        if( hitResult != MISS )
        {
            break;
        }
    }

    return hitResult;
}

//공격 받은 이후에 내 보드를 업데이트
void Player::UpdateMyBoard( const Position& position , const HitResult& hitResult )
{
    m_MyBoard->MapUpdate( position , hitResult );
}


//공격한 뒤에 받은 결과로 적 보드를 업데이트
void Player::UpdateEnemyBoard( const Position& position , const HitResult& hitResult )
{
    m_EnemyBoard->MapUpdate( position , hitResult );

    //이하 AI관련
    //적이 리턴한 결과에 따라 AI정책 결정

    GameScene* GM =	GameScene::GetInstance();
    int destroySize = 0;
    m_LastHit = position;

    if( hitResult == HIT )
    {
        if( m_AImode == HUNT)
        {
            m_Origin = position;
            m_AImode = TARGET;
            m_FindDir = FindBestNeighbor(m_Origin);
        }
    }
    else if( hitResult != MISS )
    {
        switch( hitResult )
        {
            case DESTROY_AIRCRAFT:
                destroySize = ShipSize::AIRCRAFT_SIZE;
                break;
            case DESTROY_BATTLESHIP:
                destroySize = ShipSize::BATTLESHIP_SIZE;
                break;
            case DESTROY_CRUISER:
                destroySize = ShipSize::CRUISER_SIZE;
                break;
            case DESTROY_DESTROYER:
                destroySize = ShipSize::DESTROYER_SIZE;
                break;
            default:
                break;
        }

        //파괴된 경우 EnemyUI의 해당 배를 파괴비트맵으로 변환
        GM->GetEnemyUI()->MakeDestroySprite( destroySize );
        //그리고 EnemyShipList에서 해당 배를 하나 삭제해준다.
        for( auto enemyShip : m_EnemyShipList )
        {
            if( enemyShip->m_Size == destroySize)
            {
                --enemyShip->m_Num;
            }
        }
    }
}

bool Player::AllShipIsDestroyed()
{
    for( auto shipIter : m_MyShipList )
    {
        if( !shipIter->IsDestroyed() )
        {
            return false;
        }
    }
    return true;
}

//플레이어 초기화 함수 한 게임이 시작될때마다 게임 초기화를 위해 호출된다.
void Player::InitPlayer()
{
    m_MyBoard->InitBoard();
    m_EnemyBoard->InitBoard();
    SetupShips();
    //네트워크를 위한 데이터 생성
    MakeShipData();
    //AI를 위한 정보들을 초기화
    InitEnemyShips();
    m_AImode = HUNT;
    m_LastHit = Position();
    m_Origin = Position();
    m_FindDir = UP;
    m_DestroyPosList.clear();
    m_HitPosList.clear();
}

//EnemyShip데이터를 초기화
void Player::InitEnemyShips()
{
    for( auto enemyShip : m_EnemyShipList )
    {
        enemyShip->m_Num = 0;
    }
    for( auto ship : m_MyShipList )
    {
        bool isIn = false;
        for( auto enemyShip : m_EnemyShipList )
        {
            if( enemyShip->m_Size == ship->GetMaxHP() )
            {
                enemyShip->m_Num++;
                isIn = true;
                break;
            }
        }
        if( !isIn )
        {
            m_EnemyShipList.push_back( new EnemyShip( ship->GetMaxHP() , 1 ) );
        }
    }
}

//EnemyBoard의 확률 데이터 계산
void Player::CalculateBoard()
{
	//계산할때마다 모든 값을 초기화
    m_EnemyBoard->ClearProb();
    for( auto enemyShip : m_EnemyShipList )
    {
        for( int num = 0; num < enemyShip->m_Num; ++num )
        {
            for( int y = 0; y < MAP_HEIGHT; ++y )
            {
                for( int x = 0; x < MAP_WIDTH; ++x )
                {
					//배를 배치할 수 있는 위치에 확률값 1씩 추가
                    if( ShipCanOccupy( x , y , enemyShip->m_Size , false ) )
                    {
                        m_EnemyBoard->IncreaseProbablity( x , y , enemyShip->m_Size , false );
                    }
                    if( ShipCanOccupy( x , y , enemyShip->m_Size , true ) )
                    {
                        m_EnemyBoard->IncreaseProbablity( x , y , enemyShip->m_Size , true );
                    }
                }
            }
        }
    }
	//코너에 확률 비중을 높여서 코너링 하는 애들한테 취약한점 보완
    //m_EnemyBoard->ScaleBoardProb( Position( 0 , 0 ) , 2 );
    //m_EnemyBoard->ScaleBoardProb( Position( MAP_WIDTH - 1 , 0 ) , 2 );
    //m_EnemyBoard->ScaleBoardProb( Position( 0 , MAP_HEIGHT - 1 ) , 2 );
    //m_EnemyBoard->ScaleBoardProb( Position( MAP_WIDTH - 1 , MAP_HEIGHT - 1 ) , 2 );
}


//적 보드에 배를 배치할 수 있는지 여부를 판단하는 함수 
//##기존의 isValid와 유사 수정의 여지
bool Player::ShipCanOccupy( int x , int y , int shipSize , bool isVertical )
{
    int head = isVertical ? y : x;
    int end = head + shipSize - 1;
    int max = isVertical ? MAP_HEIGHT :MAP_WIDTH;

    if( end > max - 1 ) return false;
    Position checkPos;
    for( int i = head; i <= end; ++i )
    {
        checkPos = isVertical ? Position( x , i ) : Position( i , y );
        if( m_EnemyBoard->GetBoardStatus( checkPos.m_X , checkPos.m_Y ) == MISS )
        {
            return false;
        }
    }
    return true;
}

//인자로 주어진 위치값에서 가까운 이웃(상하좌우)중 
//가장 높은 확률을 갖고 있는 방향을 리턴하는 함수
MyDirection Player::FindBestNeighbor( const Position& pos )
{
    std::vector<Position> neighbors;
    Position neighbor = pos;
    int bestDir = 0;
    int bestProb = 0;
    for( int i = 0; i < DIR_MAX; ++i )
    {
        neighbors.push_back( neighbor.dirPos((MyDirection)i));
    }

    for( size_t i = 0; i < neighbors.size(); ++i )
    {
        Position curPos = neighbors[i];
        if( curPos.isValid() && m_EnemyBoard->GetBoardProb( curPos ) > bestProb )
        {
            bestDir = i;
            bestProb = m_EnemyBoard->GetBoardProb( curPos );
        }
    }
    return ( MyDirection )bestDir;
}

//타겟모드에서 지옥끝까지 타겟을 추적하는 함수
Position Player::FindTarget( const HitResult& hitresult )
{
    Position resultPos;
	//현재 들어온 결과값에 따라 연산을 수행
    switch( hitresult )
    {
        case HIT:
            resultPos = HitFind();
            break;
        case MISS:
            resultPos = MissFind();
            break;
        case DESTROY_AIRCRAFT:
            resultPos = DestroyFind( ShipSize::AIRCRAFT_SIZE );
            break;
        case DESTROY_BATTLESHIP:
            resultPos = DestroyFind( ShipSize::BATTLESHIP_SIZE );
            break;
        case DESTROY_CRUISER:
            resultPos = DestroyFind( ShipSize::CRUISER_SIZE );
            break;
        case DESTROY_DESTROYER:
            resultPos = DestroyFind( ShipSize::DESTROYER_SIZE );
            break;
        default:
            break;
    }
    
    return resultPos;
}

//타겟모드에서 이번턴에 맞췄으면?
Position Player::HitFind()
{
	//일단 때린 위치를 맞춘 리스트에 추가하고
	//FindBestNeighbor함수가 알려준 방향으로 다음 공격위치를 선정
    m_HitPosList.push_back( m_LastHit );
    Position nextPos = m_LastHit.dirPos( m_FindDir );
	//그 위치가 Valid한지 확인하고 적절하다면 그 위치를 리턴
	//아니라면 Miss인 경우의 추적방식으로 전환
    if( nextPos.isValid() && m_EnemyBoard->IsWater( nextPos ) )
    {
        return nextPos;
    }
    return MissFind();
}

//타겟모드인데 이번턴에 놓쳤으면?
Position Player::MissFind()
{
    Position nextPos; //다음 공격 위치
    bool findNextPos = false; //적당한 다음 공격 위치를 찾았다면 true
    
	//일단 현재 Origin으로 돌아가서 다른 방향을 시도해본다.(TryOtherDirection)
	//시도가 성공하면 변경된 nextPos값으로 공격
	//실패하면 (origin이 사방으로 막혀있는 경우) 
	//origin을 hitPosList에 저장된 다른 HitPos로 변경하고 다시 방향을 탐색한다.
	for( auto hitPos : m_HitPosList )
    {
        if( findNextPos = TryOtherDirection( &nextPos ) )
        {
            break;
        }
        m_Origin = hitPos;
    }
    
	//모든 HitPos들을 돌았는데도 다음 공격할 위치가 없다.(매우 적은 확률로 존재)
	//그러면 그냥 타겟모드를 포기하고 기존 HUNT의 공격방식으로 돌아간다.
    if( !findNextPos )
    {
        m_AImode = HUNT;
        nextPos = Attack();
    }


	//이렇게 했는데도 잘못된 결과가 나오면 ASSERT에 걸립니다. 하하
    HitResult result = m_EnemyBoard->GetBoardStatus( nextPos );
    _ASSERT( result == WATER );
    
    return nextPos;
}

//origin에서 다른 방향의 위치를 시도해보는 함수
//성공하면 true를 리턴하고 nextPos를 변경해준다.
bool Player::TryOtherDirection( OUT Position* nextPos )
{
	bool isValid = false;
	for( int i = 0; i < DIR_MAX; ++i )
	{
		m_FindDir = ( MyDirection )( ( m_FindDir + 1 ) % DIR_MAX );
		*nextPos = m_Origin.dirPos( m_FindDir );
		if( nextPos->isValid() && m_EnemyBoard->IsWater( *nextPos ) )
		{
			isValid = true;
			break;
		}
	}

	return isValid;
}

//이번턴의 결과값이 Destroy라면?
Position Player::DestroyFind( int size )
{
	//일단 공격한 위치를 Destroy리스트에 집어넣는다.
    m_DestroyPosList.push_back( m_LastHit );
    Position curPos = m_LastHit;
    MyDirection destroyDir = m_FindDir;
	//그리고 현재 방향에서부터 destroy된 배가 놓인 방향을 찾는다.
    FindDestroyDir( curPos , size , &destroyDir );
	//찾은 다음에 HitPosList에서 destroy된 배가 가진 위치들을 제외시킨다.
	//파괴된 배는 이제 더 이상 타겟이 아니기 때문
    RemoveDestroyedPath( curPos , size , destroyDir );

	//이렇게해서 남은 Hitpos가 없다면 HUNT모드로 전환하여 공격
    if( m_HitPosList.empty() )
    {
        m_AImode = HUNT;
        return Attack();
    }
	//아직 남아있다면 Origin을 변경시켜서 MissFind방법으로 다시 추적시작
    else
    {
        m_Origin = m_HitPosList.front();
        return MissFind();
    }
}

//파괴된 방향을 찾는 함수
//방향을 찾지 못하면 false를 리턴한다. 그리고 인자로 들어온 방향값을 바꿔준다.
bool Player::FindDestroyDir( const Position& position , int size , OUT MyDirection* dir )
{
    bool result = false;
    Position checkPos;
    MyDirection checkDir;
    //일단 역방향으로 준다.
	//최근에 추적한 방향이 제대로 찍었을 확률이 높다고 판단
    switch( m_FindDir )
    {
        case UP:
            checkDir = DOWN;
            break;
        case DOWN:
            checkDir = UP;
            break;
        case LEFT:
            checkDir = RIGHT;
            break;
        case RIGHT:
            checkDir = LEFT;
            break;
        default:
            break;
    }

	//Dir을 돌면서 그 방향으로 배 사이즈만큼의 위치가 HIT로 표시되었음을 확인.
    for( int count = 0; count < DIR_MAX; ++count , checkDir = ( MyDirection )( checkDir + 1 ) )
    {
        checkPos = position;
        result = false;
        for( int i = 1; i < size; ++i )
        {
            checkPos = checkPos.dirPos( checkDir );
            if( !checkPos.isValid() ||
                m_EnemyBoard->GetBoardStatus( checkPos ) != HIT )
            {
                break;
            }
            else
            {
                for( auto hitPos : m_HitPosList )
                {
                    if( checkPos == hitPos )
                    {
                        result = true;
                        break;
                    }
                }
            }
        }
		//사이즈 만큼 돌았는데 모든 위치가 HIT이면 현 Dir이 올바른 Dir
        if( result == true)
        {
            *dir = checkDir;
            break;
        }
    }
	//Destroy로부터 적어도 어느 한 방향은 성공해야하므로 ASSERT를 걸어서 확인한다.
    _ASSERT( result );
    return result;
}

//Destroy된 방향이 확인되면 리스트에서 파괴된 배의 위치를 제외시켜준다.
bool Player::RemoveDestroyedPath( const Position& position , int size , const MyDirection& dir )
{
    Position deletePos = position;
    m_DestroyPosList.remove( deletePos );
    for( int i = 1; i < size; ++i )
    {
        deletePos = deletePos.dirPos( dir );
        m_HitPosList.remove( deletePos );
    }
    return true;
}

//네트워크 시작시 전송해야하는 ShipData 를 만드는 함수
void Player::MakeShipData()
{
    Coord curCoord;
    bool isFirstDestroyer = true;
    for( auto ship : m_MyShipList )
    {
        MyShipType type = ship->GetShipType();
        int i = 0;
        switch( type )
        {
            
            case DESTROYER:
                for( auto pos : ship->GetPos() )
                {
                    curCoord = Coord( pos.m_X , pos.m_Y );
                    if( isFirstDestroyer )
                    {
                        m_ShipData->SetShipCoord( MD_DESTROYER1 , i++ , curCoord);
                    }
                    else
                    {
                        m_ShipData->SetShipCoord( MD_DESTROYER2 , i++ , curCoord );
                    }
                }
                isFirstDestroyer = false;
                break;
            case CRUISER:
                for( auto pos : ship->GetPos() )
                {
                    curCoord = Coord( pos.m_X , pos.m_Y );
                    m_ShipData->SetShipCoord( MD_CRUISER , i++ , curCoord );
                }
                break;
            case BATTLESHIP:
                for( auto pos : ship->GetPos() )
                {
                    curCoord = Coord( pos.m_X , pos.m_Y );
                    m_ShipData->SetShipCoord( MD_BATTLESHIP , i++ , curCoord );
                }
                break;
            case AIRCRAFT:
                for( auto pos : ship->GetPos() )
                {
                    curCoord = Coord( pos.m_X , pos.m_Y );
                    m_ShipData->SetShipCoord( MD_AIRCRAFT , i++ , curCoord );
                }
                break;
            default:
                break;
        }
    }

}

//배를 배치시킬 최적의 위치를 찾는 함수
//맵의 확률을 계산한뒤 가장 작은 확률을 가진 위치와 방향으로 
//주어진 포인터 인자를 변경한다.

void Player::FindBestSetupPos( OUT Position* setupPos , OUT MyDirection* setupDir , int shipSize )
{
    Position curPos;
    MyDirection curDir;
	int minProb = BIG_PROB - 1;
    int curProb = 0;
    CalculateBoard();
    for( int x = 0; x < MAP_WIDTH; ++x )
    {
        for( int y = 0; y < MAP_HEIGHT; ++y )
        {
            for( int i = 0; i < DIR_MAX; ++i )
            {
                curPos = Position( x , y );
                curDir = ( MyDirection) i;
				//현재 위치와 방향으로 배를 놓았을때 그 위치들의 확률총합을 구한다.
				//이때 산술적으로 확률계산을 하면 배가 한쪽으로 몰리게 되므로 
				//적절한 분산을 위한 랜덤 보정치를 부여한다.
                curProb = SumProbforShip( curPos , curDir , shipSize ) + rand() % ( MAGIC_NUM );
                //총합이 이전 최소값보다 적으면 최소값을 현재값으로 변경
				if( curProb <= minProb ) 
                {
                    *setupPos = curPos;
                    *setupDir = curDir;
                    minProb = curProb;
                }
            }
        }
    }
	//그리고 그 위치에 배를 배치해 봐야 
	//다음 배를 놓았을때 제대로된 확률계산이 가능하다.
    SetEnemyShip( *setupPos , *setupDir , shipSize );
}

//주어진 위치와 방향에 배를 놓았을때 배가 갖는 총 확률값을 리턴하는 함수.
int Player::SumProbforShip( const Position& position , const MyDirection& dir , int shipSize )
{
    Position curPos = position;
    int sumResult = 0;
    for( int i = 0; i < shipSize; ++i )
    {
        sumResult += m_EnemyBoard->GetBoardProb( curPos );
        curPos = curPos.dirPos( dir );
		//Valid하지 않은 위치가 나오면 충분히 큰값을 넣어버린다.
        if( !curPos.isValid() || m_EnemyBoard->GetBoardStatus(curPos) == MISS)
        {
			return BIG_PROB;
        }
    }
    return sumResult;
}

//적 맵에 배를 배치하는 시뮬레이션을 수행하는 함수
//배치해본다음에 초기화를 반드시 하도록 하자.
void Player::SetEnemyShip( const Position& position , const MyDirection& dir , int shipSize )
{
    Position curPos = position;
    for( int i = 0; i < shipSize; ++i )
    {
		//이미 Valid체크가 끝났기 때문에 여기서 Valid하지 않다는 판정이 나오면
		//알고리즘 자체에 문제가 있기에 확인차 ASSERT
        _ASSERT( curPos.isValid() );
        m_EnemyBoard->SetBoardStatus( curPos , MISS );
        curPos = curPos.dirPos( dir );
    }
}

