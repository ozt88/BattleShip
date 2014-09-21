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
	bool					TryOtherDirection(OUT Position* nextPos);
	bool					FindDestroyDir( const Position& position , int size , OUT MyDirection* dir );
	bool					RemoveDestroyedPath( const Position& position , int size , const MyDirection& dir );
	void					FindBestSetupPos( OUT Position* setupPos , OUT MyDirection* setupDir , int shipSize );
	int						SumProbforShip(const Position& positon, const MyDirection& dir, int shipSize);
	void					SetEnemyShip( const Position& positon , const MyDirection& dir , int shipSize );
	
	//NETWORK
	void					MakeShipData();
	ShipData*				GetShipData(){ return m_ShipData; }



private:
	Board*					m_MyBoard;		//나의 전장 상태를 표시하는 보드
	Board*					m_EnemyBoard;	//적의 전장 상태를 표시하는 보드
	std::list<Ship*>		m_MyShipList;	//내가 가진 배들의 리스트
	ShipData*				m_ShipData;		//내 배들의 위치정보
	int						m_Type;			//차후 AI와 일반 Player구분하기 위한 플레그
	std::wstring			m_Name;			

	//For AI

	std::vector<EnemyShip*>	m_EnemyShipList;	//적의 배 정보 리스트
	std::list<Position>		m_HitPosList;		//유효한 맞춘 위치 리스트
	std::list<Position>		m_DestroyPosList;	//유효한 파괴 위치 리스트
	Position				m_Origin;			//추적의 시작점
	Position				m_LastHit;			//추적시 마지막으로 때린 위치
	AImode					m_AImode;			//HUNT or TARGET
	MyDirection				m_FindDir;			//추적하는 방향
};

