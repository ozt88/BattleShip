/************************************************************************/
/*
Class:		UIShipObject

����:		ActiveShipSprite�� HP sprite�� ���� �����ϴ� ������Ʈ 
			������ HP sprite�� ȭ�鿡�� �����ϰ�, �ı��Ǹ� ���� ��Ʈ���� ����

�߰����:
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

