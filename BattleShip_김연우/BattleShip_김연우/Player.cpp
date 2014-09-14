// #include "stdafx.h"
// #include "Player.h"
// #include "Board.h"
// #include "AirCraft.h"
// #include "BattleShip.h"
// #include "Cruiser.h"
// #include "Destroyer.h"
// 
// 
// Player::Player()
// {
// 	m_Name = "Player";
// 	m_MyBoard = new Board;
// 	m_EnemyBoard = new Board;
// 	m_ShipList.push_back( new AirCraft() );
// 	m_ShipList.push_back( new BattleShip() );
// 	m_ShipList.push_back( new Cruiser() );
// 	m_ShipList.push_back( new Destroyer() );
// 	m_ShipList.push_back( new Destroyer() );
// // 	std::list<Ship*> shipListFromManager;
// // 	std::list<Ship*>::iterator iterPos = m_ShipList.begin();
// //	shipList.insert( iterPos , shipListFromManager.begin() , shipListFromManager.end() );
// }
// 
// 
// Player::~Player()
// {
// 	delete m_MyBoard;
// 	delete m_EnemyBoard;
// 	for( auto ship : m_ShipList )
// 	{
// 		delete ship;
// 		ship = nullptr;
// 	}
// 	m_ShipList.clear();
// }
// 
// void Player::SetupShips()
// {
// 	int maxHeight = m_MyBoard->GetMaxHeight();
// 	int maxWidth = m_MyBoard->GetMaxWidth();
// 	Position setPos;
// 	Direction direction = UP;
// 
// 	for( auto shipIter : m_ShipList )
// 	{
// 		shipIter->ShipInit();
// 		do
// 		{
// 			direction = ( Direction )( rand() % 4 );
// 			setPos.m_X = rand() % maxWidth;
// 			setPos.m_Y = rand() % maxHeight;
// 		} while( !IsValidPosition(setPos , shipIter->GetMaxHP() , direction ) );
// 		PlaceShip( shipIter , setPos , direction );
// 	}
// }
// 
// 
// void Player::PlaceShip( Ship* ship , Position setPos , Direction direction )
// {
// 	if( ship == nullptr )
// 	{
// 		return;
// 	}
// 
// 	for( int i = 0; i < ship->GetMaxHP(); i++ )
// 	{
// 		ship->AddPosition( setPos );
// 
// 		switch( direction )
// 		{
// 			case UP:
// 				setPos.m_Y--;
// 				break;
// 			case DOWN:
// 				setPos.m_Y++;
// 				break;
// 			case LEFT:
// 				setPos.m_X--;
// 				break;
// 			case RIGHT:
// 				setPos.m_X++;
// 				break;
// 		}
// 	}
// }
// 
// bool Player::IsValidPosition( Position setPos , int maxHp , Direction direction )
// {
// 	for( int i = 0; i < maxHp; i++ )
// 	{
// 		if( m_MyBoard->IsOutOfBoard( setPos ) )
// 		{
// 			return false;
// 		}
// 
// 		for( auto iterPos : m_ShipList )
// 		{
// 			if( iterPos->IsDuplicate( setPos ) )
// 			{
// 				return false;
// 			}
// 		}
// 
// 		switch( direction )
// 		{
// 			case UP:
// 				setPos.m_Y--;
// 				break;
// 			case DOWN:
// 				setPos.m_Y++;
// 				break;
// 			case LEFT:
// 				setPos.m_X--;
// 				break;
// 			case RIGHT:
// 				setPos.m_X++;
// 				break;
// 		}
// 
// 	}
// 	return true;
// }
// 
// void Player::PrintShips()
// {
// 	for( auto shipIter : m_ShipList )
// 	{
// 		shipIter->Print();
// 	}
// }
// 
// Position Player::Attack()
// {
// 	CalculateBoard();
// 	Position maxProbPos;
// 	Position curPos;
// 	int	maxProb = 0;
// 	for( int y = 0; y < m_EnemyBoard->GetMaxHeight(); ++y )
// 	{
// 		for( int x = 0; x < m_EnemyBoard->GetMaxWidth(); ++x )
// 		{
// 			curPos = Position( x , y );
// 			if( m_EnemyBoard->IsWater( curPos ) && m_EnemyBoard->GetBoardProb( curPos ) > maxProb )
// 			{
// 				maxProbPos = curPos;
// 				maxProb = m_EnemyBoard->GetBoardProb( maxProbPos );
// 			}
// 		}
// 	}
// 	return maxProbPos;
// }
// 
// HitResult Player::SendResult( Position position )
// {
// 	HitResult hitResult = WATER;
// 
// 	for( auto shipIter : m_ShipList )
// 	{
// 		hitResult = shipIter->HitCheck( position );
// 		if( hitResult != MISS )
// 		{
// 			break;
// 		}
// 	}
// 
// 	return hitResult;
// }
// 
// void Player::UpdateMyBoard( Position position , HitResult hitResult )
// {
// 	m_MyBoard->MapUpdate( position , hitResult );
// }
// 
// void Player::UpdateEnemyBoard( Position position , HitResult hitResult )
// {
// 	m_EnemyBoard->MapUpdate( position , hitResult );
// 	CalculateBoard();
// }
// 
// bool Player::AllShipIsDestroyed()
// {
// 	for( auto shipIter : m_ShipList )
// 	{
// 		if( !shipIter->IsDestroyed() )
// 		{
// 			return false;
// 		}
// 	}
// 	return true;
// }
// 
// void Player::PrintMyBoard()
// {
// 	m_MyBoard->PrintBoard();
// }
// 
// void Player::InitPlayer()
// {
// 	m_MyBoard->InitBoard();
// 	m_EnemyBoard->InitBoard();
// 	SetupShips();
// }
// 
// void Player::CalculateBoard()
// {
// 	m_EnemyBoard->ClearProb();
// 	for( auto ship : m_ShipList )
// 	{
// 		for( int y = 0; y < m_EnemyBoard->GetMaxHeight(); ++y )
// 		{
// 			for( int x = 0; x < m_EnemyBoard->GetMaxWidth(); ++x )
// 			{
// 				if( ShipCanOccupy( x , y , ship->GetMaxHP() , false ) )
// 				{
// 					m_EnemyBoard->IncreaseProbablity( x , y , ship->GetMaxHP() , false );
// 				}
// 				if( ShipCanOccupy( x , y , ship->GetMaxHP() , true ) )
// 				{
// 					m_EnemyBoard->IncreaseProbablity( x , y , ship->GetMaxHP() , true );
// 				}
// 			}
// 		}
// 	}
// }
// 
// bool Player::ShipCanOccupy( int x , int y , int shipSize , bool isVertical )
// {
// 	int head = isVertical ? y : x;
// 	int end = head + shipSize - 1;
// 	int max = isVertical ? m_EnemyBoard->GetMaxHeight() : m_EnemyBoard->GetMaxWidth();
// 	
// 	if( end > max - 1 ) return false;
// 	Position checkPos;
// 	for( int i = head; i <= end; ++i )
// 	{
// 		checkPos = isVertical ? Position( x , i ) : Position( i , y );
// 		if( m_EnemyBoard->GetBoardStatus( checkPos.m_X , checkPos.m_Y ) == MISS )
// 		{
// 			return false;
// 		}
// 	}
// 	return true;
// }
// 
// void Player::PrintEnemyBoard()
// {
// 	m_EnemyBoard->PrintBoard();
// }
// 
// 
// 
// 
// 

