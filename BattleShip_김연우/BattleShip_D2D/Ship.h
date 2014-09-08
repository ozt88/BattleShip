#pragma once
#include "BFShipSprite.h"
#include "UIShipObject.h"
#include "Bitmap.h"
#include "Enum.h"

class Ship
{
public:
	Ship();
	virtual ~Ship();

	void					ShipInit();
	void					PlaceShip( Position setPos , Direction direction );
	void					AddPosition( Position addPos );
	virtual HitResult		HitCheck( Position hitPos );
	void					SetHP( int _hp );
	int						GetHP();
	int						GetMaxHP(){return m_MaxHP;}
	bool					IsDestroyed();
	bool					IsDuplicate( Position checkPos );
	
	BFShipSprite*			GetBFSprite() {return m_BattleSprite; }
	UIShipObject*			GetUISprite() {return m_UISprite; }
	void					CreateUISprite( float rowNum );

protected:
	BFShipSprite*			m_BattleSprite;
	UIShipObject*			m_UISprite;
	std::string				m_Name;
	ShipType				m_Type;
	std::vector <Position>	m_Pos;
	int						m_HP;
	int						m_MaxHP;
	Bitmap*					m_VerticalBitmap;
	Bitmap*					m_HorizontalBitmap;
};

