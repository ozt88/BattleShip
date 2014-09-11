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

	void				InitPlayer();
	void				SetupShips(); // random location, random direction, check if within map bounds, ships can't overlap
	bool				IsValidPosition( Position setPos , int maxHp , Direction direction );
	
	void				CalculateBoard();
	bool				ShipCanOccupy( int x , int y , int shipSize , bool isVertical );
	Position			Attack();   

	HitResult			SendResult( Position position );   
	void				UpdateMyBoard( Position position , HitResult hitResult );
	void				UpdateEnemyBoard( Position position , HitResult hitResult );
	Board*				GetMyBoard() {return m_MyBoard;}
	Board*				GetEnemyBoard() {return m_EnemyBoard;}
	std::wstring		GetName(){return m_Name;}
	void				SetName( std::wstring name ){m_Name = name;}
	std::list<Ship*>	GetShipList() {return m_ShipList; }
	bool				AllShipIsDestroyed();

private:
	Board*				m_MyBoard;
	Board*				m_EnemyBoard;
	std::list <Ship*>	m_ShipList;
	int					m_Type;
	std::wstring		m_Name;
};

