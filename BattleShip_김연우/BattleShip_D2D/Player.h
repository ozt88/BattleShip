/************************************************************************/
/*
Class:		Player

설명:		게임에 참여하는 플레이어의 클래스
			Ship 들과 자신과 적의 Board 정보를 가지고 있다.
			Board정보에 기반하여 Ship을 배치할 수 있다.
			알맞은 위치를 판단하여 타격할 수 있다.
			공격을 받았을때 자신의 맵 정보를 읽어 결과를 전송할 수 있다.

추가기능:
*/
/************************************************************************/
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

	virtual void			InitPlayer();
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
	void					FindBestSetupPos( OUT Position* setupPos , OUT MyDirection* setupDir , int shipSize );
	int						SumProbforShip(const Position& positon, const MyDirection& dir, int shipSize);
	void					SetEnemyShip( const Position& positon , const MyDirection& dir , int shipSize );
	
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

