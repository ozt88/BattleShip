#pragma once
#include "stdafx.h"
#include "Enums.h"

class Ship;
class Board;

class Player
{
public:
	Player();
	~Player();

	void		InitPlayer();
	void		SetupShips(); // random location, random direction, check if within map bounds, ships can't overlap
	
	void		SetMyBoard( Position position , HitResult hitResult );
	void		SetEnemyBoard( Position position , HitResult hitResult );
	void		GetMyBoard();
	std::string getName(){return m_Name;}
	void		setName( std::string name ){m_Name = name;}
	bool		AllShipIsDestroyed();

	Position	Attack();
	HitResult	SendResult( Position position );
	void		PrintShips();


protected:
	bool		IsValidPosition( Position setPos , int maxHp , Direction direction );
	void		PlaceShip( Ship& ship , Position setPos , Direction direction );

private:
	Board*				m_MyBoard;
	Board*				m_EnemyBoard;
	std::list <Ship*>	m_ShipList;
	int					m_Type;
	std::string			m_Name;
};

