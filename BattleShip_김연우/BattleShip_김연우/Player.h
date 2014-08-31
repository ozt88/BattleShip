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
	bool		IsValidPosition( Position setPos , int maxHp , Direction direction );
	void		PlaceShip( Ship* ship , Position setPos , Direction direction );
	Position	Attack();   //ATTACKER
	HitResult	SendResult( Position position );   //DEFENDER
	void		UpdateMyBoard( Position position , HitResult hitResult );
	void		UpdateEnemyBoard( Position position , HitResult hitResult );
	void		PrintMyBoard();
	std::string GetName(){return m_Name;}
	void		SetName( std::string name ){m_Name = name;}
	bool		AllShipIsDestroyed();
	void		PrintShips();

private:
	Board*				m_MyBoard;
	Board*				m_EnemyBoard;
	std::list <Ship*>	m_ShipList;
	int					m_Type;
	std::string			m_Name;
};

