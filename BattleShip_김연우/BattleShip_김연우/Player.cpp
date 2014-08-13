#include "stdafx.h"
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
	std::list<Ship*> shipListFromManager;
	std::list<Ship*>::iterator iterPos = m_ShipList.begin();
	m_ShipList.push_back( new AirCraft() );
	m_ShipList.push_back( new BattleShip() );
	m_ShipList.push_back( new Cruiser() );
	m_ShipList.push_back( new Destroyer() );
	m_ShipList.push_back( new Destroyer() );
	//shipList.insert( iterPos , shipListFromManager.begin() , shipListFromManager.end() );
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
	srand( time( NULL ) );
	int maxHeight = m_MyBoard->GetMaxHeight();
	int maxWidth = m_MyBoard->GetMaxWidth();
	int maxHp = 0;
	Position setPos;
	Direction direction = UP;

	for( auto iterPos : m_ShipList )
	{
		maxHp = iterPos->GetMaxHP();
		do
		{
			direction = ( Direction )( rand() % 4 );

			setPos.m_X = rand() % maxWidth;
			setPos.m_Y = rand() % maxHeight;
		} while( !IsValidPosition( setPos , iterPos->GetMaxHP() , direction ) );
		PlaceShip( *iterPos , setPos , direction );
	}
}


void Player::PlaceShip( Ship& ship , Position setPos , Direction direction )
{
	for( int i = 0; i < ship.GetMaxHP(); i++ )
	{
		ship.AddPosition( setPos );

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

void Player::PrintShips()
{
	for( auto iterPos : m_ShipList )
	{
		iterPos->Print();
	}
}

Position Player::Attack()
{
	Position position;
	int posX = 0;
	int posY = 0;
	do
	{
		posX = rand() % m_EnemyBoard->GetMaxWidth();
		posY = rand() % m_EnemyBoard->GetMaxHeight();
	} while( !m_EnemyBoard->IsWater( posX , posY ) );
	position.m_X = posX;
	position.m_Y = posY;
	return position;
}

HitResult Player::SendResult( Position position )
{
	HitResult hitResult = NONE;

	for( auto ship : m_ShipList )
	{
		hitResult = ship->HitCheck( position );
		if( hitResult != MISS )
		{
			break;
		}
	}

	return hitResult;
}

void Player::SetMyBoard( Position position , HitResult hitResult )
{
	m_MyBoard->SetBoard( position , hitResult );
}

void Player::SetEnemyBoard( Position position , HitResult hitResult )
{
	m_EnemyBoard->SetBoard( position , hitResult );
}

bool Player::AllShipIsDestroyed()
{
	for( auto ship : m_ShipList )
	{
		if( !ship->IsDestroyed() )
		{
			return false;
		}
	}
	return true;
}

void Player::GetMyBoard()
{
	m_MyBoard->PrintBoard();
}

