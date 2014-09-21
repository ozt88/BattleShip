#pragma once
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)
#define SHIP_NUM 5
#define FONT_NAME L"Consolas"
#define FONT_SIZE 15
#define BUFFERSIZE 256
#define SERVERIPPORT "10.73.42.117", 9000

//#define SERVERIPPORT "127.0.0.1", 9001 //내컴
//#define SERVERIPPORT "10.73.43.26", 9001 //현욱



enum MyDirection
{
	UP ,
	DOWN ,
	LEFT ,
	RIGHT ,
	DIR_MAX,
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

enum MyShipType
{
	DESTROYER ,
	CRUISER ,
	BATTLESHIP ,
	AIRCRAFT ,
	SHIPTYPE_MAX,
};

enum ShipSize
{
	DESTROYER_SIZE = 2,
	CRUISER_SIZE ,
	BATTLESHIP_SIZE ,
	AIRCRAFT_SIZE ,
};

enum Menu
{
	MENU_NONE ,
	GAMESTART ,
	GAMEQUIT ,
};

enum GameState
{
	GAME_WAIT,
	GAME_ATTACK ,
	GAME_RESULT ,
	GAME_RUNNING ,
	GAME_RESET ,
	GAME_END ,
	GAME_OVER ,
	GAME_QUIT ,
};

enum AImode
{
	HUNT,
	TARGET,
};

enum GameMode
{
	SOLO,
	NETWORK,	
};

enum SystemState
{
	START_INIT,
	START_RUNNING,
	NETWORK_INIT,
	NETWORK_READY,
	NETWORK_RESET,
	NETWORK_RUNNING,
	SOLO_INIT,
	SOLO_RUNNING,
	SYSTEM_PAUSE,
	SYSTEM_QUIT,
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
	Position( const Position& other )
	{
		m_X = other.m_X;
		m_Y = other.m_Y;
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


	Position dirPos( MyDirection dir )   //현재 위치에서 dir방향에 있는 위치를 리턴 
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
		if( result.isValid())
		{
			return result;
		}
		else
		{
			return Position( -1 , -1 );
		}
	}
};

//EnemyShi 배의 종류와 갯수가 들어있는 구조체이다.
//같은 종류가 여러개 있는 경우 다루기 쉽게 하기 위해서 이렇게 만듬

struct EnemyShip
{
	EnemyShip( int size , int num )
	{
		m_Size = size , m_Num = num;
	}
	int m_Size;
	int m_Num;
};

