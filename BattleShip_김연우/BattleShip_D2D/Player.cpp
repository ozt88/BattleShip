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

Player::Player()
{
	m_Name = L"Player";
	m_MyBoard = new Board();
	m_EnemyBoard = new Board();
	m_ShipData = new ShipData();
	m_MyShipList.push_back( new AirCraft( 1 ) );
	m_MyShipList.push_back( new BattleShip( 2 ) );
	m_MyShipList.push_back( new Cruiser( 3 ) );
	m_MyShipList.push_back( new Destroyer( 4 ) );
	m_MyShipList.push_back( new Destroyer( 5 ) );


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


void Player::SetupShips()
{
	Position setPos;
	MyDirection direction = UP;
	for( auto shipIter : m_MyShipList )
	{
		shipIter->ShipInit();
	}

	for( auto shipIter : m_MyShipList )
	{
		do
		{
// 			direction = ( MyDirection )( rand() % 4 );
// 			setPos.m_X = rand() % MAP_WIDTH;
// 			setPos.m_Y = rand() % MAP_HEIGHT;
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
		CalculateBoard();	//일단 맵의 확률을 계산
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

void Player::UpdateMyBoard( const Position& position , const HitResult& hitResult )
{
	m_MyBoard->MapUpdate( position , hitResult );
}



void Player::UpdateEnemyBoard( const Position& position , const HitResult& hitResult )
{
	m_EnemyBoard->MapUpdate( position , hitResult );
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
		GM->GetEnemyUI()->MakeDestroySprite( destroySize );
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

void Player::InitPlayer()
{
	m_MyBoard->InitBoard();
	m_EnemyBoard->InitBoard();
	SetupShips();
	InitEnemyShips();
	MakeShipData();
	m_AImode = HUNT;
	m_LastHit = Position();
	m_Origin = Position();
	m_FindDir = UP;
	m_DestroyPosList.clear();
	m_HitPosList.clear();
}


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

void Player::CalculateBoard()
{
	m_EnemyBoard->ClearProb();
	for( auto enemyShip : m_EnemyShipList )
	{
		for( int num = 0; num < enemyShip->m_Num; ++num )
		{
			for( int y = 0; y < MAP_HEIGHT; ++y )
			{
				for( int x = 0; x < MAP_WIDTH; ++x )
				{
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
 	//m_EnemyBoard->ScaleBoardProb( Position( 0 , 0 ) , 2 );
 	//m_EnemyBoard->ScaleBoardProb( Position( MAP_WIDTH - 1 , 0 ) , 2 );
 	//m_EnemyBoard->ScaleBoardProb( Position( 0 , MAP_HEIGHT - 1 ) , 2 );
 	//m_EnemyBoard->ScaleBoardProb( Position( MAP_WIDTH - 1 , MAP_HEIGHT - 1 ) , 2 );
}

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
			m_EnemyBoard->ScaleBoardProb( curPos , 2 );
		}
	}
	return ( MyDirection )bestDir;
}

Position Player::FindTarget( const HitResult& hitresult )
{
	Position resultPos;
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

Position Player::HitFind()
{
	m_HitPosList.push_back( m_LastHit );
	Position nextPos = m_LastHit.dirPos( m_FindDir );
	if( nextPos.isValid() && m_EnemyBoard->IsWater( nextPos ) )
	{
		HitResult result = m_EnemyBoard->GetBoardStatus( nextPos );
		_ASSERT( result == WATER );
		return nextPos;
	}
	return MissFind();
}

Position Player::MissFind()
{
	Position nextPos;
	bool findNextPos = false;
	for( auto hitPos : m_HitPosList )
	{
		if( findNextPos = CheckMissDir( &nextPos ) )
		{
			break;
		}
		m_Origin = hitPos;
	}
	
	if( !findNextPos )
	{
		m_AImode = HUNT;
		nextPos = Attack();
	}


	HitResult result = m_EnemyBoard->GetBoardStatus( nextPos );
	_ASSERT( result == WATER );
	
	return nextPos;
}

Position Player::DestroyFind( int size )
{
	m_DestroyPosList.push_back( m_LastHit );
	Position curPos = m_LastHit;
	MyDirection destroyDir = m_FindDir;
	FindDestroyDir( curPos , size , &destroyDir );
	RemoveDestroyedPath( curPos , size , destroyDir );

	if( m_HitPosList.empty() )
	{
		m_AImode = HUNT;
		return Attack();
	}
	else
	{
		m_Origin = m_HitPosList.front();
		return MissFind();
	}
}

bool Player::FindDestroyDir( const Position& position , int size , MyDirection* dir )
{
	bool result = false;
	Position checkPos;
	MyDirection checkDir;
	//일단 역방향으로 준다.
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
		if( result == true)
		{
			*dir = checkDir;
			break;
		}
	}
	_ASSERT( result );
	return result;
}

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

bool Player::CheckMissDir(OUT Position* nextPos)
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

void Player::FindBestSetupPos( OUT Position* setupPos , OUT MyDirection* setupDir , int shipSize )
{
	Position curPos;
	MyDirection curDir;
	int minProb = 200;
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
				curProb = SumProbforShip( curPos , curDir , shipSize ) + rand() % ( MAGIC_NUM );
				if( curProb <= minProb ) 
				{
					*setupPos = curPos;
					*setupDir = curDir;
					minProb = curProb;
				}
			}
		}
	}
	SetEnemyShip( *setupPos , *setupDir , shipSize );
}

int Player::SumProbforShip( const Position& position , const MyDirection& dir , int shipSize )
{
	Position curPos = position;
	int sumResult = 0;
	for( int i = 0; i < shipSize; ++i )
	{
		sumResult += m_EnemyBoard->GetBoardProb( curPos );
		curPos = curPos.dirPos( dir );
		if( !curPos.isValid() || m_EnemyBoard->GetBoardStatus(curPos) == MISS)
		{
			return 1000;
		}
	}
	return sumResult;
}

void Player::SetEnemyShip( const Position& position , const MyDirection& dir , int shipSize )
{
	Position curPos = position;
	for( int i = 0; i < shipSize; ++i )
	{
		_ASSERT( curPos.isValid() );
		m_EnemyBoard->SetBoardStatus( curPos , MISS );
		curPos = curPos.dirPos( dir );
	}
}

