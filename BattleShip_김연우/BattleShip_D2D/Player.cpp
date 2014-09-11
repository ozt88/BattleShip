#include "Player.h"
#include "GameScene.h"
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

	m_ShipList.push_back( new AirCraft( 1 ) );
	m_ShipList.push_back( new BattleShip( 2 ) );
	m_ShipList.push_back( new Cruiser( 3 ) );
	m_ShipList.push_back( new Destroyer( 4 ) );
	m_ShipList.push_back( new Destroyer( 5 ) );

	//std::list<Ship*> shipListFromManager;
	//std::list<Ship*>::iterator iterPos = m_ShipList.begin();
	//m_ShipList.insert( iterPos , shipListFromManager.begin() , shipListFromManager.end() );
}


Player::~Player()
{
 	delete m_MyBoard;
 	delete m_EnemyBoard;
	for( auto ship : m_ShipList )
	{
		delete ship;
		ship = nullptr;
	}
	m_ShipList.clear();
}


void Player::SetupShips()
{
	int maxHeight = m_MyBoard->GetMaxHeight();
	int maxWidth = m_MyBoard->GetMaxWidth();
	Position setPos;
	Direction direction = UP;
	for( auto shipIter : m_ShipList )
	{
		shipIter->ShipInit();
	}

	for( auto shipIter : m_ShipList )
	{
		do
		{
			direction = ( Direction )( rand() % 4 );
			setPos.m_X = rand() % maxWidth;
			setPos.m_Y = rand() % maxHeight;
		} while( !IsValidPosition( setPos , shipIter->GetMaxHP() , direction ) );
		shipIter->PlaceShip( setPos , direction );
	}
}



bool Player::IsValidPosition( Position setPos , int maxHp , Direction direction )
{
	for( int i = 0; i < maxHp; i++ )
	{
		if( m_MyBoard->IsOutOfBoard( setPos ) )
		{
			return false;
		}

		for( auto iterPos : m_ShipList )
		{
			if( iterPos->IsDuplicate( setPos ) )
			{
				return false;
			}
		}

		switch( direction )
		{
			case UP:
				setPos.m_Y--;
				break;
			case DOWN:
				setPos.m_Y++;
				break;
			case LEFT:
				setPos.m_X--;
				break;
			case RIGHT:
				setPos.m_X++;
				break;
		}

	}
	return true;
}



Position Player::Attack()
{
	CalculateBoard();
	Position maxProbPos;
	Position curPos;
	int	maxProb = 0;
	for( int y = 0; y < m_EnemyBoard->GetMaxHeight(); ++y )
	{
		for( int x = 0; x < m_EnemyBoard->GetMaxWidth(); ++x )
		{
			curPos = Position( x , y );
			if( m_EnemyBoard->IsWater( curPos ) && m_EnemyBoard->GetBoardProb( curPos ) > maxProb )
			{
				maxProbPos = curPos;
				maxProb = m_EnemyBoard->GetBoardProb( maxProbPos );
			}
		}
	}
	return maxProbPos;
}

HitResult Player::SendResult( Position position )
{
	HitResult hitResult = WATER;

	for( auto shipIter : m_ShipList )
	{
		hitResult = shipIter->HitCheck( position );
		if( hitResult != MISS )
		{
			break;
		}
	}

	return hitResult;
}

void Player::UpdateMyBoard( Position position , HitResult hitResult )
{
	m_MyBoard->MapUpdate( position , hitResult );
}

void Player::UpdateEnemyBoard( Position position , HitResult hitResult )
{
	m_EnemyBoard->MapUpdate( position , hitResult );
}

bool Player::AllShipIsDestroyed()
{
	for( auto shipIter : m_ShipList )
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
}



void Player::CalculateBoard()
{
	m_EnemyBoard->ClearProb();
	for( auto ship : m_ShipList )
	{
		for( int y = 0; y < m_EnemyBoard->GetMaxHeight(); ++y )
		{
			for( int x = 0; x < m_EnemyBoard->GetMaxWidth(); ++x )
			{
				if( ShipCanOccupy( x , y , ship->GetMaxHP() , false ) )
				{
					m_EnemyBoard->IncreaseProbablity( x , y , ship->GetMaxHP() , false );
				}
				if( ShipCanOccupy( x , y , ship->GetMaxHP() , true ) )
				{
					m_EnemyBoard->IncreaseProbablity( x , y , ship->GetMaxHP() , true );
				}
			}
		}
	}
}

bool Player::ShipCanOccupy( int x , int y , int shipSize , bool isVertical )
{
	int head = isVertical ? y : x;
	int end = head + shipSize - 1;
	int max = isVertical ? m_EnemyBoard->GetMaxHeight() : m_EnemyBoard->GetMaxWidth();

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
