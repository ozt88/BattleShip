#include "Player.h"
#include "Board.h"
#include "AirCraft.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"


Player::Player()
{
	m_Name = "Player";
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
	Position attackPos;
	do
	{
		attackPos.m_X = rand() % m_EnemyBoard->GetMaxWidth();
		attackPos.m_Y = rand() % m_EnemyBoard->GetMaxHeight();
	} while( !m_EnemyBoard->IsWater( attackPos ) );
	return attackPos;
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

void Player::PrintMyBoard()
{
	m_MyBoard->PrintBoard();
}

void Player::InitPlayer()
{
	m_MyBoard->InitBoard();
	//m_EnemyBoard->InitBoard();
	SetupShips();
}