#include "stdafx.h"
#include "Player.h"
#include "Board.h"
#include "AirCraft.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"

Player::Player()
{
	m_Name = L"Player";
	m_MyBoard = new Board;
	m_EnemyBoard = new Board;

	m_MyShipList.push_back( new AirCraft() );
	m_MyShipList.push_back( new BattleShip() );
	m_MyShipList.push_back( new Cruiser() );
	m_MyShipList.push_back( new Destroyer() );
	m_MyShipList.push_back( new Destroyer() );


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
	SafeDelete( m_MyBoard );
	SafeDelete( m_EnemyBoard );
	for( auto ship : m_MyShipList )
	{
		SafeDelete( ship );
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
	Direction direction = UP;
	for( auto shipIter : m_MyShipList )
	{
		shipIter->ShipInit();
	}

	for( auto shipIter : m_MyShipList )
	{
		do
		{
			direction = ( Direction )( rand() % 4 );
			setPos.m_X = rand() % MAP_WIDTH;
			setPos.m_Y = rand() % MAP_HEIGHT;
		} while( !IsValidPosition( setPos , shipIter->GetMaxHP() , direction ) );
		shipIter->PlaceShip( setPos , direction );
	}
}



bool Player::IsValidPosition( const Position& setPos , int maxHp , const Direction& direction )
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
	std::vector<Position> maxPosVector;
	if( !m_IsTargetMode )
	{
		CalculateBoard();
		Position curPos;
		int	maxProb = 0;
		for( int y = 0; y < MAP_HEIGHT; ++y )
		{
			for( int x = 0; x < MAP_WIDTH; ++x )
			{
				curPos = Position( x , y );
				if( m_EnemyBoard->IsWater( curPos ) && m_EnemyBoard->GetBoardProb( curPos ) > maxProb )
				{
					maxProbPos = curPos;
					maxProb = m_EnemyBoard->GetBoardProb( maxProbPos );
				}
			}
		}
		maxPosVector.push_back( maxProbPos );
		for( int y = 0; y < MAP_HEIGHT; ++y )
		{
			for( int x = 0; x < MAP_WIDTH; ++x )
			{
				curPos = Position( x , y );
				if( maxProb == m_EnemyBoard->GetBoardProb( curPos ) )
				{
					maxPosVector.push_back( Position( x , y ) );
				}
			}
		}
		if( maxPosVector.size() > 1 ) maxProbPos = maxPosVector[rand() % maxPosVector.size()];
	}
	else
	{
		maxProbPos = FindTarget( m_EnemyBoard->GetBoardStatus( m_LastHit.m_X , m_LastHit.m_Y ) );
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
	int destroySize = 0;
	m_LastHit = position;

	if( hitResult == HIT )
	{
		if( !m_IsTargetMode )
		{
			m_Origin = position;
			m_IsTargetMode = true;
			m_FindDir = FindBestNeighbor( m_Origin );
		}
	}
	else if( hitResult != MISS )
	{
		switch( hitResult )
		{
			case DESTROY_AIRCRAFT:
				destroySize = 5;
				break;
			case DESTROY_BATTLESHIP:
				destroySize = 4;
				break;
			case DESTROY_CRUISER:
				destroySize = 3;
				break;
			case DESTROY_DESTROYER:
				destroySize = 2;
				break;
			default:
				break;
		}
		for( auto enemyShip : m_EnemyShipList )
		{
			if( enemyShip->m_Size == destroySize )
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
	m_IsTargetMode = false;
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

}

bool Player::ShipCanOccupy( int x , int y , int shipSize , bool isVertical )
{
	int head = isVertical ? y : x;
	int end = head + shipSize - 1;
	int max = isVertical ? MAP_HEIGHT : MAP_WIDTH;

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


Direction Player::FindBestNeighbor( const Position& pos )
{
	std::vector<Position> neighbors;
	Position neighbor = pos;
	int bestDir = 0;
	int bestProb = 0;
	for( int i = 0; i < DIR_MAX; ++i )
	{
		neighbors.push_back( neighbor.dirPos( ( Direction )i ) );
	}

	for( size_t i = 0; i < neighbors.size(); ++i )
	{
		Position curPos = neighbors[i];
		if( curPos.isValid()
			&& m_EnemyBoard->GetBoardProb( curPos ) > bestProb )
		{
			bestDir = i;
			bestProb = m_EnemyBoard->GetBoardProb( curPos );
			m_EnemyBoard->ScaleBoardProb( curPos , 2 );
		}
	}
	return ( Direction )bestDir;
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
			resultPos = DestroyFind( 5 );
			break;
		case DESTROY_BATTLESHIP:
			resultPos = DestroyFind( 4 );
			break;
		case DESTROY_CRUISER:
			resultPos = DestroyFind( 3 );
			break;
		case DESTROY_DESTROYER:
			resultPos = DestroyFind( 2 );
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
		return nextPos;
	}
	return MissFind();
}

Position Player::MissFind()
{
	Position nextPos;
	bool isValid = false;
	for( int i = 0; i < DIR_MAX; ++i )
	{
		m_FindDir = ( Direction )( ( m_FindDir + 1 ) % DIR_MAX );
		nextPos = m_Origin.dirPos( m_FindDir );
		if( nextPos.isValid() && m_EnemyBoard->IsWater( nextPos ) )
		{
			isValid = true;
			break;
		}
	}
	if( !isValid )
	{
		_ASSERT( !m_HitPosList.empty() );
		for( auto hitPos : m_HitPosList )
		{
			if( hitPos != m_Origin )
			{
				m_Origin = hitPos;
				break;
			}
		}
	}

	return nextPos;
}

Position Player::DestroyFind( int size )
{
	m_DestroyPosList.push_back( m_LastHit );
	Position curPos = m_LastHit;
	Direction destroyDir = m_FindDir;
	_ASSERT( FindDestroyDir( curPos , size , &destroyDir ) );
	_ASSERT( RemoveDestroyedPath( curPos , size , destroyDir ) );

	if( m_HitPosList.empty() )
	{
		m_IsTargetMode = false;
		return Attack();
	}
	else
	{
		m_Origin = m_HitPosList.front();
		return MissFind();
	}
}

bool Player::FindDestroyDir( const Position& position , int size , Direction* dir )
{
	bool result = false;
	Position checkPos;
	Direction checkDir;
	for( checkDir = UP; checkDir < DIR_MAX; checkDir = ( Direction )( checkDir + 1 ) )
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
		if( result == true )
		{
			*dir = checkDir;
			break;
		}
	}

	return result;
}

bool Player::RemoveDestroyedPath( const Position& position , int size , const Direction& dir )
{
	Position deletePos = position;
	m_DestroyPosList.remove( deletePos );
	for( int i = 1; i < size; ++i )
	{
		deletePos = deletePos.dirPos( dir );
		if( !deletePos.isValid() ||
			m_EnemyBoard->GetBoardStatus( deletePos ) != HIT )
		{
			return false;
		}
		m_HitPosList.remove( deletePos );
	}
	return true;
}

