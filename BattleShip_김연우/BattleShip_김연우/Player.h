// #pragma once
// #include "stdafx.h"
// #include "Enums.h"
// 
// class Ship;
// class Board;
// 
// class Player
// {
// public:
// 	Player();
// 	~Player();
// 
// 	void		InitPlayer();
// 	void		SetupShips(); // random location, random direction, check if within map bounds, ships can't overlap
// 	bool		IsValidPosition( Position setPos , int maxHp , Direction direction );
// 	void		PlaceShip( Ship* ship , Position setPos , Direction direction );
// 	Position	Attack();   //ATTACKER
// 	HitResult	SendResult( Position position );   //DEFENDER
// 	void		UpdateMyBoard( Position position , HitResult hitResult );
// 	void		UpdateEnemyBoard( Position position , HitResult hitResult );
// 	void		PrintMyBoard();
// 	void		PrintEnemyBoard();
// 	std::string GetName(){return m_Name;}
// 	void		SetName( std::string name ){m_Name = name;}
// 	bool		AllShipIsDestroyed();
// 	void		PrintShips();
// 
// 	void		CalculateBoard();
// 	bool		ShipCanOccupy( int x , int y , int shipSize , bool isVertical );
// 
// private:
// 	Board*				m_MyBoard;
// 	Board*				m_EnemyBoard;
// 	std::list <Ship*>	m_ShipList;
// 	int					m_Type;
// 	std::string			m_Name;
// };
// 


#pragma once
#include "stdafx.h"
#include "Enums.h"

class Ship;
class Board;
struct EnemyShip
{
	EnemyShip( int size , int num )
	{
		m_Size = size , m_Num = num;
	}
	int m_Size;
	int m_Num;
};

class Player
{
public:
	Player();
	~Player();

	void					InitPlayer();
	void					SetupShips();
	bool					IsValidPosition( const Position& setPos , int maxHp , const Direction& direction );

	HitResult				SendResult( const Position& position );
	void					UpdateMyBoard( const Position& position , const HitResult& hitResult );
	void					UpdateEnemyBoard( const Position& position , const HitResult& hitResult );
	Board*					GetMyBoard()
	{
		return m_MyBoard;
	}
	Board*					GetEnemyBoard()
	{
		return m_EnemyBoard;
	}
	std::wstring			GetName()
	{
		return m_Name;
	}
	void					SetName( const std::wstring& name )
	{
		m_Name = name;
	}
	std::list<Ship*>		GetShipList()
	{
		return m_MyShipList;
	}
	bool					AllShipIsDestroyed();

	//For AI
	void					CalculateBoard();
	bool					ShipCanOccupy( int x , int y , int shipSize , bool isVertical );
	void					InitEnemyShips();
	Position				Attack();
	Direction				FindBestNeighbor( const Position& pos );
	Position				FindTarget( const HitResult& hitresult );

	Position				HitFind();
	Position				MissFind();
	Position				DestroyFind( int size );
	bool					FindDestroyDir( const Position& position , int size , Direction* dir );
	bool					RemoveDestroyedPath( const Position& position , int size , const Direction& dir );

private:
	Board*					m_MyBoard;
	Board*					m_EnemyBoard;
	std::list<Ship*>		m_MyShipList;
	int						m_Type;
	std::wstring			m_Name;

	//For AI
	std::vector<EnemyShip*>	m_EnemyShipList;
	std::list<Position>		m_HitPosList;
	std::list<Position>		m_DestroyPosList;
	Position				m_Origin;
	Position				m_LastHit;
	bool					m_IsTargetMode;
	Direction				m_FindDir;
};

