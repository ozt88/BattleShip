#pragma once
#include "Include.h"
#include "Enum.h"

class Ship;
class Board;
class Player
{
public:
	Player();
	~Player();

	void					InitPlayer();
	void					SetupShips();
	bool					IsValidPosition( const Position& setPos , int maxHp , const MyDirection& direction );

	HitResult				SendResult( const Position& position );
	void					UpdateMyBoard( const Position& position , const HitResult& hitResult );
	void					UpdateEnemyBoard( const Position& position , const HitResult& hitResult );

	Board*					GetMyBoard() {return m_MyBoard;}
	Board*					GetEnemyBoard() {return m_EnemyBoard;}
	std::wstring			GetName(){return m_Name;}
	void					SetName( const std::wstring& name ){m_Name = name;}
	std::list<Ship*>		GetShipList() {return m_MyShipList; }
	bool					AllShipIsDestroyed();

	//For AI
	void					CalculateBoard();
	bool					ShipCanOccupy( int x , int y , int shipSize , bool isVertical );
	void					InitEnemyShips();
	Position				Attack();
	MyDirection				FindBestNeighbor( const Position& pos );
	Position				FindTarget( const HitResult& hitresult );
	
	Position				HitFind();
	Position				MissFind();
	Position				DestroyFind( int size );
	bool					CheckMissDir(OUT Position* nextPos);
	bool					FindDestroyDir( const Position& position , int size , OUT MyDirection* dir );
	bool					RemoveDestroyedPath( const Position& position , int size , const MyDirection& dir );

	//NETWORK
	void					MakeShipData();
	ShipData*				GetShipData(){ return m_ShipData; }

private:
	Board*					m_MyBoard;
	Board*					m_EnemyBoard;
	std::list<Ship*>		m_MyShipList;
	ShipData*				m_ShipData;
	int						m_Type;
	std::wstring			m_Name;

	//For AI
	std::vector<EnemyShip*>	m_EnemyShipList;
	std::list<Position>		m_HitPosList;
	std::list<Position>		m_DestroyPosList;
	Position				m_Origin;
	Position				m_LastHit;
	AImode					m_AImode;
	MyDirection				m_FindDir;
};

