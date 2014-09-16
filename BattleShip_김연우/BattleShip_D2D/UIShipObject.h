#pragma once
#include "D2DObject.h"
#include "BFShipSprite.h"
#include "Bitmap.h"

class UIShipObject :
	public D2DObject
{
public:
	UIShipObject();
	~UIShipObject();

	void Init();
	void Create( Bitmap* NormalBitmap , Bitmap* DestroyedBitmap ,float maxHP , float posY );
	void Hit();
	void Clear();
	BFShipSprite* GetShipSprite() {return m_ShipSprite; }

private:
	BFShipSprite*			m_ShipSprite;
	std::list<D2DSprite*>	m_HPSpriteList;
	Bitmap*					m_HPBitmap;
};

