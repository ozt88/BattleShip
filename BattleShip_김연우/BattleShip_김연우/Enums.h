#pragma once
#include "stdafx.h"

#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define SHIP_NUM 5


enum Direction
{
	UP ,
	DOWN ,
	LEFT ,
	RIGHT ,
	DIR_MAX ,
};

enum HitResult
{
	WATER ,
	HIT ,
	MISS ,
	DESTROY ,
	DESTROY_AIRCRAFT ,
	DESTROY_BATTLESHIP ,
	DESTROY_CRUISER ,
	DESTROY_DESTROYER ,
};

enum ShipType
{
	DESTROYER ,
	CRUISER ,
	BATTLESHIP ,
	AIRCRAFT ,
	SHIPTYPE_MAX ,
};

enum Menu
{
	MENU_NONE ,
	GAMESTART ,
	GAMEQUIT ,
};

enum GameState
{
	RUNNING ,
	END ,
	RESET ,
	EXIT ,
};

struct Position
{
	int m_X;
	int m_Y;
	Position()
	{
		m_X = -1;
		m_Y = -1;
	}
	Position( int _x , int _y )
	{
		m_X = _x;
		m_Y = _y;
	}

	bool operator==( Position other )
	{
		return ( this->m_X == other.m_X && this->m_Y == other.m_Y );
	}
	bool operator!=( Position other )
	{
		return ( this->m_X != other.m_X || this->m_Y != other.m_Y );
	}
	bool isValid()
	{
		return ( m_Y < MAP_HEIGHT && 0 <= m_Y && m_X < MAP_WIDTH && 0 <= m_X );
	}

	Position dirPos( Direction dir )
	{
		Position result;
		switch( dir )
		{
			case UP:
				result = Position( this->m_X , this->m_Y - 1 );
				break;
			case DOWN:
				result = Position( this->m_X , this->m_Y + 1 );
				break;
			case LEFT:
				result = Position( this->m_X - 1 , this->m_Y );
				break;
			case RIGHT:
				result = Position( this->m_X + 1 , this->m_Y );
				break;
			default:
				break;
		}
		if( result.isValid() )
		{
			return result;
		}
		else
		{
			return Position( -1 , -1 );
		}
	}
};

#define SafeDelete(x) {if(x != nullptr){delete x; x = nullptr;}}
