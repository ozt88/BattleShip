/************************************************************************/
/*
Class:		UIShipObject

설명:		ActiveShipSprite와 HP sprite를 생성 관리하는 오브젝트 
			맞으면 HP sprite를 화면에서 제거하고, 파괴되면 배의 비트맵을 변경

추가기능:
*/
/************************************************************************/

#pragma once
#include "D2DObject.h"
#include "ActiveShipSprite.h"
#include "Bitmap.h"

class UIShipObject :
	public D2DObject
{
public:
	UIShipObject();
	~UIShipObject();

	void					Init();
	void					Create( Bitmap* NormalBitmap , Bitmap* DestroyedBitmap ,float maxHP , float posY );
	void					Hit();
	void					Clear();
	ActiveShipSprite*		GetShipSprite() {return m_ShipSprite; }

private:
	ActiveShipSprite*		m_ShipSprite;
	std::list<D2DSprite*>	m_HPSpriteList;
	Bitmap*					m_HPBitmap;
};

