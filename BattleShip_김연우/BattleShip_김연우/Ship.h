#pragma once
#include "Enums.h"
#include "stdafx.h"

class Ship
{
public:
	Ship();
	virtual ~Ship();

	void				ShipInit();
	void				AddPosition( Position addPos );
	virtual HitResult	HitCheck( Position hitPos );
	void				SetHP( int _hp );
	int					GetHP();
	int					GetMaxHP(){return m_MaxHP;}
	void				Print();
	bool				IsDestroyed();
	bool				IsDuplicate( Position checkPos );

protected:
	std::string				m_Name;
	ShipType				m_Type;
	std::vector <Position>	m_Pos;
	int						m_HP;
	int						m_MaxHP;
};