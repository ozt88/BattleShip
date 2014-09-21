/************************************************************************/
/*
Class:		Ship

설명:		게임에 사용되는 기체(배)의 추상 클래스
			하위로 AirCraft, BattleShip, Cruiser, Destroyer가 있다.
			배의 위치, 타입, 사이즈, HP등의 정보와 배가 가진 Sprite들을 관리

추가기능:
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

	//BattleField에 사용되는 스프라이트 
	D2DSprite*						m_BattleSprite;
	//EnemyUI에 사용되는 스프라이트
	ActiveShipSprite*					m_EnemyUISprite;
	//UI에 사용되는 오브젝트(배 스프라이트 + HP 스프라이트)
	UIShipObject*					m_UISprite;

	Bitmap*							m_VerticalBitmap;
	Bitmap*							m_HorizontalBitmap;
	Bitmap*							m_DestroyedBitmap;

};

