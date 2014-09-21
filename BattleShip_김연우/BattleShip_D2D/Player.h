/************************************************************************/
/*
Class:		Player

����:		���ӿ� �����ϴ� �÷��̾��� Ŭ����
			Ship ��� �ڽŰ� ���� Board ������ ������ �ִ�.
			Board������ ����Ͽ� Ship�� ��ġ�� �� �ִ�.
			�˸��� ��ġ�� �Ǵ��Ͽ� Ÿ���� �� �ִ�.
			������ �޾����� �ڽ��� �� ������ �о� ����� ������ �� �ִ�.

�߰����:
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
	Board*					m_MyBoard;		//���� ���� ���¸� ǥ���ϴ� ����
	Board*					m_EnemyBoard;	//���� ���� ���¸� ǥ���ϴ� ����
	std::list<Ship*>		m_MyShipList;	//���� ���� ����� ����Ʈ
	ShipData*				m_ShipData;		//�� ����� ��ġ����
	int						m_Type;			//���� AI�� �Ϲ� Player�����ϱ� ���� �÷���
	std::wstring			m_Name;			

	//For AI

	std::vector<EnemyShip*>	m_EnemyShipList;	//���� �� ���� ����Ʈ
	std::list<Position>		m_HitPosList;		//��ȿ�� ���� ��ġ ����Ʈ
	std::list<Position>		m_DestroyPosList;	//��ȿ�� �ı� ��ġ ����Ʈ
	Position				m_Origin;			//������ ������
	Position				m_LastHit;			//������ ���������� ���� ��ġ
	AImode					m_AImode;			//HUNT or TARGET
	MyDirection				m_FindDir;			//�����ϴ� ����
};

