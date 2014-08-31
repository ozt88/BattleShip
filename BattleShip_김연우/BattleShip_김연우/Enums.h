#pragma once
#include "stdafx.h"

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
};

enum Direction
{
	UP ,
	DOWN ,
	LEFT ,
	RIGHT ,
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
};

enum Menu
{
	MENU_NONE,
	GAMESTART,
	GAMEQUIT,
};