/************************************************************************/
/*
Class:		Ship

����:		���ӿ� ���Ǵ� ��ü(��)�� �߻� Ŭ����
			������ AirCraft, BattleShip, Cruiser, Destroyer�� �ִ�.
			���� ��ġ, Ÿ��, ������, HP���� ������ �谡 ���� Sprite���� ����

�߰����:
*/
/************************************************************************/

#pragma once
#include "Include.h"
#include "ActiveShipSprite.h"
#include "UIShipObject.h"
#include "Bitmap.h"
#include "Enum.h"

class Ship
{
public:
	Ship();
	virtual ~Ship();

	virtual void					ShipInit();
	virtual void					PlaceShip( Position setPos , MyDirection direction );
	virtual void					AddPosition( Position addPos );
	virtual HitResult				HitCheck( Position hitPos );
	void							SetHP( int _hp );
	int								GetHP();
	int								GetMaxHP(){return m_MaxHP;}
	MyShipType						GetShipType() {return m_Type;}
	std::vector <Position>			GetPos(){return m_Pos;}
	bool							IsDestroyed() {return m_IsDestroyed;}
	bool							IsDuplicate( Position checkPos );

	D2DSprite*						GetBFSprite() {return m_BattleSprite; }
	UIShipObject*					GetUISprite() {return m_UISprite; }
	ActiveShipSprite*					GetEnemyUISprite() {return m_EnemyUISprite;}
	void							CreateUISprite( float rowNum );

protected:
	std::string						m_Name;
	MyShipType						m_Type;
	std::vector <Position>			m_Pos;
	int								m_HP;
	int								m_MaxHP;
	bool							m_IsDestroyed;

	//BattleField�� ���Ǵ� ��������Ʈ 
	D2DSprite*						m_BattleSprite;
	//EnemyUI�� ���Ǵ� ��������Ʈ
	ActiveShipSprite*					m_EnemyUISprite;
	//UI�� ���Ǵ� ������Ʈ(�� ��������Ʈ + HP ��������Ʈ)
	UIShipObject*					m_UISprite;

	Bitmap*							m_VerticalBitmap;
	Bitmap*							m_HorizontalBitmap;
	Bitmap*							m_DestroyedBitmap;

};

