#pragma once
#include "D2DObject.h"
#include "D2DSprite.h"
#include "Bitmap.h"

class UIShipObject :
	public D2DObject
{
public:
	UIShipObject();
	~UIShipObject();

	void Init();
	void Create( Bitmap* bitmap , float maxHP , float posY );
	void Hit();
private:
	float					m_BoxSizeX;
	float					m_BoxSizeY;
	D2DSprite*				m_ShipSprite;
	std::list<D2DSprite*>	m_HPSpriteList;
	Bitmap*					m_HPBitmap;
};

