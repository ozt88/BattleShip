#include "stdafx.h"
#include "Ship.h"

Ship::Ship()
{
	m_HP = 0;
}

Ship::~Ship()
{
}

void Ship::AddPosition( Position addPos )
{
	for( auto positionIter : m_Pos )
	{
		if( positionIter.m_X == addPos.m_X && positionIter.m_Y == addPos.m_Y )
		{
			printf_s( "ERROR : Already Exist\n" );
			return;
		}
	}

	m_Pos.push_back( addPos );
}

HitResult Ship::HitCheck( Position hitPos )
{

	for( auto positionIter : m_Pos )
	{
		if( positionIter.m_X == hitPos.m_X && positionIter.m_Y == hitPos.m_Y )
		{
			positionIter.m_X = -1;
			positionIter.m_Y = -1;
			--m_HP;

			if( m_HP <= 0 )
			{
				return DESTROY;
			}
			else
			{
				return HIT;
			}
		}
	}

	return MISS;
}

void Ship::Print()
{
	printf_s( "%s HP : %d POS :[" , m_Name.c_str() , m_HP );
	for( auto positionIter : m_Pos )
	{
		printf_s( " (%d, %d) " , positionIter.m_X , positionIter.m_Y );
	}
	printf( "]\n" );
}

bool Ship::IsDuplicate( Position checkPos )
{

	for( auto positionIter : m_Pos )
	{
		if( positionIter.m_X == checkPos.m_X && positionIter.m_Y == checkPos.m_Y )
		{
			return true;
		}
	}
	return false;
}

bool Ship::IsDestroyed()
{
	return ( m_HP <= 0 );
}


